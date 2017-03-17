#include <iostream>
#include <string>
#include <vector>

// Problemes avec les include !!!
#include "../sgbd/Database.hpp"
#include "DBTools.hpp"
#include "Result.hpp"

#include "extraction/extraction.hpp"
#include "dateInNodes.hpp"

using namespace std;

void importChicago() {

  // Database initialization
  initDB();

  // .csv files parsing process
  cout << "Parsing station file... ";
  vector<vector<string> > stationsData = parseCSVFile("Divvy_Stations_2016_Q1Q2.csv")
  cout << "OK" << endl;

  cout << "Parsing trip file... ";
  vector<vector<string> > tripsData = parseCSVFile("Divvy_Trips_2016_Q1.csv");
  cout << "OK" << endl;

  // Creation of the database
  Database * chicagoDatabase = newDB("Chicago_Database");
  cout << "Database created" << endl;
  
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
			     new Attr<INT>("type")};
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

  cout << "Entities created" << endl;

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

  cout << "Relations created" << endl;
  
  // Creation of the nodes and the edges
  // About stations
  Result * nodesStation[2*stationsData[0].size()-1] = {NULL};
  
  INT id;
  STRING name;
  DOUBLE latitude;
  DOUBLE longitude;
  
  for (int i = 1; i < stationsData[0].size() ; i++) {
    id = unserialize<INT>(stationsData[0][i]);
    attrStation[0]->setValue(&id);
    name = unserialize<STRING>(stationsData[1][i]);
    attrStation[1]->setValue(&name);
    latitude = unserialize<DOUBLE>(stationsData[2][i]);
    attrStation[2]->setValue(&latitude);
    longitude = unserialize<DOUBLE>(stationsData[3][i]);
    attrStation[3]->setValue(&longitude);
    nodesStation[id] = chicagoDatabase->newNode("Station", attrStation, 4);
  }

  cout << "Stations saved" << endl;
  
  int numberLinesData = tripsData[0].size()-1;

  // About bikes
  INT gender;
  INT type;

  Result * nodesBike[numberLinesData] = {NULL};
  for (int i = 1 ; i < tripsData[0].size() ; i++) {
    id = unserialize<INT>(tripsData[3][i]);
    attrBike[0]->setValue(&id);
    nodesBike[i-1] = chicagoDatabase->newNode("Bike", attrBike, 1);
  }

  cout << "Bikes saved" << endl;

  // About users
  Result * nodesUser[numberLinesData] = {NULL};
  for (int i = 1 ; i < tripsData[0].size() ; i++) {
    if (tripsData[10][i] == "Male") gender = 1;
    else if (tripsData[10][i] == "Female") gender = 2;
    else gender = 0;

    if (tripsData[9][i] == "Subscriber") type = 1;
    else if (tripsData[9][i] == "Customer") type = 2;
    else type = 0;
    
    attrUser[0]->setValue(&gender);
    attrUser[1]->setValue(&type);
    nodesUser[i-1] = chicagoDatabase->newNode("User", attrUser, 2);
  }

  cout << "Users saved" << endl;
  
  // About trips
  Result * nodesTrip[numberLinesData] = {NULL};
  for (int i = 1 ; i < tripsData[0].size() ; i++) {
    nodesTrip[i-1] = chicagoDatabase->newNode("Trip", NULL, 0);
  }

  cout << "Trips saved" << endl;
  
  // About events
  Result * nodesEvent[2 * numberLinesData] = {NULL};
  for (int i = 1 ; i < tripsData[0].size() ; i++) {
    nodesEvent[2*(i-1)] = chicagoDatabase->newNode("Event", NULL, 0);
    nodesEvent[2*(i-1)+1] = chicagoDatabase->newNode("Event", NULL, 0);
  }

  cout << "Events saved" << endl;

  // Edges between the already declared nodes
  for (int i = 1 ; i < tripsData[0].size() ; i++) {
    int idStart = stoi(tripsData[5][i]);
    int idArrival = stoi(tripsData[7][i]);
    chicagoDatabase->newEdge("uses", nodesTrip[i-1], nodesBike[i-1], NULL, 0);
    chicagoDatabase->newEdge("does", nodesUser[i-1], nodesTrip[i-1], NULL, 0);
    chicagoDatabase->newEdge("departs", nodesTrip[i-1], nodesEvent[2*(i-1)], NULL, 0);
    chicagoDatabase->newEdge("arrives", nodesTrip[i-1], nodesEvent[2*(i-1)+1], NULL, 0);
    chicagoDatabase->newEdge("takesPlace", nodesEvent[2*(i-1)], nodesStation[idStart], NULL, 0);
    chicagoDatabase->newEdge("takesPlace", nodesEvent[2*(i-1)+1], nodesStation[idArrival], NULL, 0);
  }

  cout << "Events relations created" << endl;

  // Creation of the date and hour trees
  INT nb;
  Result * nodesDay[1][12][31] = {NULL};
  Result * nodesMonth[1][12] = {NULL};
  Result * nodesYear[1] = {NULL};
  for (int i=0; i<1; i++) {
    nb = i+2016;
    attrYear[0]->setValue(&nb);
    nodesYear[i] = chicagoDatabase->newNode("Year", attrYear, 1);
    for (int j=0; j<12; j++) {
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

  cout << "Date tree created" << endl;

  Result * nodesMinute[24][60] = {NULL};
  Result * nodesHour[24] = {NULL};
  for (int i=0; i<24; i++) {
    nb = i;
    attrHour[0]->setValue(&nb);
    nodesHour[i] = chicagoDatabase->newNode("Hour", attrHour, 1);
    for (int j=0; j<60; j++) {
      nb = j;
      attrMinute[0]->setValue(&nb);
      nodesMinute[i][j] = chicagoDatabase->newNode("Minute", attrMinute, 1);
      chicagoDatabase->newEdge("isChildMinute", nodesHour[i], nodesMinute[i][j], NULL, 0);
    }
  }

  cout << "Time tree created" << endl;

  vector<int> date;
  
  // About dates and hours
  for (int i = 1 ; i < tripsData[0].size() ; i++) {
    date = dateInNodes(tripsData[1][i]);
    chicagoDatabase->newEdge("datesFrom", nodesEvent[2*(i-1)], nodesDay[date[2]-2016][date[0]-1][date[1]-1], NULL, 0);
    chicagoDatabase->newEdge("timesFrom", nodesEvent[2*(i-1)], nodesMinute[date[3]][date[4]], NULL, 0);
    //cout << i << "/" << tripsData[0].size() << "\t" << date[2]-2016 << "\t" << date[0]-1 << "\t" << date[1]-1 << "\t" << date[3] << "\t" << date[4] <<endl;
    
    date = dateInNodes(tripsData[2][i]);
    //cout << i << "/" << tripsData[0].size() << "\t" << date[2]-2016 << "\t" << date[0]-1 << "\t" << date[1]-1 << "\t" << date[3] << "\t" << date[4] <<endl;
    chicagoDatabase->newEdge("datesFrom", nodesEvent[2*(i-1)+1], nodesDay[date[2]-2016][date[0]-1][date[1]-1], NULL, 0);
    chicagoDatabase->newEdge("timesFrom", nodesEvent[2*(i-1)+1], nodesMinute[date[3]][date[4]], NULL, 0);
  }

  cout << "Dates saved" << endl;

  // delete attributes objects
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

  // delete Result objects
  for (int i = 0 ; i < 2 * stationsData[0].size()-1; i++)
    if (nodesStation[i])
      delResult(nodesStation[i]);

  for (int i = 0 ; i < numberLinesData; i++)
    if (nodesBike[i])
      delResult(nodesBike[i]);
  
  for (int i = 0 ; i < numberLinesData; i++)
    if (nodesUser[i])
      delResult(nodesUser[i]);

  for (int i = 0 ; i < numberLinesData; i++)
    if (nodesTrip[i])
      delResult(nodesTrip[i]);

  for (int i = 0 ; i < 2 * numberLinesData; i++)
    if (nodesEvent[i])
      delResult(nodesEvent[i]);

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
  
  chicagoDatabase->save(".");

  delDB(chicagoDatabase);
}
