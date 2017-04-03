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

template<class T>
Result * Request::getNodes(string entityName, Attribute * attr, T v1, T v2){
  Graph * resultSubGraph = g->addSubGraph(name);
  Entity * e = db->getEntity(entityName);
  Attribute * attr_tab[1] = {attr};
  std::vector<node> * nodes = new std::vector<node>;
  
  node n;
  
  Iterator<node> * it = g->getNodes();
  Attr<T> a = attr;
  
  if (e->isValid(attr_tab,1)){
    while(it->hasNext()){
      n = it->next;
      if (e->isInstance(n) && a->prop->getNodeValue(n) >= v1 && a->prop->getNodeValue(n) <= v2)
	nodes->push_back(n);	  
    }
  }
  delete it;
  return nodes;
}

template<class T>
Result * Request::getEdges(string relationName, Attribute * attr, T v1, T v2){
  Graph * resultSubGraph = g->addSubGraph(name);
  Relation * r = db->getRelation(relationName);
  Attribute * attr_tab[1] = {attr};
  std::vector<edge> * edges = new std::vector<edge>;
  
  edge e;
  
  Iterator<node> * it = g->getEdges();
  Attr<T> a = attr;
  
  if (r->isValid(attr_tab,1)){
    while(it->hasNext()){
      e = it->next;
      if (r->isInstance(e) && a->prop->getEdgeValue(e) >= v1 && a->prop->getEdgeValue(e) <= v2)
	edges->push_back(e);	  
    }
  }
  delete it;
  return edges;
}  
  
  
template<class T>
Result * Request::getNodesSup(string entityName, Attribute * attr, T v1){
  Graph * resultSubGraph = g->addSubGraph(name);
  Entity * e = db->getEntity(entityName);
  Attribute * attr_tab[1] = {attr};
  std::vector<node> * nodes = new std::vector<node>;
  
  node n;
  
  Iterator<node> * it = g->getNodes();
  Attr<T> a = attr;
  
  if (e->isValid(attr_tab,1)){
    while(it->hasNext()){
      n = it->next;
      if (e->isInstance(n) && a->prop->getNodeValue(n) >= v1)
	nodes->push_back(n);	  
    }
  }
  delete it;
  return nodes;
}

template<class T>
Result * Request::getEdgesSup(string relationName, Attribute * attr, T v1){
  Graph * resultSubGraph = g->addSubGraph(name);
  Relation * r = db->getRelation(relationName);
  Attribute * attr_tab[1] = {attr};
  std::vector<edge> * edges = new std::vector<edge>;
  
  edge e;
  
  Iterator<node> * it = g->getEdges();
  Attr<T> a = attr;
  
  if (r->isValid(attr_tab,1)){
    while(it->hasNext()){
      e = it->next;
      if (r->isInstance(e) && a->prop->getEdgeValue(e) >= v1)
	edges->push_back(e);	  
    }
  }
  delete it;
  return edges;
}  

template<class T>
Result * Request::getNodesInf(string entityName, Attribute * attr, T v1){
  Graph * resultSubGraph = g->addSubGraph(name);
  Entity * e = db->getEntity(entityName);
  Attribute * attr_tab[1] = {attr};
  std::vector<node> * nodes = new std::vector<node>;
  
  node n;
  
  Iterator<node> * it = g->getNodes();
  Attr<T> a = attr;
  
  if (e->isValid(attr_tab,1)){
    while(it->hasNext()){
      n = it->next;
      if (e->isInstance(n) && a->prop->getNodeValue(n) <= v1)
	nodes->push_back(n);	  
    }
  }
  delete it;
  return nodes;
}

template<class T>
Result * Request::getEdgesInf(string relationName, Attribute * attr, T v1){
  Graph * resultSubGraph = g->addSubGraph(name);
  Relation * r = db->getRelation(relationName);
  Attribute * attr_tab[1] = {attr};
  std::vector<edge> * edges = new std::vector<edge>;
  
  edge e;
  
  Iterator<node> * it = g->getEdges();
  Attr<T> a = attr;
  
  if (r->isValid(attr_tab,1)){
    while(it->hasNext()){
      e = it->next;
      if (r->isInstance(e) && a->prop->getEdgeValue(e) <= v1)
	edges->push_back(e);	  
    }
  }
  delete it;
  return edges;
}
