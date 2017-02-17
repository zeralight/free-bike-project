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

using namespace tlp;

Entity::Entity(const std::string &name, const Attribute * const attr[], int nAttr, Graph * g) {
  this->g = g;
  
  // Initialize nodes with entity's name
  this->name = name;
  this->nameProp = this->g->getLocalProperty<StringProperty>(PROP_ENTITY_NAME);
  this->nameProp->setAllNodeValue(name);
  
  // Creation of all properties
  this->nAttr = nAttr;
  for(int i = 0 ; i < nAttr ; i++) {
    this->attr[attr[i]->getLabel()] = attr[i]->clone();
    this->attr[attr[i]->getLabel()]->setProperty(this->g->getLocalProperty(attr[i]->getLabel(), attr[i]->getTypeName()));

    //initialisation ? ou Tulip le fait par défaut ?
  }
}

Entity::~Entity() {
  this->attr.clear();
  delete nameProp;
  delete g;
}


Graph * Entity::getGraph() const {
  return this->g;
}


const node * Entity::newInstance(Attribute * attr[], int nAttr) {
  node * n = (node *) malloc(sizeof(node));
  *n = this->g->addNode();

  if (isValid(attr, nAttr)) {
    for(int i = 0 ; i < nAttr ; i++)
      attr[i]->setValue(*n);

    return n;
  }
  else
    return NULL;
}

void Entity::delInstance(const std::set<node> * nSet) {
  for (auto it = nSet->begin() ; it != nSet->end() ; it++)
    this->g->delNode(*it, true);
}

void Entity::delInstance(const node * n) {
  this->g->delNode(*n, true);
}

bool Entity::editInstance(node * n, Attribute * attr[], int nAttr) {
  if (!isInstance(n) || !isValid(attr, nAttr))
    return false;

  for (int i = 0 ; i < nAttr ; i++)
    attr[i]->setValue(*n);

  return true;
}

bool Entity::editInstance(std::set<node> * nSet, Attribute * attr[], int nAttr) {
  bool res = true;
  node * n;
  for (auto it = nSet->begin() ; it != nSet->end() ; it++) {
    *n = *it;
    res = res && editInstance(n, attr, nAttr);
  }

  return res;
}

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

bool Entity::isInstance(const node * n) const {
  return this->g->isElement(*n);
}
