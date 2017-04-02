#include "cityDB.h"
#include <iostream>
#include <string>
#include <vector>

#include "Database.hpp"
#include "DBTools.hpp"
#include "Result.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <wrappy/wrappy.h>
using namespace std;

CityDB::CityDB(string const& name, string const & scriptPath, string const & dirCSV, string const & dirDB,
               vector<string const&> filesNames, CSVShape * shape, int minYearData,
               int maxYearData) : name(name), scriptPath(scriptPath), dirCSV(dirCSV), dirDB(dirDB),
                                  filesNames(filesNames), shape(shape), minYearData(minYearData), maxYearData(maxYearData) {
    //pas finis
}
void CityDB::download() {
    wrappy::call(scriptPath);
}

void CityDB::DBInstanciation() {

    // .csv files parsing process
    int i = 0;
    for (i; i++; i < filesNames.size()) {
        importOneFile(filesNames[i]);
    }
}
int CityDB::getMaxID(vector<vector<string> > data, int first, int second){
    int temp1;
    int temp2;
    int max=0;
    for (int i = 1; i < data[0].size() ; i++) {
        temp1 = unserialize<INT>(stationsData[first][i]);
        temp2 = unserialize<INT>(stationsData[second][i]);
        if (temp1<temp2) {
            temp1 = temp2;
        }
        if(temp1>max){
            max = id;
        }
    }
    return max;
}
void CityDB::initialiseStationNode(vector<string> data, Result ** nodesStation, Attribute * attrStation[4],
                                   int idPlace, int namePlace, int latitudePlace, int longitudePlace){

    Attribute * attrStation[4] = {new Attr<INT>("id"),
                                  new Attr<STRING>("name"),
                                  new Attr<DOUBLE>("latitude"),
                                  new Attr<DOUBLE>("longitude")};
    INT id = unserialize<INT>(data[idPlace]);
    attrStation[0]->setValue(&id);
    STRING name = unserialize<STRING>(data[namePlace]);
    attrStation[1]->setValue(&name);
    DOUBLE latitude = unserialize<DOUBLE>(data[latitudePlace]);
    attrStation[2]->setValue(&latitude);
    DOUBLE longitude = unserialize<DOUBLE>(data[longitudePlace]);
    attrStation[3]->setValue(&longitude);
    nodesStation[id] = this->database->newNode("Station", attrStation, 4);

    //// Delete Attribute object
    delAttr(attrStation, 4);

}

void CityDB::initialiseDateNode(Result * nodeDay, Result * nodeMonth, Result * nodeYear,int year, int month, int day) {
    Attribute * attrYear[1] = {new Attr<INT>("value")};
    Attribute * attrMonth[1] = {new Attr<INT>("value")};
    Attribute * attrDay[1] = {new Attr<INT>("value")};
    if(nodeYear == NULL) {
        attrYear[0]->setValue(&year);
        nodeYear = database->newNode("Year", attrYear, 1);
    }
    if(nodeMonth == NULL) {
        attrMonth[0]->setValue(&month);
        nodeMonth = database->newNode("Month", attrMonth, 1);
        database->newEdge("isChildMonth", nodeYear, nodeMonth, NULL, 0);
    }
    if(nodeDay == NULL){
        attrDay[0]->setValue(&day);
        nodeDay = database->newNode("Day", attrDay, 1);
        database->newEdge("isChildDay", nodeMonth, nodeDay, NULL, 0);

    }
    delAttr(attrYear, 1);
    delAttr(attrMonth, 1);
    delAttr(attrDay, 1);

}

void CityDB::initialiseHourNode(Result * nodeHour, Result * nodeMinute,int hour, int minute){
    Attribute * attrMinute[1] = {new Attr<INT>("value")};
    Attribute * attrHour[1] = {new Attr<INT>("value")};

    if(nodeHour == NULL) {
        attrHour[0]->setValue(&hour);
        nodeHour = database->newNode("Hour", attrHour, 1);
    }
    if(nodeMinute == NULL){
        attrMinute[0]->setValue(&minute);
        nodeMinute = database->newNode("Minute", attrMinute, 1);
        database->newEdge("isChildMinute", nodeHour, nodeMinute, NULL, 0);
        }
    delAttr(attrMinute, 1);
    delAttr(attrHour, 1);

};

