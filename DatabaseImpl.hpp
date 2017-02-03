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


class DatabaseImpl: public Database {
 private:
  Graph * G;
  std::string name;
  Entity * E[];
  int nbE;
  Relation * R[];
  int nbR;

 public:
  DatabaseImpl(std::string name);
  void newEntity(std::string name, const AttrType attributes[], int nAttr);
  const Result * newNode(std::string entityName, const AttrValue values[], int nVal);
  const Result * newNode(const Attr attributes[], int nAttr) ;
  void newRelation(std::string relationName, std::string entitySrc, std::string entityDst, const AttrType attributes[], int nAttr);
  void newEdge(std::string relationName, const Result src, const Result dst, const AttrValue values[], int nVal);
  void newEdge(std::string name, const Result src, const Result dst, const Attr attributes[], int nAttr);
  int saveDB(std::string path) const;
  Database * loadDB(std::string path) const;
};

#endif
