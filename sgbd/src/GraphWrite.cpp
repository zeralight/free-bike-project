#include <iostream>
#include <string>
#include <cstdlib>

#include <tulip/TlpTools.h>
#include <tulip/Graph.h>

#include "GraphWrite.hpp"
#include "GraphRead.hpp"
#include "DBTools.hpp"
#include "DatabaseImpl.hpp"
#include "Entity.hpp"
#include "Relation.hpp"


GraphWriteAbstract::GraphWriteAbstract(Graph * g, DatabaseImpl * db): GraphReadAbstract(g, db) {}


GraphWriteAbstract::~GraphWriteAbstract() {}


bool GraphWriteAbstract::editNodes(const std::string &entityName, Attribute * attr[], int nAttr){
  Entity * e = this->db->getEntity(entityName);
  std::vector<node> * nodes = e->getInstance(this->g);
  bool res = e->editInstance(nodes, attr, nAttr);
  return res;
}


bool GraphWriteAbstract::editEdges(const std::string &relationName, Attribute * attr[], int nAttr){
  Relation * r = this->db->getRelation(relationName);
  std::vector<edge> * edges = r->getInstance(this->g);
  bool res = r->editInstance(edges, attr, nAttr);
  return res;
}
