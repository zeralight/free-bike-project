#include <tulip/Graph.h>

#include "DatabaseImpl.hpp"
#include "PatternImpl.hpp"
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
  return GraphWriteAbstract::editNodes(entityName, attr, nAttr);
}


bool ResultImpl::editEdges(const std::string &relationName, Attribute * attr[], int nAttr) {
  return GraphWriteAbstract::editEdges(relationName, attr, nAttr);
}


/* */
void ResultImpl::filterNodes(const std::string &entityName, Attribute * attr[], int nAttr, int cmpOp) {
  Entity * e = this->db->getEntity(entityName);
  //on récupère les noeuds remplissant les conditions opposées à celles souhaitées pour ensuite les supprimer
  std::vector<node> * nodes = e->getInstance(this->g, attr, nAttr, oppose(cmpOp));
  this->g->delNodes(*nodes);
  
  delete nodes;
}


void ResultImpl::filterEdges(const std::string &relationName, Attribute *attr[], int nAttr, int cmpOp) {
  Relation * r = this->db->getRelation(relationName);
  //on récupère les arêtes remplissant les conditions opposées à celles souhaitées pour ensuite les supprimer
  std::vector<edge> * edges = r->getInstance(this->g, attr, nAttr, oppose(cmpOp));
  this->g->delEdges(*edges);
  
  delete edges;
}


void ResultImpl::filterNodesPat(const std::string &label, Attribute * attr[], int nAttr, int cmpOp) {
  //on récupère les noeuds remplissant les conditions opposées à celles souhaitées pour ensuite les supprimer
  std::vector<node> * nodes = this->pattern->getNodes(label, this->g, attr, nAttr, oppose(cmpOp));
  this->g->delNodes(*nodes);
  
  delete nodes;
}


void ResultImpl::filterEdgesPat(const std::string &label, Attribute * attr[], int nAttr, int cmpOp) {
  //on récupère les noeuds remplissant les conditions opposées à celles souhaitées pour ensuite les supprimer
  std::vector<edge> * edges = this->pattern->getEdges(label, this->g, attr, nAttr, oppose(cmpOp));
  this->g->delEdges(*edges);
  
  delete edges;
}


Result * ResultImpl::match(Pattern * p) {
  return GraphWriteAbstract::match(p);
}


/*cmpOp : EQUAL -> = , DIFFERENT -> != */
void ResultImpl::where(std::string label, Attribute * attr[], int nAttr, int cmpOp){
  bool lookForPatLabel = true;

  try {
    if (pattern != NULL) {
      std::cout << "maybe i am a pattern" << std::endl;
      if(pattern->isNode(label))
        filterNodesPat(label, attr, nAttr, cmpOp);
      else if(pattern->isEdge(label))
        filterEdgesPat(label, attr, nAttr, cmpOp);
      else
	lookForPatLabel = false;

      std::cout << (lookForPatLabel ? "true" : "false") << std::endl;
    }
    else
      lookForPatLabel = false;
    
    if (!lookForPatLabel) {
      std::cout << "i am a entity/relation" << std::endl;
      if(db->isEntity(label))
	filterNodes(label, attr, nAttr, cmpOp);
      else if(db->isRelation(label))
	filterEdges(label, attr, nAttr, cmpOp);
    }
  }
  catch (std::string &errMessage) {
    std::cerr << errMessage << std::endl;
  }
}


std::vector<Attribute*> * ResultImpl::get(const std::string &label, const std::string &attributeName) const {
  return GraphWriteAbstract::get(label, attributeName);
}
  

int oppose(int cmpOp) {
  if (cmpOp == EQUAL)
    return DIFFERENT;
  return EQUAL;
}
