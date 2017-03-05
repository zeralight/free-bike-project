#include <tulip/TlpTools.h>
#include <tulip/Node.h>
#include <tulip/Edge.h>

#include "DBTools.hpp"
#include "Database.hpp"
//#include "Result.hpp"
#include "DatabaseImpl.hpp"

Database * newDB(const std::string &name) {
  Database * db = new DatabaseImpl(name);
  return db;
}


void delDB(Database * db) {
  delete ((DatabaseImpl *) db);
}


void initDB() {
  //initialize the Tulip lib
  tlp::initTulipLib();
}
