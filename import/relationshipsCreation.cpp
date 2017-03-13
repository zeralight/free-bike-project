#include "relationshipsCreation.hpp"

void relationshipsCreation() {

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
 
}
