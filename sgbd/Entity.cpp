#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unordered_map>
#include <set>
#include <iterator>

#include <tulip/TlpTools.h>
#include <tulip/Graph.h>
#include <tulip/Node.h>

#include <tulip/StringProperty.h>

#include "Entity.hpp"
#include "DBTools.hpp"

#define TLPPROP_ENTITY_NAME "dbEntityName"

using namespace tlp;

Entity::Entity(const std::string &name, const Attribute * const attr[], int nAttr) {
  int i;
  
  this->name = name;
  this->nAttr = nAttr;
  this->g = newGraph();

  for(i = 0 ; i < nAttr ; i++) {
    this->attr[attr[i]->getLabel()] = attr[i]->clone();
    this->attr[attr[i]->getLabel()]->setProperty(g->getLocalProperty(attr[i]->getLabel(), attr[i]->getTypeName()));

    //initialisation ? ou Tulip le fait par défaut ?
  }
}

Entity::~Entity() {
  this->attr.clear();

  delete g;
}


Graph * Entity::getGraph() const {
  return this->g;
}


const node * Entity::newInstance(Attribute * attr[], int nAttr) {
  int i;
  node * n = (node *) malloc(sizeof(node));
  *n = g->addNode();

  if (isValid(attr, nAttr)) {
    for(i = 0 ; i < nAttr ; i++) {
      attr[i]->setProperty(this->attr[attr[i]->getLabel()]);
      attr[i]->setValue(*n);
    }

    return n;
  }
  else
    return NULL;
}

int Entity::delInstance(const std::set<node> * instSet) {
  for (auto it = instSet->begin() ; it != instSet->end() ; it++)
    this->g->delNode(*it, true);
}

int Entity::delInstance(const node * n) {
  this->g->delNode(*n, true);
}

/*
int Entity::editEntityInstance(const char * attrNames[], const char * valueProperty[], int len)
{
  struct node* l;
  int lenL=this->getEntityInstance(attrNames, valueProperty, len, l);
  for (int j=0; j<lenL; j++)
    {
      for(int i=0; i<len; i++)
	{
	  while(!property[i]->PropertyInterface::getName().compare(attrNames[i]))
	    {
	      property[i]->setNodeStringValue(l[i], valueProperty[i]);
	    } 
	  
	}
    }
}
*/

std::set<node> * Entity::getInstance(Attribute * attr[], int nAttr) const {
  std::set<node> * res = new std::set<node>;
  bool hasMatchingAttr;
  Iterator<node> * itNodes;
  node n;
  
  if (this->isValid(attr, nAttr)) {
    itNodes = this->g->getNodes();
    
    while(itNodes->hasNext()) {
      n = itNodes->next();
      hasMatchingAttr = true;
      
      for(int i = 0 ; i < nAttr ; i++) {	
	if (!attr[i]->isEqual(n))
	  hasMatchingAttr = false;
      }

      if (hasMatchingAttr)
	res->emplace(n);
    }
  }
  
  return res;
}

// modifie egalement les propriétés de attr si elle existe
bool Entity::isValid(Attribute * attr[], int nAttr) const {
  for (int i = 0 ; i < nAttr ; i++) {
    auto it = this->attr.find(attr[i]->getLabel());
    if (it == this->attr.end())
      return false;

    attr[i]->setProperty((*it).second);
  }

  return true;
}