void CityDB::importOneFile(string const & file){

    cout << "Parsing station file... " << endl;
    vector<vector<string> > data = parseCSVFile(dirCSV+file);
    cout << filesNames[i] << "OK" << endl;

    // Creation of the nodes and the edges
    /// About stations

    //// Needed variables
    INT id;
    STRING name;
    DOUBLE latitude;
    DOUBLE longitude;

    //// Gives the maximum id to declare the array of nodes correctly
    int max = getMaxID(data,shape->stationEndIDPlace,shape->stationStartIDPlace);

    Result * nodesStation[max+1] = {NULL};



    /// About dates and time

    //// Dates nodes creation
    Result * nodesDay[1][12][31] = {NULL};
    Result * nodesMonth[1][12] = {NULL};
    Result * nodesYear[1] = {NULL};

    //// Time nodes creation
    Result * nodesMinute[24][60] = {NULL};
    Result * nodesHour[24] = {NULL};

    /// About data

    //// Needed variables
    INT gender;
    INT type;

    Attribute * attrBike[1] = {new Attr<INT>("id")}; // UNIQUE
    Attribute * attrUser[2] = {new Attr<INT>("type"),
                               new Attr<INT>("gender")};

    Result * nodeBike = NULL;
    Result * nodeUser = NULL;
    Result * nodeTrip = NULL;
    Result * nodesEvent[2] = {NULL};

    vector<int> date;

    //// Nodes and edges creation loop
    for (int i = 1 ; i < data[0].size() ; i++) {

        ///// Bike node
        id = unserialize<INT>(tripsData[3][i]);
        attrBike[0]->setValue(&id);
        nodeBike = database->newNode("Bike", attrBike, 1);

        ///// User node
        if (tripsData[10][i] == "Male") gender = GENDER_MALE;
        else if (tripsData[10][i] == "Female") gender = GENDER_FEMALE;
        else gender = GENDER_NO_INFO;

        if (tripsData[9][i] == "Subscriber") type = TYPE_SUBSCRIBER;
        else if (tripsData[9][i] == "Customer") type = TYPE_CUSTOMER;
        else type = TYPE_NO_INFO;

        attrUser[0]->setValue(&gender);
        attrUser[1]->setValue(&type);
        nodeUser = database->newNode("User", attrUser, 2);

        ///// Trip node
        nodeTrip = database->newNode("Trip", NULL, 0);

        ///// Event nodes
        nodesEvent[0] = database->newNode("Event", NULL, 0);
        nodesEvent[1] = database->newNode("Event", NULL, 0);

        ///// Edges
        database->newEdge("uses", nodeTrip, nodeBike, NULL, 0);

        database->newEdge("does", nodeUser, nodeTrip, NULL, 0);

        database->newEdge("departs", nodeTrip, nodesEvent[0], NULL, 0);

        database->newEdge("arrives", nodeTrip, nodesEvent[1], NULL, 0);

        int idStart = stoi(tripsData[5][i]);
        int idArrival = stoi(tripsData[7][i]);

        database->newEdge("takesPlace", nodesEvent[0], nodesStation[idStart], NULL, 0);
        database->newEdge("takesPlace", nodesEvent[1], nodesStation[idArrival], NULL, 0);

        date = dateInNodes(tripsData[1][i]);
        database->newEdge("datesFrom", nodesEvent[0], nodesDay[date[2]-2016][date[0]-1][date[1]-1], NULL, 0);
        database->newEdge("timesFrom", nodesEvent[0], nodesMinute[date[3]][date[4]], NULL, 0);
        date = dateInNodes(tripsData[2][i]);
        database->newEdge("datesFrom", nodesEvent[1], nodesDay[date[2]-2016][date[0]-1][date[1]-1], NULL, 0);
        database->newEdge("timesFrom", nodesEvent[1], nodesMinute[date[3]][date[4]], NULL, 0);
    }

    // Delete Attribute objects
    delAttr(attrBike, 1);
    delAttr(attrUser, 2);

    // Delete Result objects
    for (int i = 0 ; i < max+1; i++) {
        if (nodesStation[i])
            delResult(nodesStation[i]);
    }

    delResult(nodeBike);
    delResult(nodeUser);
    delResult(nodeTrip);
    delResult(nodesEvent[0]);
    delResult(nodesEvent[1]);

    for (int i = 0 ; i < 1; i++)
        for (int j = 0 ; j < 12; j++)
            for (int k = 0 ; k < 31; k++)
                if (nodesDay[i])
                    delResult(nodesDay[i][j][k]);

    for (int i = 0 ; i < 1; i++)
        for (int j = 0 ; j < 12; j++)
            if (nodesMonth[i])
                delResult(nodesMonth[i][j]);

    for (int i = 0 ; i < 1; i++)
        if (nodesYear[i])
            delResult(nodesYear[i]);

    for (int i = 0 ; i < 24; i++)
        for (int j = 0 ; j < 60; j++)
            if (nodesMinute[i])
                delResult(nodesMinute[i][j]);

    for (int i = 0 ; i < 24; i++)
        if (nodesHour[i])
            delResult(nodesHour[i]);

}

