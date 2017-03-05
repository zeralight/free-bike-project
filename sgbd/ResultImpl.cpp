#include <tulip/Graph.h>

#include "DatabaseImpl.hpp"
#include "ResultImpl.hpp"


using namespace tlp;


ResultImpl::ResultImpl(Graph * g, DatabaseImpl * db): GraphWriteAbstract(g, db) {}


ResultImpl::~ResultImpl() {}


bool ResultImpl::editResultNodes(Entity& e, Attribute * attr[], int nAttr){
  std::vector<node> * nodes = e.getInstance(attr, nAttr);
  bool res = e.editInstance(nodes, attr, nAttr);
  return res;
}


bool ResultImpl::editResultEdges(Relation& r, Attribute * attr[], int nAttr){
  std::vector<edge> * edges = r.getInstance(attr, nAttr);
  bool res = r.editInstance(edges, attr, nAttr);
  return res;
}


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

