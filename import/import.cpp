#include <iostream>
#include <string>
#include <vector>

#include "Database.hpp"
#include "DBTools.hpp"
#include "Result.hpp"

#include "extraction.hpp"
#include "dateInNodes.hpp"

using namespace std;

void importChicago() { // ON CHANGE LE PROTOTYPE OU PAS ? CAR A LA FIN, delDB !
  
  // Database initialization
  initDB();
  
  // .csv files parsing process
  cout << "Parsing station file... ";
  vector<vector<string> > stationsData = parseCSVFile("Divvy_Stations_2016_Q1Q2.csv");
  cout << "OK" << endl;
  
  cout << "Parsing trip file... ";
  vector<vector<string> > tripsData = parseCSVFile("Divvy_Trips_2016_Q1.csv");
  cout << "OK" << endl;
  
  // Creation of the database
  Database * chicagoDatabase = newDB("Chicago_Database");
  cout << "Database created" << endl;
  
  // Creation of the entities
  entitiesCreation(chicagoDatabase);
  cout << "Entities created" << endl;
  
  // Creation of the relationships
  relationshipsCreation(chicagoDatabase);
  cout << "Relations created" << endl;
  
  // Creation of the nodes and the edges
  /// About stations
  
  //// Needed variables
  INT id;
  STRING name;
  DOUBLE latitude;
  DOUBLE longitude;
  
  //// Gives the maximum id to declare the array of nodes correctly
  int max = -1;
  for (int i = 1; i < stationsData[0].size() ; i++) {
    if (id = unserialize<INT>(stationsData[0][i]) > max)
      max = id;
  }
  Result * nodesStation[max+1] = {NULL};
  
  //// Nodes initialization
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
  
  //// Delete Attribute object
  delAttr(attrStation, 4);
  
  cout << "Stations saved" << endl;
  
  /// About dates and time
  
  //// Needed variable
  INT nb;
  
  //// Dates nodes creation
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
  
  //// Time nodes creation
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
  
  
  /// About data
  
  //// Needed variables
  int numberLinesData = tripsData[0].size()-1;
  INT gender;
  INT type;
  
  Attribute * attrBike[1] = {new Attr<INT>("id")}; // UNIQUE
  Attribute * attrUser[1] = {new Attr<INT>("value")};
  
  Result * nodeBike = NULL;
  Result * nodeUser = NULL;
  Result * nodeTrip = NULL;
  Result * nodesEvent[2] = {NULL};

  vector<int> date;
  
  //// Nodes and edges creation loop
  for (int i = 1 ; i < tripsData[0].size() ; i++) {
    
    ///// Bike node 
    id = unserialize<INT>(tripsData[3][i]);
    attrBike[0]->setValue(&id);
    nodeBike = chicagoDatabase->newNode("Bike", attrBike, 1);
    
    ///// User node
    if (tripsData[10][i] == "Male") gender = 1;
    else if (tripsData[10][i] == "Female") gender = 2;
    else gender = 0;
    
    if (tripsData[9][i] == "Subscriber") type = 1;
    else if (tripsData[9][i] == "Customer") type = 2;
    else type = 0;
    
    attrUser[0]->setValue(&gender);
    attrUser[1]->setValue(&type);
    nodeUser = chicagoDatabase->newNode("User", attrUser, 2);
    
    ///// Trip node
    nodeTrip = chicagoDatabase->newNode("Trip", NULL, 0);
    
    ///// Event nodes
    nodesEvent[0] = chicagoDatabase->newNode("Event", NULL, 0);
    nodesEvent[1] = chicagoDatabase->newNode("Event", NULL, 0);
    
    ///// Edges
    chicagoDatabase->newEdge("uses", nodeTrip, nodeBike, NULL, 0);
    
    chicagoDatabase->newEdge("does", nodeUser, nodeTrip, NULL, 0);
    
    chicagoDatabase->newEdge("departs", nodeTrip, nodesEvent[0], NULL, 0);
    
    chicagoDatabase->newEdge("arrives", nodeTrip, nodesEvent[1], NULL, 0);
    
    int idStart = stoi(tripsData[5][i]);
    int idArrival = stoi(tripsData[7][i]);
    chicagoDatabase->newEdge("takesPlace", nodesEvent[0], nodesStation[idStart], NULL, 0);
    chicagoDatabase->newEdge("takesPlace", nodesEvent[1], nodesStation[idArrival], NULL, 0);
    
    date = dateInNodes(tripsData[1][i]);
    chicagoDatabase->newEdge("datesFrom", nodesEvent[0], nodesDay[date[2]-2016][date[0]-1][date[1]-1], NULL, 0);
    chicagoDatabase->newEdge("timesFrom", nodesEvent[0], nodesMinute[date[3]][date[4]], NULL, 0);
    date = dateInNodes(tripsData[2][i]);
    chicagoDatabase->newEdge("datesFrom", nodesEvent[1], nodesDay[date[2]-2016][date[0]-1][date[1]-1], NULL, 0);
    chicagoDatabase->newEdge("timesFrom", nodesEvent[1], nodesMinute[date[3]][date[4]], NULL, 0);
  }
  
  // Delete Attribute objects
  delAttr(attrBike, 1);
  delAttr(attrUser, 1);
  
  // Delete Result objects
  for (int i = 0 ; i < max+1; i++)
    if (nodesStation[i])
      delResult(nodesStation[i]);

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

  // ?
  chicagoDatabase->save(".");
 
  // ?
  delDB(chicagoDatabase);

}
  
