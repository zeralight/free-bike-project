#include "Request.hpp"

using namespace tlp;

Request::Request(Graph * gr, string n):g(gr), name(n){}

Result Request::getAllNodes(){
  Graph * resultSubGraph = g->addSubGraph(name);
  Iterator<node> * nodes = g->getNodes();
  resultSubGraph->addNodes(nodes);
  return Result(resultSubGraph, name);
}

Result Request::getAllNodes(const Entity &e){
  Graph * resultSubGraph = g->addSubGraph(name);
  std::string nameE = e.getName();
  Iterator<node> * nodes = g->getNodes();
  while (nodes->hasNext()){
    if (getNodeDefaultStringValue(*nodes) == nameE)
      resultSubGraph->addNode(*nodes);
    nodes->next();
  }
  return Result(resultSubGraph, name); 
}

Result Request::getAllEdges(){
  Graph * resultSubGraph = g->addSubGraph(name);
  Iterator<edge> * edges = g->getEdges();
  resultSubGraph->addEdges(edges);
  return Result(resultSubGraph, name);
}
	    
Result Request::getAllEdges(const Relation &r){
  Graph * resultSubGraph = g->addSubGraph(name);
  std::string nameR = r.getName();
  Iterator<edge> * edges = g->getEdges();
  while (edges->hasNext()){
    if (getEdgeDefaultStringValue(*edges) == nameR)
      resultSubGraph->addEdge(*edges);
    edges->next();
  }
  return Result(resultSubGraph, name); 
}

Result getNodes(const Entity &e, const int value){
  Graph * resultSubGraph = g->addSubGraph(name);
  std::string nameE = e.getName();
  Iterator<node> * nodes = g->getNodes();
  while (nodes->hasNext()){
    if(getNodeDefaultStringValue(*nodes) == nameE && value == getNodeValue(*nodes))
      resultSubGraph->addNode(*nodes);
    nodes->next();
  }
  return Result(resultSubGraph, name);      
}

Result getNodes(const Entity &e, const double value){
  Graph * resultSubGraph = g->addSubGraph(name);
  std::string nameE = e.getName();
  Iterator<node> * nodes = g->getNodes();
  while (nodes->hasNext()){
    if(getNodeDefaultStringValue(*nodes) == nameE && value == getNodeDoubleValue(*nodes))
      resultSubGraph->addNode(*nodes);
    nodes->next();
  }
  return Result(resultSubGraph, name);      
}

Result getNodes(const Entity &e, const bool value){
  Graph * resultSubGraph = g->addSubGraph(name);
  std::string nameE = e.getName();
  Iterator<node> * nodes = g->getNodes();
  while (nodes->hasNext()){
    if(getNodeDefaultStringValue(*nodes) == nameE && value == getNodeValue(*nodes))
      resultSubGraph->addNode(*nodes);
    nodes->next();
  }
  return Result(resultSubGraph, name);      
}

Result getNodes(const Entity &e, const string value){
  Graph * resultSubGraph = g->addSubGraph(name);
  std::string nameE = e.getName();
  Iterator<node> * nodes = g->getNodes();
  while (nodes->hasNext()){
    if(getNodeStringValue(*nodes) == nameE && value == getNodeStringValue(*nodes))
      resultSubGraph->addNode(*nodes);
    nodes->next();
  }
  return Result(resultSubGraph, name);      
}

Result getEdges(const Relation &r, const int value){
  Graph * resultSubGraph = g->addSubGraph(name);
  std::string nameR = r.getName();
  Iterator<edge> * edges = g->getEdges();
  while (edges->hasNext()){
    if(getEdgeDefaultStringValue(*edges) == nameR && value == getEdgeValue(*edges))
      resultSubGraph->addEdge(*edges);
    edges->next();
  }
  return Result(resultSubGraph, name);      
}

Result getEdges(const Relation &r, const double value){
  Graph * resultSubGraph = g->addSubGraph(name);
  std::string nameR = r.getName();
  Iterator<edge> * edges = g->getEdges();
  while (edges->hasNext()){
    if(getEdgeDefaultStringValue(*edges) == nameR && value == getEdgeDoubleValue(*edges))
      resultSubGraph->addEdge(*edges);
    edges->next();
  }
  return Result(resultSubGraph, name);      
}

Result getEdges(const Relation &r, const bool value){
  Graph * resultSubGraph = g->addSubGraph(name);
  std::string nameR = r.getName();
  Iterator<edge> * edges = g->getEdges();
  while (edges->hasNext()){
    if(getEdgeDefaultStringValue(*edges) == nameR && value == getNodeValue(*edges))
      resultSubGraph->addEdge(*edges);
    edges->next();
  }
  return Result(resultSubGraph, name);      
}

Result getEdges(const Relation &r, const string value){
  Graph * resultSubGraph = g->addSubGraph(name);
  std::string nameR = r.getName();
  Iterator<edge> * edges = g->getEdges();
  while (edges->hasNext()){
    if(getEdgeDefaultStringValue(*edges) == nameR && value == getEdgeStringValue(*edges))
      resultSubGraph->addEdge(*edges);
    edges->next();
  }
  return Result(resultSubGraph, name);      
}
