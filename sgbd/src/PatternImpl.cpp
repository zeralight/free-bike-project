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
#define PROP_LABEL_NAME "ptLabel"
#define PROP_CHECKED_NAME "ptChecked"
#define PROP_ALIAS_NAME "ptAlias"

using namespace tlp;

PatternImpl::PatternImpl(DatabaseImpl * db) {
  this->db = (DatabaseImpl *) db;
  this->g = newGraph();
  this->labelProp = this->g->getLocalProperty<StringProperty>(PROP_LABEL_NAME);
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

  this->labelProp->setNodeValue(n, label);
  this->typeProp->setNodeValue(n, entityName);
  this->checkedProp->setNodeValue(n, false);
}


void PatternImpl::addEdge(const std::string &label, const std::string &relationName, const std::string labelSrc, const std::string labelDst) {
  edge e;

  try {
    // test for the existance of the labels (dirty but getNode displays an error message)
    this->getNode(labelSrc);
    this->getNode(labelDst);
    
    if (!isAvailable(label))
      throw std::string("ERROR: Label '" + label + "' already exists");
    
    Relation * rel = db->getRelation(relationName);
    if (!rel->verify(this->getEntity(labelSrc), this->getEntity(labelDst)))
      throw std::string("ERROR: Wrong type for label '" + labelSrc + "' and/or '" + labelDst + "', here is the definition of the relation : " + rel->debug(false));
  }
  catch (std::string &errMessage){
    std::cerr << errMessage << std::endl;
    return;
  }

  e = this->g->addEdge(nodes[labelSrc], nodes[labelDst]);
  edges[label] = e;

  this->labelProp->setEdgeValue(e, label);
  this->typeProp->setEdgeValue(e, relationName);
  this->checkedProp->setEdgeValue(e, false);
}


Entity * PatternImpl::getEntity(node n) const {
  std::string name = typeProp->getNodeValue(n);
  Entity * e = db->getEntity(name);
  return e;
}


Entity * PatternImpl::getEntity(std::string label) const {
  return getEntity(getNode(label));
}


Relation * PatternImpl::getRelation(edge e) const {
  std::string name = typeProp->getEdgeValue(e);
  Relation * r = db->getRelation(name);
  return r;
}


Relation * PatternImpl::getRelation(std::string label) const {
  return getRelation(getEdge(label));
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


// Contrainte : pour logique, gDst doit etre sous-graphe du graphe gSrc
// gSrc doit etre 
void PatternImpl::match(Graph * gDst) {
  node n;
  Graph * gSrc = this->db->getGraph();
  
  if (this->nodes.empty())
    return;

  auto it = nodes.begin();
  n = (*it).second;
 
  this->aliasProp = gDst->getLocalProperty<StringProperty>(PROP_ALIAS_NAME);
  initProp();
  
  Graph * g = gSrc->addSubGraph("matchTmp");
  Entity * ent = getEntity(n);
  
  std::vector<node> * gNodes = ent->getInstance(NULL, 0, EQUAL);

  for (auto it = gNodes->begin() ; it != gNodes->end(); it++) {
    this->checkedProp->setAllNodeValue(false);
    this->checkedProp->setAllEdgeValue(false);

    g->addNode(*it);
    std::cout << ent->getName() << ": " << ent->getGraph()->getProperty<IntegerProperty>("id")->getNodeValue(*it) << std::endl;
    
    if (matchRec(g, n, *it)) {
      std::cout << "\x1b[33;1mmatch\x1b[0m" << std::endl;
      gDst->addNodes(g->getNodes());
      gDst->addEdges(g->getEdges());
    }

    g->clear();
  }

  delete gNodes;
  gSrc->delSubGraph(g);
}


bool PatternImpl::matchRec(Graph * gDst, node nPat, node n) {
  if (isChecked(nPat))
    return true;

  this->checkedProp->setNodeValue(nPat, true);
  this->aliasProp->setNodeValue(n, labelProp->getNodeValue(nPat));
  
  Graph * gSrc = this->db->getGraph();
  edge ePat, e;
  node nTargetPat, nTarget;
  Iterator<edge> * adjEdgesPat = this->g->getInOutEdges(nPat);
  Iterator<edge> * adjEdges = gSrc->getInOutEdges(n);
  
  while(adjEdgesPat->hasNext()) {
    ePat = adjEdgesPat->next();

    if (isChecked(ePat))
      continue;
    
    do {
      e = matchEdge(ePat, adjEdges, gDst);
      
      if (!e.isValid()) {
	std::cout << "\x1b[31;1mno edge\x1b[0m" << std::endl;
	return false;
      }
      
      nTarget = gSrc->opposite(e, n);      
      nTargetPat = this->g->opposite(ePat, nPat);
    } while (!matchNode(nTargetPat, nTarget, gDst));
    
    gDst->addNode(nTarget);
    gDst->addEdge(e);
    
    this->checkedProp->setEdgeValue(ePat, true);
    this->aliasProp->setEdgeValue(e, labelProp->getEdgeValue(ePat));
    
    if (!matchRec(gDst, nTargetPat, nTarget)) {
      std::cout << "\x1b[31;1mnon match\x1b[0m" << std::endl;
      return false;
    }
  }
  
  return true;
}


edge PatternImpl::matchEdge(edge ePat, Iterator<edge> * potEdges, Graph * gDst) {
  edge e;
  Relation * r = this->getRelation(ePat);

  while(potEdges->hasNext()) {
    e = potEdges->next();
    
    // Check that e has the same type as ePat
    if (r->isInstance(e) && !gDst->isElement(e))
      return e;
  }

  return edge();
}


bool PatternImpl::matchNode(node nPat, node n, Graph * gDst) {
  std::string nLabel = this->labelProp->getNodeValue(nPat);

  // Check that, if n already exists in gDst, n has the same label as nPat
  if ((gDst->isElement(n) &&
       nLabel != aliasProp->getNodeValue(n)))
    return false;
  /*    
  if (!gDst->isElement(n))
    this->aliasProp->setNodeValue(n, nLabel);
  */
  
  return true;
}


void PatternImpl::initProp() {
  std::string emptyStr;
  this->aliasProp->setAllNodeValue(emptyStr);
  this->aliasProp->setAllEdgeValue(emptyStr);
  this->checkedProp->setAllNodeValue(false);
  this->checkedProp->setAllEdgeValue(false);
}


DatabaseImpl * PatternImpl::getDB() {
  return this->db;
}


Graph * PatternImpl::getGraph() {
  return this->g;
}
