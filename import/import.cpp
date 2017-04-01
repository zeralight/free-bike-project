#include <iostream>
#include <string>
#include <vector>

#include "Database.hpp"
#include "DBTools.hpp"
#include "Result.hpp"

#include "import.hpp"
#include "extraction.hpp"
#include "dateInNodes.hpp"
#include "entitiesCreation.hpp"
#include "relationshipsCreation.hpp"

#ifndef PATH_TO_FILES_DIRECTORY
  #define PATH_TO_FILES_DIRECTORY "./"
#endif
#ifndef PATH_FOR_DB
  #define PATH_FOR_DB "."
#endif
#ifndef DB_NAME
  #define DB_NAME "chicagoDatabase"
#endif

using namespace std;

void importChicago() { // ON CHANGE LE PROTOTYPE OU PAS ? CAR A LA FIN, delDB !
  
  // Database initialization
  initDB();
  
  // .csv files parsing process
  cout << "Parsing station file... ";
  vector<vector<string> > stationsData = parseCSVFile(string(PATH_TO_FILES_DIRECTORY)+"Divvy_Stations_2016_Q1Q2.csv");
  cout << "OK" << endl;
  
  cout << "Parsing trip file... ";
  vector<vector<string> > tripsData = parseCSVFile(string(PATH_TO_FILES_DIRECTORY)+"Divvy_Trips_2016_Q1.csv");
  cout << "OK" << endl;
  
  // Creation of the database
  Database * database = newDB(DB_NAME);
  cout << "Database created" << endl;
  
  // Creation of the entities
  entitiesCreation(database);
  cout << "Entities created" << endl;
  
  // Creation of the relationships
  relationshipsCreation(database);
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
    if ((id = unserialize<INT>(stationsData[0][i])) > max)
      max = id;
  }
  Result * nodesStation[max+1] = {NULL};
  
  Attribute * attrStation[4] = {new Attr<INT>("id"),
				new Attr<STRING>("name"),
				new Attr<DOUBLE>("latitude"),
				new Attr<DOUBLE>("longitude")};
  
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
    nodesStation[id] = database->newNode("Station", attrStation, 4);
  }
  
  //// Delete Attribute object
  delAttr(attrStation, 4);
  
  cout << "Stations saved" << endl;
  
  /// About dates and time
  
  //// Needed variables
  INT nb;
  
  Attribute * attrYear[1] = {new Attr<INT>("value")};
  Attribute * attrMonth[1] = {new Attr<INT>("value")};
  Attribute * attrDay[1] = {new Attr<INT>("value")};
  
  //// Dates nodes creation
  Result * nodesDay[1][12][31] = {NULL};
  Result * nodesMonth[1][12] = {NULL};
  Result * nodesYear[1] = {NULL};
  
  for (int i=0; i<1; i++) {
    nb = i+2016;
    attrYear[0]->setValue(&nb);
    nodesYear[i] = database->newNode("Year", attrYear, 1);
    for (int j=0; j<12; j++) {
      nb = j+1;
      attrMonth[0]->setValue(&nb);
      nodesMonth[i][j] = database->newNode("Month", attrMonth, 1);
      for (int k=0; k<31; k++) {
	nb = k+1;
	attrDay[0]->setValue(&nb);
	nodesDay[i][j][k] = database->newNode("Day", attrDay, 1);
	database->newEdge("isChildDay", nodesMonth[i][j], nodesDay[i][j][k], NULL, 0);
      }
      database->newEdge("isChildMonth", nodesYear[i], nodesMonth[i][j], NULL, 0);
    }
  }
  
  cout << "Date tree created" << endl;
  
  //// Time nodes creation
  Result * nodesMinute[24][60] = {NULL};
  Result * nodesHour[24] = {NULL};

  Attribute * attrMinute[1] = {new Attr<INT>("value")};
  Attribute * attrHour[1] = {new Attr<INT>("value")};
  
  for (int i=0; i<24; i++) {
    nb = i;
    attrHour[0]->setValue(&nb);
    nodesHour[i] = database->newNode("Hour", attrHour, 1);
    for (int j=0; j<60; j++) {
      nb = j;
      attrMinute[0]->setValue(&nb);
      nodesMinute[i][j] = database->newNode("Minute", attrMinute, 1);
      database->newEdge("isChildMinute", nodesHour[i], nodesMinute[i][j], NULL, 0);
    }
  }
  
  cout << "Time tree created" << endl;
  
  
  /// About data
  
  //// Needed variables
  int numberLinesData = tripsData[0].size()-1;
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
  for (int i = 1 ; i < tripsData[0].size() ; i++) {
    
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

  // ?
  database->save(PATH_FOR_DB);
 
  // ?
  delDB(database);
}
  
