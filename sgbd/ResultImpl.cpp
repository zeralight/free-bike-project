#include <tulip/Graph.h>

#include "DatabaseImpl.hpp"
#include "ResultImpl.hpp"


using namespace tlp;


ResultImpl::ResultImpl(Graph * g, DatabaseImpl * db): GraphWriteAbstract(g, db) {}


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

