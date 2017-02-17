#ifndef DATABASEIMPL_HPP
#define DATABASEIMPL_HPP

#include <string>
#include <tulip/Node.h>
#include <tulip/Edge.h>

#include "DBTools.hpp"
#include "Database.hpp"
//#include "Result.hpp"
#include "Entity.hpp"
#include "Relation.hpp"

using namespace tlp;

class Result;

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
  std::string name;
  Entity * E;
  int nbE;
  Relation * R;
  int nbR;

 public:
  DatabaseImpl(const std::string &name);
  ~DatabaseImpl();
  void newEntity(const std::string &name, const Attribute * const attributes[], int nAttr);
  Result * newNode(const std::string &entityName, Attribute * attributes[], int nVal);
  /*const Result * newNode(const Attribute * const attributes[], int nAttr) ;*/
  void newRelation(const std::string &relationName, const std::string &entitySrc, const std::string &entityDst, const Attribute * const attributes[], int nAttr);
  void newEdge(const std::string &relationName, const Result * src, const Result * dst, const Attribute * const attributes[], int nVal);
  /*void newEdge(const std::string name, const Result * src, const Result * dst, const Attribute * const attributes[], int nAttr);*/
  int saveDB(const std::string &path) const;
  Database * loadDB(const char * path, const std::string &name);
};

Relation getRelation(Relation * R, int nbR, const std::string &relationName);
Entity getEntity(Entity * E, int nbE, const std::string &entityName);
int loadE(Entity * E, const char * path );
int loadR(Relation * R, const char * path );
void saveE(Entity * E, int nbE, const char * path );
void saveR(Relation * R, int nbR, const char *path );

#endif
