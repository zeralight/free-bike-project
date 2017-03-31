#include <string>
#include <vector>

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
#define PROP_CHECKED_DB_NAME "ptCheckedDB"

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
    
    db->getEntity(entityName);
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
    
    db->getRelation(relationName);
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
  Entity * e = db->getEntity(name);
  return e;
}


Relation * PatternImpl::getRelation(edge e) const {
  std::string name = typeProp->getEdgeValue(e);
  Relation * r = db->getRelation(name);
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


// Contrainte : pour logique, 
void PatternImpl::match(Graph * gSrc, Graph * gDst) {
  node n;
  
  if (!this->nodes.empty()) {
    auto it = nodes.begin();
    n = (*it).second;
  }
  else
    return;

  this->checkedDBProp = gDst->getLocalProperty<BooleanProperty>(PROP_CHECKED_DB_NAME);
  initProp();
  
  Graph * g = gSrc->addSubGraph("matchTmp");
  Entity * ent = getEntity(n);
  
  std::vector<node> * gNodes = ent->getInstance(gSrc, EQUAL);

  for (auto it = gNodes->begin() ; it != gNodes->end(); it++) {
    if (matchRec(gSrc, g, *it, n)) {
      copyToGraph(g, gDst);
      g->clear();
    }
  }

  delete gNodes;
  delete g;
}


bool PatternImpl::matchRec(Graph * gSrc, Graph * gDst, node nPat, node n) {
  if (isChecked(nPat))
    return true;

  edge ePat, e;
  node nTargetPat, nTarget;
  bool ret = true;
  int nbToMatch;
  
  gDst->addNode(n);
  Iterator<edge> * outEdgesPat = this->g->getOutEdges(nPat);
  Iterator<edge> * outEdges = gSrc->getOutEdges(n);
  
  while(outEdgesPat->hasNext()) {
    ePat = outEdgesPat->next();
    e = matchEdge(ePat, outEdges);
    nTarget = gSrc->opposite(e, n);

    if (e.isValid() && !isCheckedDB(nTarget)) {
      gDst->addNode(nTarget);
      gDst->addEdge(e);

      nTargetPat = this->g->opposite(ePat, nPat);

      if (!matchRec(gSrc, gDst, nTargetPat, nTarget))
	return false;
    }
    else
      return false;
  }

  return true;
}


edge PatternImpl::matchEdge(edge e, Iterator<edge> * potEdges) {
  edge tmp;

  Relation * r = getRelation(e);

  while(potEdges->hasNext()) {
    tmp = potEdges->next();

    if (r->isInstance(tmp) && !isCheckedDB(e))
      return tmp;
  }

  return tmp;
}


void PatternImpl::initProp() {
  this->checkedDBProp->setAllNodeValue(false);
  this->checkedDBProp->setAllEdgeValue(false);
  this->checkedProp->setAllNodeValue(false);
  this->checkedProp->setAllEdgeValue(false);
}


bool PatternImpl::isCheckedDB(node n) {
  return this->checkedDBProp->getNodeValue(n);
}


bool PatternImpl::isCheckedDB(edge e) {
  return this->checkedDBProp->getEdgeValue(e);
}
