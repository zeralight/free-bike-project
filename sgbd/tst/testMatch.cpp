#include <vector>

#include "Database.hpp"
#include "DatabaseImpl.hpp"
#include "Result.hpp"
#include "ResultImpl.hpp"
#include "Pattern.hpp"

#include "tstMacros.h"

#define DATABASE_NAME "chicagoDatabase.db"

using namespace tlp;

INIT_OUTPATH("testMatch");
INIT_INPATH("testMatch");

int main () {
  CREATE_OUTPATH;
  
  initDB();
  
  // Loading a database on which we will make requests
  Database * db = newDB("");
  db->load(S_INPATH(DATABASE_NAME));

  // Creation of a Pattern to match
  Pattern * p = newPattern(db);

  p->addNode("T", "Trip");
  p->addNode("E", "Event");
  p->addNode("S", "Station");

  p->addEdge("depart", "departs", "T", "E");
  p->addEdge("in", "takesPlace", "E", "S");

  // Request on db
  Result * res;

  res = db->match(p);

  // Save the request's result
  Graph * sav = ((ResultImpl *) res)->getGraph();
  saveGraph(sav, S_OUTPATH("testMatch.tlp"));

  // Quick test for getAttr function
  DatabaseImpl * dbi = ((DatabaseImpl *) db);
  Entity * e = dbi->getEntity("Station");
  std::vector<node> * stations = e->getInstance(sav, EQUAL);

  std::cout << "\x1b[1mStations :\x1b[0m" << stations->size() << std::endl; 
  for (auto it = stations->begin() ; it != stations->end() ; it++) {
    Attribute * attr;
    INT id;
    attr = e->getAttr("id", *it);
    attr->getValue(&id);
    std::cout << "id :\t" << id << std::endl;
  }
  
  delPattern(p);
  delResult(res);
  delDB(db);
}
