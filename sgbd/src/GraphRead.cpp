#include <vector>

#include <tulip/TlpTools.h>
#include <tulip/Graph.h>

#include "GraphRead.hpp"
#include "DatabaseImpl.hpp"
#include "ResultImpl.hpp"
#include "PatternImpl.hpp"
#include "Entity.hpp"
#include "Relation.hpp"


GraphReadAbstract::GraphReadAbstract(Graph * g, DatabaseImpl * db) {
  this->g = g;
  this->db = db;
  this->pattern = NULL;
}


GraphReadAbstract::~GraphReadAbstract() {
  if (g) {
    Graph * supG = g->getSuperGraph();
    if (supG != g)
      supG->delAllSubGraphs(g);
    else
      delete g;
  }
}


std::vector<node> * GraphReadAbstract::getNodes(const std::string &entityName) const {
  Entity * e = this->db->getEntity(entityName);
  std::vector<node> * res;
  
  if (this == ((GraphReadAbstract *) this->db))
    res = e->getInstance(NULL, 0, EQUAL);
  else
    res = e->getInstance(this->g, EQUAL);

  return res;
}


std::vector<edge> * GraphReadAbstract::getEdges(const std::string &relationName) const {
  Relation * r = this->db->getRelation(relationName);
  std::vector<edge> * res;
  
  if (this == ((GraphReadAbstract *) this->db))
    res = r->getInstance(NULL, 0, EQUAL);
  else
    res = r->getInstance(this->g, EQUAL);

  return res;
}


Result * GraphReadAbstract::match(Pattern * p) {
  PatternImpl * pi = ((PatternImpl *) p);
  Graph * g = this->db->newGraphResult("");
  ResultImpl * res = new ResultImpl("match", g, this->db);

  try {
    if (pi->getDB() != this->db)
      throw std::string("ERROR: The pattern isn't associated with the database");
  }
  catch (std::string &errMessage) {
    std::cerr << errMessage << std::endl;
  }

  res->setPattern(pi);
  pi->match(g);
  
  return res;
}


std::vector<Attribute*> * GraphReadAbstract::get(const std::string &label, const std::string &attributeName) const {
  std::vector<Attribute *> * res = new std::vector<Attribute *>;

  try {
    if (this->pattern == NULL)
      res = getElement(label, attributeName);
    else if (this->pattern->isNode(label)) {
      Entity * e = this->pattern->getEntity(label);
      std::vector<node> * nodes = e->getInstance(this->g, EQUAL);
      
      for(auto it = nodes->begin() ; it != nodes->end() ; it++)
	res->push_back(e->getAttr(attributeName, *it));
    }
    else if (this->pattern->isEdge(label)) {
      Relation * r = this->pattern->getRelation(label);
      std::vector<edge> * edges = r->getInstance(this->g, EQUAL);
      
      for(auto it = edges->begin() ; it != edges->end() ; it++)
	res->push_back(r->getAttr(attributeName, *it));
    }
    else 
      res = getElement(label, attributeName); 
  }
  catch (std::string &errMessage) {
    std::cout << errMessage << std::endl;
  }
  
  return res;
};


std::vector<Attribute*> * GraphReadAbstract::getElement(const std::string &label, const std::string &attributeName) const {
  std::vector<Attribute *> * res = new std::vector<Attribute *>;
  
  if (this->db->isEntity(label)) {
    Entity * e = this->db->getEntity(label);
    std::vector<node> * nodes = e->getInstance(this->g, EQUAL);
    
    for(auto it = nodes->begin() ; it != nodes->end() ; it++)
      res->push_back(e->getAttr(attributeName, *it));
  }
  else if (this->db->isRelation(label)) {
    Relation * r = this->db->getRelation(label);
    std::vector<edge> * edges = r->getInstance(this->g, EQUAL);
    
    for(auto it = edges->begin() ; it != edges->end() ; it++)
      res->push_back(r->getAttr(attributeName, *it));
  }
  else
    throw std::string("ERROR: No element correspond to the label '" + label + "'");
  
  return res;
}


Graph * GraphReadAbstract::getGraph() {
  return this->g;
}


void GraphReadAbstract::setPattern(PatternImpl * pi) {
  this->pattern = pi;
}
