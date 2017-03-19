#include "relationshipsCreation.hpp"

void relationshipsCreation(Database * database) {

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
