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

#include "DatabaseImpl.hpp"

using namespace tlp;

class Pattern {
public:  
  virtual void addNode(const std::string &label, const std::string &entityName) =0;
  virtual void addEdge(const std::string &label, const std::string &relationName, const std::string labelSrc, const std::string labelDst) =0;
};


class PatternImpl : public Pattern {
  Graph * g;
  DatabaseImpl * db;
  std::unordered_map<std::string, node> nodes;
  std::unordered_map<std::string, edge> edges;
  StringProperty * typeProp;
  BooleanProperty * checkedProp;

public:
  Pattern(DatabaseImpl * db);
  ~Pattern();

  void addNode(const std::string &label, const std::string &entityName);
  void addEdge(const std::string &label, const std::string &relationName, const std::string labelSrc, const std::string labelDst);

  std::string getEntity(node n);
  std::string getRelation(edge e);

  node getNode(std::string label);
  edge getEdge(std::string label);

  std::string isChecked(node n);
  std::string isChecked(edge e);

  bool isNode(std::string label);
  bool isEdge(std::string label);
};

  
#endif //PATTERN_HPP
