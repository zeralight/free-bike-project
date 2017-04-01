#include "entitiesCreation.hpp"

void entitiesCreation(Database * database) {
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
