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
  DatabaseImpl(std::string name);
  void newEntity(std::string name, const AttrType attributes[], int nAttr);
  const Result * newNode(std::string entityName, const AttrValue values[], int nVal);
  const Result * newNode(const Attr attributes[], int nAttr) ;
  void newRelation(std::string relationName, std::string entitySrc, std::string entityDst, const AttrType attributes[], int nAttr);

  void newEdge(std::string relationName, const Result * src, const Result * dst, const AttrValue values[], int nVal);
  void newEdge(std::string name, const Result * src, const Result * dst, const Attr attributes[], int nAttr);
  int saveDB(std::string path) const;
  Database * loadDB(std::string path, const std::string name);
};

Relation getRelation(Relation * R, int nbR, std::string relationName);
Entity getEntity(Entity * E, int nbE, std::string entityName);

#endif
