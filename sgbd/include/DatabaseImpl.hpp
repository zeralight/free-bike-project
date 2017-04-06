#ifndef DATABASEIMPL_HPP
#define DATABASEIMPL_HPP

#include <string>
#include <unordered_map>

#include <tulip/Node.h>
#include <tulip/Edge.h>

#include "DBTools.hpp"
#include "GraphWrite.hpp"
#include "Database.hpp"
#include "Result.hpp"
#include "Entity.hpp"
#include "Relation.hpp"

using namespace tlp;

/**
 * @brief This class is the implementation of the Database Management System described in <Database.hpp>.
 *
 * Remark : The file <DBTools.hpp> must be inserted in order to use certain data types like : Attr.
 *          See this file for more details on its use.
 *
 **/
class DatabaseImpl: public Database, public GraphWriteAbstract {
private:
  Graph * gRelations;
  Graph * gEntities;
  Graph * gResults;
  std::string name;
  std::unordered_map<std::string, Entity *> entities;
  std::unordered_map<std::string, Relation *> relations;
  
public:
  DatabaseImpl(const std::string &name);
  ~DatabaseImpl();
  void newEntity(const std::string &name, const Attribute * const attributes[], int nAttr);
  void newRelation(const std::string &name, const std::string &entitySrc, const std::string &entityDst, const Attribute * const attr[], int nAttr);
  Result * newNode(const std::string &entityName, Attribute * attr[], int nVal);
  void newEdge(const std::string &relationName, const Result * src, const Result * dst, Attribute * attr[], int nAttr);
  bool editNodes(const std::string &entityName, Attribute * attr[], int nAttr);  
  bool editEdges(const std::string &relationName, Attribute * attr[], int nAttr);
  void load(const std::string &path);
  void save(const std::string &path) const;

  Relation * getRelation(const std::string &name);
  Entity * getEntity(const std::string &name);

  bool isEntity(const std::string &name) const;
  bool isRelation(const std::string &name) const;

  Result * match(Pattern * p);

  Graph * newGraphResult(const std::string &name);

private:
  void loadEntities(const std::string &path);
  void loadRelations(const std::string &path);

  void saveEntities(const std::string &path) const;
  void saveRelations(const std::string &path) const;
};

#endif
