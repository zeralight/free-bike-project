#include "Database.hpp"
#include "Result.hpp"
#include "Pattern.hpp"

#define DATABASE_PATH "./chicagoDatabase.db"

int main () {
  initDB();

  // Loading a database on which we will make requests
  Database * db = newDB("");
  db->load(DATABASE_PATH);

  // Creation of a Pattern to match
  Pattern * p = newPattern(db);

  p->addNode("T", "Trip");
  p->addNode("E", "Event");
  p->addNode("S", "Station");

  p->addEdge("depart", "departs", "T", "E");
  p->addEdge("in", "takesPlace", "E", "S");

  // Request on db 
  
  delDB(db);
}
