#ifndef DATABASEIMPL_HPP
#define DATABASEIMPL_HPP

#include <string>
#include <tulip/Node.h>
#include <tulip/Edge.h>

#include "DBTools.hpp"
#include "Database.hpp"
#include "Result.hpp"
#include "Entity.hpp"
#include "Relation.hpp"

using namespace tlp;

/**
 * @brief This class is the implementation of the Database Management System describ in <Database.cpp>.
 *
 * Remark : The file <DBTools.hpp> must be inserted in order to use certain data types like : Attr, AttrType and AttrValue.
 *          See this file for more details on its use.
 *
 **/
class DatabaseImpl: public Database {
 private:
  Graph * G;
  std::string  name;
  Entity * E;
  int nbE;
  Relation * R;
  int nbR;

 public:
  DatabaseImpl(std::string name);
  ~DatabaseImpl();
  void newEntity(std::string name, const Attribute * const attributes[], int nAttr);
  Result * newNode(std::string entityName, Attribute * attributes[], int nVal);
  /*const Result * newNode(const Attribute * const attributes[], int nAttr) ;*/
  void newRelation(std::string relationName, std::string entitySrc, std::string entityDst, const Attribute * const attributes[], int nAttr);
  void newEdge(std::string relationName, const Result * src, const Result * dst, const Attribute * const attributes[], int nVal);
  /*void newEdge(std::string name, const Result * src, const Result * dst, const Attribute * const attributes[], int nAttr);*/
  int saveDB(std::string path) const;
  Database * loadDB(std::string path, const std::string name);
};

Relation getRelation(Relation * R, int nbR, std::string relationName);
Entity getEntity(Entity * E, int nbE, std::string entityName);
int loadE(Entity * E, char * path );
int loadR(Relation * R, char * path );
void saveE(Entity * E, int nbE, char * path );
void saveR(Relation * R, int nbR, char *path );

#endif
