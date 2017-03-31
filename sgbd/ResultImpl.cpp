#include <tulip/Graph.h>

#include "DatabaseImpl.hpp"
#include "ResultImpl.hpp"


using namespace tlp;


ResultImpl::ResultImpl(const std::string &name, Graph * g, DatabaseImpl * db): GraphWriteAbstract(g, db) {
  g->setName(name);
}


ResultImpl::~ResultImpl() {}


Iterator<node> * ResultImpl::getNodes() const {
  return this->g->getNodes();
}


Iterator<edge> * ResultImpl::getEdges() const {
  return this->g->getEdges();
}


void ResultImpl::addNode(const node &n) {
  this->g->addNode(n);
}


void ResultImpl::addEdge(const edge &e) {
  this->g->addEdge(e);
}


bool ResultImpl::editNodes(const std::string &entityName, Attribute * attr[], int nAttr) {
  GraphWriteAbstract::editNodes(entityName, attr, nAttr);
}


bool ResultImpl::editEdges(const std::string &relationName, Attribute * attr[], int nAttr) {
  GraphWriteAbstract::editEdges(relationName, attr, nAttr);
}

/* */
Result * ResultImpl::filterNodes(string entityName, Attribute * attr[], int nAttr, int cmpOp){
  Entity * e = this->db->getEntity(entityName);
  std::vector<node> * nodes = e->getInstance(attr, nAttr, oppose(cmpOp));//on récupère les noeuds remplissant les conditions opposées à celles souhaitées pour ensuite les supprimer /!\fonction oppose à implémenter
  this->g->delNodes(*nodes);

  delete nodes;
  return this*;      
}

Result * ResultImpl::filterEdges(string RelationName, Attribute *attr[], int nAttr, int cmpOp){
  Relation * r = this->db->getRelation(relationName);
  std::vector<edge> * edges = r->getInstance(attr, nAttr, oppose(cmpOp));//on récupère les arêtes remplissant les conditions opposées à celles souhaitées pour ensuite les supprimer
  this->g->delEdges(*edges);
  
  delete edges;
  return this*;      
}

/*cmpOp : EQUAL -> = , DIFFERENT -> != */
Result * ResultImpl::where(string label, Attribute * attr[], int nAttr, int cmpOp){
  if(pattern->isNode(label)){
    return filterNodes(label, attr, nAttr, cmpOp);
  }
 else if(pattern->isEdge(label)){
   return filterEdges(label, attr, nAttr, cmpOp);
 }
}

int oppose(int cmpOp){
  if (cmpOp == EQUAL)
    return DIFFERENT;
  return EQUAL;
}
