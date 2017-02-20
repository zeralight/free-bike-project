#include <tulip/TlpTools.h>
#include <tulip/Graph.h>
#include <tulip/Node.h>
#include <tulip/Edge.h>

#include "DBTools.hpp"

using namespace tlp;

/*
Iterator<edge> * getItEdges(const Graph * g, const node * nA, const node * nB, direction dir) {
  Iterator<edge> * ret = NULL;
  
  switch(dir) {
  case IN:
    if (nB)
      ret = g->getInOutEdges(*nB, *nA, true);
    else
      ret = g->getInEdges(*nA);
    break;
    
  case OUT:
    if (nB)
      ret = g->getEdges(*nA, *nB, true);
    else
      ret = g->getOutEdges(*nA);
    break;
    
  case INOUT:
    if (nB)
      ret = g->getEdges(*nA, *nB, false);
    else
      ret = g->getInOutEdges(*nA);
    break;
    
  default:
    return ret;
  };

  return ret;
}
*/


std::vector<node> * getNodes(const Graph * g, Attribute * attr[], int nAttr) {
  std::vector<node> * res = new std::vector<node>;
  bool hasMatchingAttr;
  node n;

  Iterator<node> * it = g->getNodes();

  while(it->hasNext()) {
    n = it->next();
    hasMatchingAttr = true;
    
    for(int i = 0 ; i < nAttr ; i++) {
      if (!attr[i]->isEqual(n))
	hasMatchingAttr = false;
    }
    
    if (hasMatchingAttr)
      res->push_back(n);
  }

  delete it;

  return res;
}


std::vector<edge> * getEdges(const Graph * g, const node * nA, const node * nB, Attribute * attr[], int nAttr, direction dir) {
  std::vector<edge> * res = new std::vector<edge>;
  bool hasMatchingAttr;

  switch(dir) {
  case IN:
    *res = g->getEdges(*nB, *nA, true);
    break;
    
  case OUT:
    *res = g->getEdges(*nA, *nB, true);
    break;
   
  case INOUT:
    *res = g->getEdges(*nA, *nB, false);
    break;
  };

  auto it = res->begin(); 
  while(it != res->end()) {
    hasMatchingAttr = true;
    
    for(int i = 0 ; i < nAttr ; i++) {
      if (!attr[i]->isEqual(*it))
	hasMatchingAttr = false;
    }
      
    if (!hasMatchingAttr)
      it = res->erase(it);
    else
      it++;
  }
  
  return res;
}


std::vector<edge> * getEdges(Iterator<edge> * it, Attribute * attr[], int nAttr) {
  std::vector<edge> * res = new std::vector<edge>;
  bool hasMatchingAttr;
  edge e;
  
  while(it->hasNext()) {
    e = it->next();
    hasMatchingAttr = true;
    
    for(int i = 0 ; i < nAttr ; i++) {	
      if (!attr[i]->isEqual(e))
	hasMatchingAttr = false;
    }
    
    if (hasMatchingAttr)
      res->push_back(e);
  }

  return res;
}


std::vector<edge> * getEdges(const Graph * g, const node * n, Attribute * attr[], int nAttr, direction dir) {
  Iterator<edge> * it = NULL;
  
  switch(dir) {
  case IN:
    it = g->getInEdges(*n);
    break;
    
  case OUT:
    it = g->getOutEdges(*n);
    break;
    
  case INOUT:
    it = g->getInOutEdges(*n);
    break;
  };

  std::vector<edge> * ret = getEdges(it, attr, nAttr);
  delete it;
  
  return ret;
}


std::vector<edge> * getEdges(const Graph * g, Attribute * attr[], int nAttr) {
  Iterator<edge> * it = g->getEdges();
  
  std::vector<edge> * ret = getEdges(it, attr, nAttr);
  delete it;
  
  return ret;
}
