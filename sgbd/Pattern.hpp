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

using namespace tlp;

class Pattern {
public:  
  virtual void addNode(const std::string &label, const std::string &entityName) =0;
  virtual void addEdge(const std::string &label, const std::string &relationName, const std::string labelSrc, const std::string labelDst) =0;
  virtual void debug() const =0;
};


class PatternImpl : public Pattern {
  Graph * g;
  DatabaseImpl * db;
  std::unordered_map<std::string, node> nodes;
  std::unordered_map<std::string, edge> edges;
  StringProperty * typeProp;
  BooleanProperty * checkedProp;

public:
  PatternImpl(DatabaseImpl * db);
  ~PatternImpl();

  void addNode(const std::string &label, const std::string &entityName);
  void addEdge(const std::string &label, const std::string &relationName, const std::string labelSrc, const std::string labelDst);

  Entity * getEntity(node n) const;
  Relation * getRelation(edge e) const;

  node getNode(std::string label) const;
  edge getEdge(std::string label) const; 

  bool isChecked(node n) const;
  bool isChecked(edge e) const;

  bool isNode(std::string label) const;
  bool isEdge(std::string label) const;

  bool isAvailable(std::string label) const;
  
  void debug() const;
};

Pattern * newPattern(Database * db);
void delPattern(Pattern * p);
  
#endif //PATTERN_HPP