Database * CityDB::activate(){
    struct stat buf;
    if( stat(dirDB+name+".db",&buf)){
        database = newDB(name);
        entitiesCreation(database);
        relationshipsCreation(database);

    }
    this->database = newDB(this->name);
    this->database->load(dirDB+"/"+name+".db");
    this->isActive = true;
    return this->database;
}
void CityDB::desactivate() {
    this->database->save(dirDB);
    this->isActive = false;
    delDB(this->database);
}

void CityDB::entitiesCreation(Database * database) {
    Attribute * attrStation[4] = {new Attr<INT>("id"), // UNIQUE
                                  new Attr<STRING>("name"),
                                  new Attr<DOUBLE>("latitude"),
                                  new Attr<DOUBLE>("longitude")};
    database->newEntity("Station", attrStation, 4);

    database->newEntity("Event", NULL, 0);

    database->newEntity("Trip", NULL, 0);

    Attribute * attrBike[1] = {new Attr<INT>("id")}; // UNIQUE
    database->newEntity("Bike", attrBike, 1);

    Attribute * attrUser[2] = {new Attr<INT>("type"),
                               new Attr<INT>("gender")};
    database->newEntity("User", attrUser, 2);

    Attribute * attrDay[1] = {new Attr<INT>("value")};
    database->newEntity("Day", attrDay, 1);

    Attribute * attrMonth[1] = {new Attr<INT>("value")};
    database->newEntity("Month", attrMonth, 1);

    Attribute * attrYear[1] = {new Attr<INT>("value")};
    database->newEntity("Year", attrYear, 1);

    Attribute * attrMinute[1] = {new Attr<INT>("value")};
    database->newEntity("Minute", attrMinute, 1);

    Attribute * attrHour[1] = {new Attr<INT>("value")};
    database->newEntity("Hour", attrHour, 1);
    Attribute * attrRootHour[1] = {new Attr<INT>("value")};
    database->newEntity("RootHour", attrRootHour, 1);

    Attribute * attrRootDate[1] = {new Attr<INT>("value")};
    database->newEntity("RootDate", attrRootDate, 1);

    // Delete Attribute objects
    delAttr(attrStation, 4);
    delAttr(attrBike, 1);
    delAttr(attrUser, 2);
    delAttr(attrDay, 1);
    delAttr(attrMonth, 1);
    delAttr(attrYear, 1);
    delAttr(attrMinute, 1);
    delAttr(attrHour, 1);
    delAttr(attrRootHour, 1);
    delAttr(attrRootDate, 1);
}



vector<int> CityDB::dateInNodes(const string &csvDate) {
    vector<string> tmpDateInNodes;
    string tmpNode="";
    for (int i=0; i<=csvDate.size(); ++i) {
        if (csvDate[i]=='/' || csvDate[i]==':' || csvDate[i]==' ' || csvDate[i]=='\000') {
            tmpDateInNodes.push_back(tmpNode);
            tmpNode="";
        }
        else {
            tmpNode+=csvDate[i];
        }
    }
    vector<int> dateInNodes;
    for (int i=0; i<5; ++i)
        dateInNodes.push_back(stoi(tmpDateInNodes[i]));
    return dateInNodes;
}


