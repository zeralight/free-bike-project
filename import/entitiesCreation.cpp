#include "entitiesCreation.hpp"

void entitiesCreation() {
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
  
  // Supprimé :
  // Attribute * attrDate[1] = {new Attr<STRING>("value")};
  // chicagoDatabase->newEntity("Date", attrDate, 1);

}
