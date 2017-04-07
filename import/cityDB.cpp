#include "cityDB.hpp"
#include <iostream>
#include <fstream>
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

CityDB::CityDB(string const name, string const scriptPath, string const dirCSV, string const dirDB,
               vector<string> * filesNames, CSVShape * shape, int minYearData,
               int maxYearData) : name(name), scriptPath(scriptPath), dirCSV(dirCSV), dirDB(dirDB),
                                  filesNames(filesNames), maxYearData(maxYearData), minYearData(minYearData), shape(shape) {
    //pas finis
}
CityDB::~CityDB(){
    if(isActive){
        this->database->save(dirDB);
        delDB(this->database);
    }
    delete this->shape;
    delete this->filesNames;
}
void CityDB::download() {
    wrappy::call(scriptPath);
}

int CityDB::getMaxID(vector<vector<string>> data, int first, int second){
    int temp1;
    int temp2;
    int max=0;
    for (int i = 1; i < data[0].size() ; i++) {
        temp1 = unserialize<INT>(data[first][i]);
        temp2 = unserialize<INT>(data[second][i]);
        if (temp1<temp2) {
            temp1 = temp2;
        }
        if(temp1>max){
            max = temp1;
        }
    }
    return max;
}


void CityDB::initialiseStationNode(Result * nodeStation, int id, string name, double latitude, double longitude){
    Attribute * attrStation[4] = {new Attr<INT>("id"),
                                  new Attr<STRING>("name"),
                                  new Attr<DOUBLE>("latitude"),
                                  new Attr<DOUBLE>("longitude")};
    if(nodeStation == NULL) {
        attrStation[0]->setValue(&id);
        attrStation[1]->setValue(&name);
        attrStation[2]->setValue(&latitude);
        attrStation[3]->setValue(&longitude);
        nodeStation = this->database->newNode("Station", attrStation, 4);
    }
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


void CityDB::DBInstanciation() {

    int i = 0;
    vector<Result*> nodesStation(1,NULL);
    //// Dates nodes creation
    vector<vector<vector<Result * > > > nodesDay(this->maxYearData - this->minYearData +1, vector<vector<Result *> >(12, vector<Result *>(31, NULL)));
    
    vector<vector<Result * > > nodesMonth(this->maxYearData - this->minYearData +1, vector<Result *> (12,  NULL));

    vector<Result * > nodesYear(this->maxYearData - this->minYearData +1, NULL);

    /*
    Result * nodesDay[MAXYEARGAP][12][31] = {NULL};
    Result * nodesMonth[MAXYEARGAP][12] = {NULL};
    Result * nodesYear[MAXYEARGAP] = {NULL};
    */
    //// Time nodes creation
    vector<vector<Result * > > nodesMinute(24, vector<Result *>(60,  NULL));
    vector<Result * > nodesHour(24, NULL);
    /*Result * nodesMinute[24][60] = {NULL};
    Result * nodesHour[24] = {NULL};
    */
    
    for (i=0; i < filesNames->size(); i++) {
      importOneFile((*filesNames)[i], nodesStation, nodesDay,nodesMonth,nodesYear,nodesMinute,nodesHour);
    }
    // Delete Result objects
    for (int i = 0 ; i < nodesStation.size(); i++) {
        if (nodesStation[i]!=NULL)
            delResult(nodesStation[i]);
    }

    for (int i = 0 ; i < this->maxYearData - this->minYearData +1; i++)
        for (int j = 0 ; j < 12; j++)
            for (int k = 0 ; k < 31; k++)
                if (nodesDay[i][j][k]!=NULL)
                    delResult(nodesDay[i][j][k]);

    for (int i = 0 ; i < this->maxYearData - this->minYearData +1; i++)
        for (int j = 0 ; j < 12; j++)
            if (nodesMonth[i][j]!=NULL)
                delResult(nodesMonth[i][j]);

    for (int i = 0 ; i < this->maxYearData - this->minYearData +1; i++)
        if (nodesYear[i]!=NULL)
            delResult(nodesYear[i]);

    for (int i = 0 ; i < 24; i++)
        for (int j = 0 ; j < 60; j++)
            if (nodesMinute[i][j]!=NULL)
                delResult(nodesMinute[i][j]);

    for (int i = 0 ; i < 24; i++)
        if (nodesHour[i]!=NULL)
            delResult(nodesHour[i]);

}

void CityDB::importOneFile(string const file, vector<Result *> nodesStation,  vector<vector<vector<Result * > > > nodesDay,
		     vector<vector<Result * > > nodesMonth,
		     vector<Result * > nodesYear,
		     vector<vector<Result * > > nodesMinute,
			   vector<Result * > nodesHour)
{

    cout << "Parsing station file... " << dirCSV+file << endl;
    vector<vector<string> > data = parseCSVFile(dirCSV+file);
    cout << file << "OK" << endl;

    // Creation of the nodes and the edges
    //// About stations

    //// Needed variables
    INT id;
    STRING name;
    DOUBLE latitude;
    DOUBLE longitude;

    //// Gives the maximum id to declare the array of nodes correctly
    int max = getMaxID(data,shape->stationEndIDPlace,shape->stationStartIDPlace);
    if(max > nodesStation.size() -1 ){
        nodesStation.resize(max+1,NULL);
    }


    //// About data

    //// Needed variables
    INT gender;
    INT type;
    string date;
    string time;

    Attribute * attrBike[1] = {new Attr<INT>("id")}; // UNIQUE
    Attribute * attrUser[2] = {new Attr<INT>("type"),
                               new Attr<INT>("gender")};

    Result * nodeBike = NULL;
    Result * nodeUser = NULL;
    Result * nodeTrip = NULL;
    Result * nodesEvent[2] = {NULL};

    dateAndTime * dateTime;

    int idStart ;
    int idArrival ;

    //// Nodes and edges creation loop
    for (int i = 1 ; i < data[0].size() ; i++) {
        /////station initialisation
        idStart = stoi(data[i][this->shape->stationStartIDPlace]);
        initialiseStationNode(nodesStation[idStart],idStart,data[i][this->shape->stationStartNamePlace],unserialize<DOUBLE>(data[i][this->shape->stationStartLatitudePlace]),unserialize<DOUBLE>(data[i][this->shape->stationStartLongitudePlace]));
        idArrival = stoi(data[i][this->shape->stationEndIDPlace]);
        initialiseStationNode(nodesStation[idArrival],idArrival,data[i][this->shape->stationEndNamePlace],unserialize<DOUBLE>(data[i][this->shape->stationEndLatitudePlace]),unserialize<DOUBLE>(data[i][this->shape->stationEndLongitudePlace]));

        ///// Bike node
        id = unserialize<INT>(data[this->shape->bikeIDPlace][i]);
        attrBike[0]->setValue(&id);
        nodeBike = database->newNode("Bike", attrBike, 1);

        ///// User node
        if(this->shape->genderPlace != -1) {
            if (data[this->shape->genderPlace][i] == "Male") gender = GENDER_MALE;
            else if (data[this->shape->genderPlace][i] == "Female") gender = GENDER_FEMALE;
            else gender = GENDER_NO_INFO;
        }
        else{
            gender = GENDER_NO_INFO;
        }

        if(this->shape->userTypePlace != -1) {
            if (data[this->shape->userTypePlace][i] == "Subscriber") type = TYPE_SUBSCRIBER;
            else if (data[this->shape->userTypePlace][i] == "Customer") type = TYPE_CUSTOMER;
            else type = TYPE_NO_INFO;
        }
        else{
            type = TYPE_NO_INFO;
        }
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

        database->newEdge("takesPlace", nodesEvent[0], nodesStation[idStart], NULL, 0);
        database->newEdge("takesPlace", nodesEvent[1], nodesStation[idArrival], NULL, 0);

        ///// extract date and time for the start of the trip

        //In case date and time are found in the same place in the CSV
        if(this->shape->startDatePlace == this->shape->startTimePlace){
            int midPos = data[this->shape->startTimePlace][i].find(' ');
            //when date is first
            if(midPos > data[this->shape->startTimePlace][i].size()/2){
                date = data[this->shape->startTimePlace][i].substr(0,midPos);
                time = data[this->shape->startTimePlace][i].substr(midPos+1);
            }
            //when time is first
            else{
                time = data[this->shape->startTimePlace][i].substr(0,midPos);
                date = data[this->shape->startTimePlace][i].substr(midPos+1);
            }
        }
        //When date and time can be found in different places
        else{
            date = data[this->shape->startDatePlace][i];
            time = data[this->shape->startTimePlace][i];
        }

        dateTime = dateInNodes(date,time);


        initialiseDateNode(nodesDay[dateTime->year - this->maxYearData][dateTime->month-1][dateTime->day-1],
                           nodesMonth[dateTime->year - this->maxYearData][dateTime->month-1],
                           nodesYear[dateTime->year - this->maxYearData],dateTime->year,dateTime->month,dateTime->day);
        initialiseHourNode(nodesHour[dateTime->hour-1],nodesMinute[dateTime->minute-1][dateTime->hour-1],dateTime->hour,dateTime->minute);
        database->newEdge("datesFrom", nodesEvent[0], nodesDay[dateTime->year - this->maxYearData][dateTime->month-1][dateTime->day-1], NULL, 0);
        database->newEdge("timesFrom", nodesEvent[0], nodesMinute[dateTime->minute-1][dateTime->hour-1], NULL, 0);

        ///// extract date and time for the arrival of the trip

        //In case date and time are found in the same place in the CSV
        if(this->shape->endDatePlace == this->shape->endTimePlace){
            int midPos = data[this->shape->endTimePlace][i].find(' ');
            //when date is first
            if(midPos > data[this->shape->endTimePlace][i].size()/2){
                date = data[this->shape->endTimePlace][i].substr(0,midPos);
                time = data[this->shape->endTimePlace][i].substr(midPos+1);
            }
                //when time is first
            else{
                time = data[this->shape->endTimePlace][i].substr(0,midPos);
                date = data[this->shape->endTimePlace][i].substr(midPos+1);
            }
        }
            //When date and time can be found in different places
        else{
            date = data[this->shape->endDatePlace][i];
            time = data[this->shape->endTimePlace][i];
        }
        dateTime = dateInNodes(date,time);

        initialiseDateNode(nodesDay[dateTime->year - this->maxYearData][dateTime->month-1][dateTime->day-1],
                           nodesMonth[dateTime->year - this->maxYearData][dateTime->month-1],
                           nodesYear[dateTime->year - this->maxYearData],dateTime->year,dateTime->month,dateTime->day);
        initialiseHourNode(nodesHour[dateTime->hour-1],nodesMinute[dateTime->minute-1][dateTime->hour-1],dateTime->hour,dateTime->minute);
        database->newEdge("datesFrom", nodesEvent[1], nodesDay[dateTime->year - this->maxYearData][dateTime->month-1][dateTime->day-1], NULL, 0);
        database->newEdge("timesFrom", nodesEvent[1], nodesMinute[dateTime->minute-1][dateTime->hour-1], NULL, 0);

    }

    // Delete Attribute objects
    if(attrBike!=NULL)
        delAttr(attrBike, 1);
    if(attrUser!=NULL)
        delAttr(attrUser, 2);

    if(nodeBike!=NULL)
        delResult(nodeBike);
    if(nodeUser!=NULL)
        delResult(nodeUser);
    if(nodeTrip!=NULL)
        delResult(nodeTrip);
    if(nodesEvent[0]!=NULL)
        delResult(nodesEvent[0]);
    if(nodesEvent[1]!=NULL)
        delResult(nodesEvent[1]);

}

Database * CityDB::activate(){
    struct stat buf;
    if( stat((dirDB+name+".db").c_str(),&buf)){

      this->database = newDB(this->name);

      entitiesCreation(database);

      relationshipsCreation(database);


      download();
      DBInstanciation();
    } else {
        this->database = newDB(this->name);
        this->database->load(dirDB + "/" + name + ".db");
        this->isActive = true;
    }
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



dateAndTime * CityDB::dateInNodes(const string & date, const string & time) {
    dateAndTime * dateTime = new(dateAndTime);
    string token;

    istringstream tmpStreamDate(date);

    getline(tmpStreamDate, token, '/');
    dateTime->month=stoi(token);
    getline(tmpStreamDate, token, '/');
    dateTime->day=stoi(token);
    getline(tmpStreamDate, token, '/');
    dateTime->year=stoi(token);

    istringstream tmpStreamTime(time);

    getline(tmpStreamTime, token, ':');
    dateTime->hour=stoi(token);
    getline(tmpStreamTime, token, ':');
    dateTime->minute=stoi(token);

    return  dateTime;
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

