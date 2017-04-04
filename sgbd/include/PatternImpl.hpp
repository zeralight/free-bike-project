#ifndef PATTERN_HPP
#define PATTERN_HPP

#include <string>
#include <unordered_map>

#include <tulip/TlpTools.h>
#include <tulip/Graph.h>
#include <tulip/Node.h>
#include <tulip/Edge.h>
#include <tulip/StringProperty.h>
#include <tulip/BooleanProperty.h>

#include "Database.hpp"
#include "DatabaseImpl.hpp"
#include "Entity.hpp"
#include "Relation.hpp"
#include "Pattern.hpp"

using namespace tlp;

class PatternImpl : public Pattern {
  Graph * g;
  DatabaseImpl * db;
  std::unordered_map<std::string, node> nodes;
  std::unordered_map<std::string, edge> edges;
  StringProperty * typeProp;
  BooleanProperty * checkedProp;
  StringProperty * labelProp;
  StringProperty * aliasProp;

public:
  PatternImpl(DatabaseImpl * db);
  ~PatternImpl();

  void addNode(const std::string &label, const std::string &entityName);
  void addEdge(const std::string &label, const std::string &relationName, const std::string labelSrc, const std::string labelDst);

  Entity * getEntity(node n) const;
  Entity * getEntity(std::string label) const;
  Relation * getRelation(edge e) const;
  Relation * getRelation(std::string label) const;

  node getNode(std::string label) const;
  edge getEdge(std::string label) const; 

  bool isChecked(node n) const;
  bool isChecked(edge e) const;

  /*
   * bool isCheckedDB(node n);
   * bool isCheckedDB(edge e);  
   */
  
  bool isNode(std::string label) const;
  bool isEdge(std::string label) const;

  bool isAvailable(std::string label) const;

  void match(Graph * gDst);
  bool matchRec(Graph * gDst, node nPat, node n);

  edge matchEdge(edge ePat, Iterator<edge> * potEdges, Graph * gDst);
  bool matchNode(node nPat, node n, Graph * gDst);
  void initProp();

  DatabaseImpl * getDB();
  Graph * getGraph();
};
  
#endif //PATTERN_HPP
