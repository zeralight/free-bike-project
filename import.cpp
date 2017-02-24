#include <iostream>
#include <string>
#include <vector>

#include "Database.hpp"
#include "DBTools.hpp"
#include "extraction/extraction.hpp"
#include "dateInNodes.hpp"

using namespace std;

int importChicago() {

  // .csv files parsing process
  vector<vector<string> > stationsData = parseCSVFile("Divvy_Stations_2016_Q1Q2.csv");
  vector<vector<string> > tripsData = parseCSVFile("Divvy_Trips_2016_Q1.csv");

  // Creation of the database
  Database * chicagoDatabase = newDB("Chicago Database");

  // Creation of the entities
  Attribute * attrStation[4] = {new Attr<INT>("id"), // UNIQUE 
				new Attr<STRING>("name"), 
				new Attr<DOUBLE>("latitude"), 
				new Attr<DOUBLE>("longitude")};
  chicagoDatabase->newEntity("Station", attrStation, 4);
  
  chicagoDatabase->newEntity("Event", NULL, 0);
  
  chicagoDatabase->newEntity("Trip", NULL, 0);
  
  Attribute * attrBike[1] = {new Attr<INT>("id")}; // UNIQUE
  chicagoDatabase->newEntity("Bike", attrBike, 1);

  Attribute * attrUser[2] = {new Attr<INT>("gender"),
			     new Attr<STRING>("type")};
  chicagoDatabase->newEntity("User", attrUser, 2);

  Attribute * attrDay[1] = {new Attr<INT>("value")};
  chicagoDatabase->newEntity("Day", attrDay, 1);

  Attribute * attrMonth[1] = {new Attr<INT>("value")};
  chicagoDatabase->newEntity("Month", attrMonth, 1);

  Attribute * attrYear[1] = {new Attr<INT>("value")};
  chicagoDatabase->newEntity("Year", attrYear, 1);

  Attribute * attrMinute[1] = {new Attr<INT>("value")};
  chicagoDatabase->newEntity("Minute", attrMinute, 1);
  
  Attribute * attrHour[1] = {new Attr<INT>("value")};
  chicagoDatabase->newEntity("Hour", attrHour, 1);

  Attribute * attrRootHour[1] = {new Attr<INT>("value")};
  chicagoDatabase->newEntity("RootHour", attrRootHour, 1);

  Attribute * attrRootDate[1] = {new Attr<INT>("value")};
  chicagoDatabase->newEntity("RootDate", attrRootDate, 1);

  // Supprimé :
  // Attribute * attrDate[1] = {new Attr<STRING>("value")};
  // chicagoDatabase->newEntity("Date", attrDate, 1);

  // Creation of the relationships
  chicagoDatabase->newRelation("takesPlace", "Event", "Station", NULL, 0);

  chicagoDatabase->newRelation("departs", "Trip", "Event", NULL, 0);
  chicagoDatabase->newRelation("arrives", "Trip", "Event", NULL, 0);

  chicagoDatabase->newRelation("uses", "Trip", "Bike", NULL, 0);

  chicagoDatabase->newRelation("does", "User", "Trip", NULL, 0);

  chicagoDatabase->newRelation("datesFrom", "Event", "Day", NULL, 0);

  chicagoDatabase->newRelation("timesFrom", "Event", "Minute", NULL, 0);

  chicagoDatabase->newRelation("isFirstDay", "Month", "Day", NULL, 0);
  chicagoDatabase->newRelation("isChildDay", "Month", "Day", NULL, 0);
  chicagoDatabase->newRelation("isLastDay", "Month", "Day", NULL, 0);
  chicagoDatabase->newRelation("isNextDay", "Day", "Day", NULL, 0);

  chicagoDatabase->newRelation("isFirstMonth", "Year", "Month", NULL, 0);
  chicagoDatabase->newRelation("isChildMonth", "Year", "Month", NULL, 0);
  chicagoDatabase->newRelation("isLastMonth", "Year", "Month", NULL, 0);
  chicagoDatabase->newRelation("isNextMonth", "Month", "Month", NULL, 0);

  chicagoDatabase->newRelation("isFirstYear", "RootDate", "Year", NULL, 0);
  chicagoDatabase->newRelation("isChildYear", "RootDate", "Year", NULL, 0);
  chicagoDatabase->newRelation("isLastYear", "RootDate", "Year", NULL, 0);
  chicagoDatabase->newRelation("isNextYear", "Year", "Year", NULL, 0);

  chicagoDatabase->newRelation("isFirstMinute", "Hour", "Minute", NULL, 0);
  chicagoDatabase->newRelation("isChildMinute", "Hour", "Minute", NULL, 0);
  chicagoDatabase->newRelation("isLastMinute", "Hour", "Minute", NULL, 0);
  chicagoDatabase->newRelation("isNextMinute", "Minute", "Minute", NULL, 0);

  chicagoDatabase->newRelation("isFirstHour", "RootHour", "Hour", NULL, 0);
  chicagoDatabase->newRelation("isChildHour", "RootHour", "Hour", NULL, 0);
  chicagoDatabase->newRelation("isLastHour", "RootHour", "Hour", NULL, 0);
  chicagoDatabase->newRelation("isNextHour", "Hour", "Hour", NULL, 0);

  chicagoDatabase->newRelation("isBorn", "User", "Year", NULL, 0);

  chicagoDatabase->newRelation("links", "Station", "Station", NULL, 0);
  

  // Creation of the nodes and the edges
  // About stations
  Result * nodesStation[stationsData[0].size-1];
  
  INT id;
  STRING name;
  DOUBLE latitude;
  DOUBLE longitude;
  
  for (int i = 1; i < stationsData[0].size ; i++) {
    id = unserialize<INT>(stationsData[0][i]);
    attrStation[0]->setValue(&id);
    name = unserialize<STRING>stationsData[1][i];
    attrStation[1]->setValue(&name);
    latitude = unserialize<DOUBLE>(stationsData[2][i]);
    attrStation[2]->setValue(&latitude);
    longitude = unserialize<DOUBLE>(stationsData[3][i]);
    attrStation[3]->setValue(&longitude);
    nodesStation[id] = chicagoDatabase->newNode("Station", attrStation, 4);
  }

  int numberLinesData = tripsData[0].size-1;
  INT gender;
  STRING type;
  // Avant : STRING date;

  // About bikes
  Result * nodesBike[numberLinesData];
  for (int i = 1 ; i < tripsData[0].size ; i++) {
    id = unserialize<INT>(tripsData[3][i]);
    attrBike[0]->setValue(&id);
    nodesBike[i-1] = chicagoDatabase->newNode("Bike", attrBike, 1);
  }

  // About users
  Result * nodesUser[numberLinesData];
  for (int i = 1 ; i < tripsData[0].size ; i++) {
    gender = unserialize<INT>(tripsData[10][i]);
    type = unserialize<STRING>(tripsData[9][i]);
    attrUser[0]->setValue(&gender);
    attrUser[1]->setValue(&type);
    nodesUser[i-1] = chicagoDatabase->newNode("User", attrUser, 2);
  }

  // About trips
  Result * nodesTrip[numberLinesData];
  for (int i = 1 ; i < tripsData[0].size ; i++) {
    nodesTrip[i-1] = chicagoDatabase->newNode("Trip", NULL, 0);
  }

  // About events
  Result * nodesEvent[2 * numberLinesData];
  for (int i = 1 ; i < tripsData[0].size ; i++) {
    nodesEvent[2*(i-1)] = chicagoDatabase->newNode("Event", NULL, 0);
    nodesEvent[2*(i-1)+1] = chicagoDatabase->newNode("Event", NULL, 0);
  }

  // Edges between the already declared nodes
  for (int i = 1 ; i < tripsData[0].size ; i++) {
    chicagoDatabase->newEdge("uses", nodesTrip[i-1], nodesBike[i-1], NULL, 0);
    chicagoDatabase->newEdge("does", nodesUser[i-1], nodesTrip[i-1], NULL, 0);
    chicagoDatabase->newEdge("departs", nodesTrip[i-1], nodesEvent[2*(i-1)], NULL, 0);
    chicagoDatabase->newEdge("arrives", nodesTrip[i-1], nodesEvent[2*(i-1)+1], NULL, 0);
    chicagoDatabase->newEdge("takesPlace", nodesEvent[2*(i-1)], nodesStation[&tripsData[5][i]], NULL, 0);
    chicagoDatabase->newEdge("takesPlace", nodesEvent[2*(i-1)+1], nodesStation[&tripsData[7][i]], NULL, 0);
    // FAUT-IL VRAIMENT CREER 2 FOIS PLUS D'EVENTS ?
  }

  // Creation of the date and hour trees
  INT nb;
  Result * nodesDay[1][3][31];
  Result * nodesMonth[1][3];
  Result * nodesYear[1];
  for (int i=0; i<1; i++) {
    nb = i+2016;
    attrYear[0]->setValue(&nb);
    nodesYear[i] = chicagoDatabase->newNode("Year", attrYear, 1);
    for (int j=0; j<3; j++) {
      nb = j+1;
      attrMonth[0]->setValue(&nb);
      nodesMonth[i][j] = chicagoDatabase->newNode("Month", attrMonth, 1);
      for (int k=0; k<31; k++) {
	nb = k+1;
	attrDay[0]->setValue(&nb);
	nodesDay[i][j][k] = chicagoDatabase->newNode("Day", attrDay, 1);
	chicagoDatabase->newEdge("isChildDay", nodesMonth[i][j], nodesDay[i][j][k], NULL, 0);
      }
      chicagoDatabase->newEdge("isChildMonth", nodesYear[i], nodesMonth[i][j], NULL, 0);
    }
  }

  Result * nodesMinute[24][60];
  Result * nodesHour[24];
  for (int i=0; i<24; i++) {
    nb = i;
    attrHour[0]->setValue(&nb);
    nodesHour[i] = chicagoDatabase->newNode("Hour", attrHour, 1);
    for (int j=0; i<60; i++) {
      nb = j;
      attrMinute[0]->setValue(&nb);
      nodesMinute[i][j] = chicagoDatabase->newNode("Minute", attrMinute, 1);
      chicagoDatabase->newEdge("isChildMinute", nodesHour[i], nodesMinute[i][j], NULL, 0);
    }
  }

  vector<int> dateInNodes;
  
  // About dates and hours
  for (int i = 1 ; i < tripsData[0].size ; i++) {
    dateInNodes = dateInNodes(tripsData[1][i]);
    chicagoDatabase->newEdge("datesFrom", nodesEvent[2*(i-1)], nodesDay[dateInNodes[2]-2016][dateInNodes[0]-1][dateInNodes[1]-1], NULL, 0);
    chicagoDatabase->newEdge("timesFrom", nodesEvent[2*(i-1)], nodesMinute[dateInNodes[3]][dateInNodes[4]], NULL, 0);
    dateInNodes = dateInNodes(tripsData[2][i]);
    chicagoDatabase->newEdge("datesFrom", nodesEvent[2*(i-1)+1], nodesDay[dateInNodes[2]-2016][dateInNodes[0]-1][dateInNodes[1]-1], NULL, 0);
    chicagoDatabase->newEdge("timesFrom", nodesEvent[2*(i-1)+1], nodesMinute[dateInNodes[3]][dateInNodes[4]], NULL, 0);
  }
}
