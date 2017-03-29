#include "cityDB.h"
#include <iostream>
#include <string>
#include <vector>

#include "Database.hpp"
#include "DBTools.hpp"
#include "Result.hpp"

using namespace std;

CityDB::CityDB(string const& name, string const & scriptDir, string const & dirCSV, string const & dirDB,
               vector<string const&> filesNames, CSVShape * shape) : name(name), scriptDir(scriptDir), dirCSV(dirCSV),
                dirDB(dirDB), filesNames(filesNames), shape(shape){
    initDB();
    database = newDB(name+"Database");
    entitiesCreation(database);
    relationshipsCreation(database);
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

    Attribute * attrUser[1] = {new Attr<INT>("value")};
    database->newEntity("User", attrUser, 1);

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
    delAttr(attrBike, 1);
    delAttr(attrUser, 1);
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
