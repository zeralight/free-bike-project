#include <tulip/TlpTools.h>
#include <tulip/Node.h>
#include <tulip/Edge.h>

#include "DBTools.hpp"
#include "Database.hpp"
#include "Result.hpp"
#include "DatabaseImpl"

Database * newDB(std::string name){
  Database * D = new DatabaseImpl(name);
  return D;
}

void delDB(Database * db){
  //pas de destructeur pour DatabaseImpl, necessaire ?
}
