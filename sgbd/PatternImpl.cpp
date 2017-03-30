#include <string>

#include <tulip/TlpTools.h>
#include <tulip/Graph.h>
#include <tulip/StringProperty.h>
#include <tulip/BooleanProperty.h>

#include "PatternImpl.hpp"
#include "DatabaseImpl.hpp"


// pas sensé etre visible ?
#define PROP_TYPE_NAME "ptType"
//#define PROP_LABEL_NAME "ptLabel"
#define PROP_CHECKED_NAME "ptChecked"

using namespace tlp;

PatternImpl::PatternImpl(DatabaseImpl * db) {
  this->db = (DatabaseImpl *) db;
  this->g = newGraph();
  //this->labelProp = this->g->addLocalProperty<StringProperty>(PROP_TYPE_NAME);
  this->typeProp = this->g->getLocalProperty<StringProperty>(PROP_TYPE_NAME);
  this->checkedProp = this->g->getLocalProperty<BooleanProperty>(PROP_CHECKED_NAME);
}


PatternImpl::~PatternImpl() {
  delete this->g;
}


void PatternImpl::addNode(const std::string &label, const std::string &entityName) {
  node n;

  try {
    if (!isAvailable(label))
      throw std::string("ERROR: Label '" + label + "' already exists");
  }
  catch (std::string &errMessage){
    std::cerr << errMessage << std::endl;
    return;
  }
  
  n = this->g->addNode();
  nodes[label] = n;
    
  this->typeProp->setNodeValue(n, entityName);
  this->checkedProp->setNodeValue(n, false);
}


void PatternImpl::addEdge(const std::string &label, const std::string &relationName, const std::string labelSrc, const std::string labelDst) {
  edge e;

  try {
    node nSrc = this->getNode(labelSrc);
    node nDst = this->getNode(labelDst);
    
    if (!isAvailable(label))
      throw std::string("ERROR: Label '" + label + "' already exists");
  }
  catch (std::string &errMessage){
    std::cerr << errMessage << std::endl;
    return;
  }

  e = this->g->addEdge(nodes[labelSrc], nodes[labelDst]);
  edges[label] = e;
  
  this->typeProp->setEdgeValue(e, relationName);
  this->checkedProp->setEdgeValue(e, false);
}


Entity * PatternImpl::getEntity(node n) const {
  std::string name = typeProp->getNodeValue(n);
  Entity * e = NULL;
  
  try {
    e = db->getEntity(name);
  }
  catch (std::string &errMessage) {
    std::cerr << errMessage << std::endl;
  }

  return e;
}


Relation * PatternImpl::getRelation(edge e) const {
  std::string name = typeProp->getEdgeValue(e);
  Relation * r = NULL;
  
  try {
    r = db->getRelation(name);
  }
  catch (std::string &errMessage) {
    std::cerr << errMessage << std::endl;
  }

  return r;
}


node PatternImpl::getNode(std::string label) const {
  auto it = nodes.find(label);
  if (it == nodes.end())
    throw std::string("ERROR: Label '" + label + "' doesn't exist");
  
  return (*it).second;
}


edge PatternImpl::getEdge(std::string label) const {
  auto it = edges.find(label);
  if (it == edges.end())
    throw std::string("ERROR: Label '" + label + "' doesn't exist");

  return (*it).second;
}


bool PatternImpl::isChecked(node n) const {
  return checkedProp->getNodeValue(n);
}


bool PatternImpl::isChecked(edge e) const {
  return checkedProp->getEdgeValue(e);
}


bool PatternImpl::isNode(std::string label) const {
  auto it = nodes.find(label);
  if (it == nodes.end())
    return false;

  return true;
}


bool PatternImpl::isEdge(std::string label) const {
  auto it = edges.find(label);
  if (it == edges.end())
    return false;

  return true;
}


bool PatternImpl::isAvailable(std::string label) const {
  return (nodes.find(label) == nodes.end() &&
	  edges.find(label) == edges.end());
}


void PatternImpl::debug() const {
  saveGraph(this->g, "testPattern.tlp");
}
