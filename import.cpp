#include <iostream>
#include <string>
#include <vector>
#include "Database.hpp"
#include "parseCSVfile.hpp"

using namespace std;

int importChicago() {

  // .csv files parsing process
  vector<vector<string> > stationsData = parseCSVFile("Divvy_Stations_2016_Q1Q2.csv");
  vector<vector<string> > tripsData = parseCSVFile("Divvy_Trips_2016_Q1.csv");


  // Creation of the database
  Database * chicagoDatabase = newDB("Chicago Database");


  // Creation of the entities
  AttrType attrStation[4] = {AttrType("id", INT, UNIQUE), 
			     AttrType("name", STRING), 
			     AttrType("latitude", DOUBLE), 
			     AttrType("longitude", DOUBLE)};
  chicagoDatabase->newEntity("Station", attrStation, 4);

  chicagoDatabase->newEntity("Event", NULL, 0);

  chicagoDatabase->newEntity("Trip", NULL, 0);

  AttrType attrBike[1] = {AttrType("id", INT, UNIQUE)};
  chicagoDatabase->newEntity("Bike", attrBike, 1);

  AttrType attrUser[2] = {AttrType("gender", INT, UNIQUE),
			  AttrType("type", STRING)};
  chicagoDatabase->newEntity("User", attrUser, 2);

  AttrType attrDay[1] = {AttrType("value", STRING, UNIQUE)};
  chicagoDatabase->newEntity("Day", NULL, 0);

  AttrType attrMonth[1] = {AttrType("value", STRING, UNIQUE)};
  chicagoDatabase->newEntity("Month", NULL, 0);

  AttrType attrYear[1] = {AttrType("value", STRING, UNIQUE)};
  chicagoDatabase->newEntity("Year", NULL, 0);

  AttrType attrMinute[1] = {AttrType("value", STRING, UNIQUE)};
  chicagoDatabase->newEntity("Minute", NULL, 0);

  AttrType attrHour[1] = {AttrType("value", STRING, UNIQUE)};
  chicagoDatabase->newEntity("Hour", NULL, 0);

  AttrType attrRootHour[1] = {AttrType("value", STRING, UNIQUE)};
  chicagoDatabase->newEntity("RootHour", NULL, 0);

  AttrType attrRootDate[1] = {AttrType("value", STRING, UNIQUE)};
  chicagoDatabase->newEntity("RootDate", NULL, 0);


  // Creation of the relationships
  chicagoDatabase->newRelation("takesPlace", "Event", "Station", NULL, 0);

  chicagoDatabase->newRelation("departs", "Trip", "Event", NULL, 0);
  chicagoDatabase->newRelation("arrives", "Trip", "Event", NULL, 0);

  chicagoDatabase->newRelation("uses", "Trip", "Bike", NULL, 0);

  chicagoDatabase->newRelation("does", "User", "Trip", NULL, 0);

  chicagoDatabase->newRelation("datesFrom", "Event", "Day", NULL, 0);

  chicagoDatabase->newRelation("timesFrom", "Event", "Minute", NULL, 0);

  chicagoDatabase->newRelation("isFirstDay", "Month", "Day", NULL, 0);
  chicagoDatabase->newRelation("isChildDay", "Month", "Day", NULL, 0); // a traiter lors de l'insertion en n'ajoutant que les dates apparaissant
  chicagoDatabase->newRelation("isLastDay", "Month", "Day", NULL, 0);
  chicagoDatabase->newRelation("isNextDay", "Day", "Day", NULL, 0);

  chicagoDatabase->newRelation("isFirstMonth", "Year", "Month", NULL, 0);
  chicagoDatabase->newRelation("isChildMonth", "Year", "Month", NULL, 0); // a traiter lors de l'insertion en n'ajoutant que les dates apparaissant
  chicagoDatabase->newRelation("isLastMonth", "Year", "Month", NULL, 0);
  chicagoDatabase->newRelation("isNextMonth", "Month", "Month", NULL, 0);

  chicagoDatabase->newRelation("isFirstYear", "RootDate", "Year", NULL, 0);
  chicagoDatabase->newRelation("isChildYear", "RootDate", "Year", NULL, 0); // a traiter lors de l'insertion en n'ajoutant que les dates apparaissant
  chicagoDatabase->newRelation("isLastYear", "RootDate", "Year", NULL, 0);
  chicagoDatabase->newRelation("isNextYear", "Year", "Year", NULL, 0);

  chicagoDatabase->newRelation("isFirstMinute", "Hour", "Minute", NULL, 0);
  chicagoDatabase->newRelation("isChildMinute", "Hour", "Minute", NULL, 0); // a traiter lors de l'insertion en n'ajoutant que les dates apparaissant
  chicagoDatabase->newRelation("isLastMinute", "Hour", "Minute", NULL, 0);
  chicagoDatabase->newRelation("isNextMinute", "Minute", "Minute", NULL, 0);

  chicagoDatabase->newRelation("isFirstHour", "RootHour", "Hour", NULL, 0);
  chicagoDatabase->newRelation("isChildHour", "RootHour", "Hour", NULL, 0); // a traiter lors de l'insertion en n'ajoutant que les dates apparaissant
  chicagoDatabase->newRelation("isLastHour", "RootHour", "Hour", NULL, 0);
  chicagoDatabase->newRelation("isNextHour", "Hour", "Hour", NULL, 0);

  chicagoDatabase->newRelation("isBorn", "User", "Year", NULL, 0);

  chicagoDatabase->newRelation("links", "Station", "Station", NULL, 0);
  

  // Creation of the nodes and the edges
  node * nodesStation[stationsData[0].size-1];
  AttrValue valuesStation[4] = {AttrValue("id", 0),
				AttrValue("name", ""),
				AttrValue("latitude", 0.0),
				AttrValue("longitude", 0.0)};
  for (int i=1; i<stationsData[0].size; i++) {
    for (int j=0; j<4; j++) {
      valuesStation[j].value = stationsData[j][i];
    }
    nodesStation[i-1] = chicagoDatabase->newNode("Station", valuesStations, 4);
  }

  int numberLinesData = tripsData[0].size-1;

  node * nodesBike[numberLinesData];
  AttrValue valuesBike[1] = {AttrValue("id", 0)};
  node * nodesUser[numberLinesData];
  AttrValue valuesUser[2] = {AttrValue("gender", 0),
			     AttrValue("type", "")};
  node * nodesDate[numberLinesData]; // provisoire
  AttrValue valuesDate[2] = {AttrValue("start", ""),
			     AttrValue("stop", "")}; // provisoire
  node * nodesTrip[numberLinesData];
  node * nodesEvent[numberLinesData];

  for (int i=1; i<tripsData[0].size; i++) {
    valuesBike[0].value = tripsData[3][i];
    valuesUser[0].value = tripsData[10][i];
    valuesUser[1].value = tripsData[9][i];
    nodesBike[i-1] = chicagoDatabase->newNode("Bike", valuesBike, 1);
    nodesUser[i-1] = chicagoDatabase->newNode("User", valuesUser, 2);

    valuesDate[0].value = tripsData[1][i]; // provisoire
    valuesDate[1].value = tripsData[2][i]; // provisoire
    nodesDate[i-1] = chicagoDatabase->newNode("Date", valuesDate, 2); // provisoire

    nodesTrip[i-1] = chicagoDatabase->newNode("Trip", NULL, 0);
    nodesEvent[i-1] = chicagoDatabase->newNode("Event", NULL, 0);

    chicagoDatabase->newEdge("uses", nodesTrip[i-1], nodesBike[i-1], NULL, 0);
    chicagoDatabase->newEdge("does", nodesUser[i-1], nodesTrip[i-1], NULL, 0);
    chicagoDatabase->newEdge("departs", nodesTrip[i-1], nodesEvent[i-1], NULL, 0);
    chicagoDatabase->newEdge("arrives", nodesTrip[i-1], nodesEvent[i-1], NULL, 0);
    chicagoDatabase->newEdge("datesFrom", nodesEvent[i-1], nodesDate[i-1], NULL, 0);
    chicagoDatabase->newEdge("takesPlace", nodesEvent[i-1], //, NULL, 0);
  }
}
