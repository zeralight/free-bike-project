#include "Request.hpp"


using namespace tlp;

Request::Request(Graph * gr, string n, DatabaseImpl * d):db(d),g(gr), name(n){}

Result* Request::getAllNodes(){
  Graph * resultSubGraph = g->addSubGraph(name);
  Iterator<node> * nodes = g->getNodes();
  resultSubGraph->addNodes(nodes);
  ResultImpl r = ResultImpl(name, resultSubGraph, db);
  Result* res = &r;
  delete nodes;
  return res;
}

/*utiliser Entity::getInstance */
/*penser au template pr éviter la duplication de code*/
/*utiliser Entity::isInstance*/
/*l'utilisateur ne fournit pas d'Entity mais une chaine de caractère correspondant au nom d'une entité*/
Result* Request::getAllNodes(string entityName){
  Graph * resultSubGraph = g->addSubGraph(name);
  Entity * e = this->db->getEntity(entityName);
  std::vector<node> * nodes = e->getInstance(this->g);
  resultSubGraph->addNodes(*nodes);
  ResultImpl r = ResultImpl(name, resultSubGraph, db);
  Result* res = &r;
  delete nodes;
  return res;
}

Result* Request::getAllEdges(){
  Graph * resultSubGraph = g->addSubGraph(name);
  Iterator<edge> * edges = g->getEdges();
  resultSubGraph->addEdges(edges);
  ResultImpl r = ResultImpl(name, resultSubGraph, db);
  Result* res = &r;
  delete edges;
  return res;
}
	    
Result* Request::getAllEdges(string relationName){
  Graph * resultSubGraph = g->addSubGraph(name);
  Relation * relation = this->db->getRelation(relationName);
  std::vector<edge> * edges = relation->getInstance(this->g);
  resultSubGraph->addEdges(*edges);
  ResultImpl r = ResultImpl(name, resultSubGraph, db);
  Result* res = &r;
  delete edges;
  return res;
}

Result* Request::getNodes(string entityName, Attribute * attr[], int nAttr){
  Graph * resultSubGraph = g->addSubGraph(name);
  Entity * e = this->db->getEntity(entityName);
  std::vector<node> * nodes = e->getInstance(attr, nAttr);
  resultSubGraph->addNodes(*nodes);
  ResultImpl r = ResultImpl(name, resultSubGraph, db);
  Result* res = &r;
  delete nodes;
  return res;      
}

Result* Request::getEdges(string relationName, Attribute * attr[], int nAttr){
  Graph * resultSubGraph = g->addSubGraph(name);
  Relation * relation = db->getRelation(relationName);
  std::vector<edge> * edges = relation->getInstance(attr, nAttr);
  resultSubGraph->addEdges(*edges);
  ResultImpl r = ResultImpl(name, resultSubGraph, db);
  Result* res = &r;
  delete edges;
  return res;      
}