void CityDB::relationshipsCreation(Database * database) {

    database->newRelation("takesPlace", "Event", "Station", NULL, 0);

    database->newRelation("departs", "Trip", "Event", NULL, 0);
    database->newRelation("arrives", "Trip", "Event", NULL, 0);

    database->newRelation("uses", "Trip", "Bike", NULL, 0);

    database->newRelation("does", "User", "Trip", NULL, 0);

    database->newRelation("datesFrom", "Event", "Day", NULL, 0);

    database->newRelation("timesFrom", "Event", "Minute", NULL, 0);

    database->newRelation("isFirstDay", "Month", "Day", NULL, 0);
    database->newRelation("isChildDay", "Month", "Day", NULL, 0);
    database->newRelation("isLastDay", "Month", "Day", NULL, 0);
    database->newRelation("isNextDay", "Day", "Day", NULL, 0);

    database->newRelation("isFirstMonth", "Year", "Month", NULL, 0);
    database->newRelation("isChildMonth", "Year", "Month", NULL, 0);
    database->newRelation("isLastMonth", "Year", "Month", NULL, 0);
    database->newRelation("isNextMonth", "Month", "Month", NULL, 0);

    database->newRelation("isFirstYear", "RootDate", "Year", NULL, 0);
    database->newRelation("isChildYear", "RootDate", "Year", NULL, 0);
    database->newRelation("isLastYear", "RootDate", "Year", NULL, 0);
    database->newRelation("isNextYear", "Year", "Year", NULL, 0);

    database->newRelation("isFirstMinute", "Hour", "Minute", NULL, 0);
    database->newRelation("isChildMinute", "Hour", "Minute", NULL, 0);
    database->newRelation("isLastMinute", "Hour", "Minute", NULL, 0);
    database->newRelation("isNextMinute", "Minute", "Minute", NULL, 0);

    database->newRelation("isFirstHour", "RootHour", "Hour", NULL, 0);
    database->newRelation("isChildHour", "RootHour", "Hour", NULL, 0);
    database->newRelation("isLastHour", "RootHour", "Hour", NULL, 0);
    database->newRelation("isNextHour", "Hour", "Hour", NULL, 0);

    database->newRelation("isBorn", "User", "Year", NULL, 0);

    database->newRelation("links", "Station", "Station", NULL, 0);

}

vector<vector<string> > CityDB::parseCSVFile(const string &csv_file) {
    ifstream file(csv_file, ios::in); // Read-only .csv file opening
    if (file) // If the opening succeeded
    {
        vector<string> namesVarList; // Dynamic array declaration
        char character; // Last character read
        int i=0;
        while ( character != '\n' && file.get(character) ) // While it is the 1st line
        {
            namesVarList.push_back(""); // Creates a field
            while ( character != ',' && character != '\n' ) // While it is the 1st line and the same field
            {
                namesVarList[i] += character; // Continues to write the field name
                file.get(character); // Reads the next character
            }
            i++;
        }
        vector<vector<string> > data; // Dynamic bidimensional array for data
        for (int j=0; j<i; ++j)
        {
            data.push_back(vector<string>(1, namesVarList[j])); // Creates as columns as fields in the table
        }
        i=0; int j=1; character='\0'; // '\0' to avoid a falsifying '\n'
        while (j < 10000 && !file.eof() && file.get(character) ) // While it's not the end of the file
        {
            data[i].push_back(""); // Creates a value
            while ( character != ',' && character != '\n' ) // While it is the same line and the same value
            {
                data[i][j] += character; // Continues to write the value
                file.get(character); // Reads the next character
            }
            if ( character == ',' ) // Manages the counters
            {
                i++;
            }
            if ( character == '\n' )
            {
                i=0;
                j++;
            }
        }
        return data; // Returns the table
    }
    else
    {
        cerr << "Error: can't open file" << endl;
        vector<vector<string> > empty; // Creates an empty dynamic bidimensional array...
        return empty; // ... to respect the type
    }
}

