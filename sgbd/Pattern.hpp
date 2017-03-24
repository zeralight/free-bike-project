#ifndef PATTERN_HPP
#define PATTERN_HPP

#include <string>

#include <tulip/TlpTools.h>
#include <tulip/Graph.h>
#include <tulip/Node.h>
#include <tulip/Edge.h>
#include <tulip/StringProperty.h>
#include <tulip/BooleanProperty.h>

#include "DatabaseImpl.hpp"

class Pattern {
public:  
  virtual void addNode(const std::string &label, const std::string &entityName) =0;
  virtual void addEdge(const std::string &label, const std::string &relationName, const std::string labelSrc, const std::string labelDst) =0;
};


class PatternImpl : public Pattern {
  Graph * g;
  DatabaseImpl * db;
  StringProperty * labelProp;
  StringProperty * typeProp;
  BooleanProperty * checkedProp;

public:
  Pattern(DatabaseImpl * db);
  ~Pattern();

  void addNode(const std::string &label, const std::string &entityName);
  void addEdge(const std::string &label, const std::string &relationName, const std::string labelSrc, const std::string labelDst);

  std::string getType(tlp::node);
  std::string getType(tlp::edge);

  tlp::node getNode(std::string label);
  tlp::edge getEdge(std::string label);

  std::string isChecked(tlp::node);
  std::string isChecked(tlp::edge);

  bool isNode(std::string label);
  bool isEdge(std::string label);
};

  
#endif //PATTERN_HPP
