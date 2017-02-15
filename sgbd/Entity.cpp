#include <iostream>
#include <cstring>
#include <cstdlib>

#include <tulip/TlpTools.h>
#include <tulip/Graph.h>
#include <tulip/Node.h>

#include <tulip/StringProperty.h>

#include "Entity.hpp"
#include "DBTools.hpp"

#define TLPPROP_ENTITY_NAME "dbEntityName"

using namespace tlp;

Entity::Entity(const std::string name, const Attribute * const attr[], int nAttr) {
  int i;
  
  this->name = name;
  this->nAttr = nAttr;
  this->attr = (Attribute **) malloc(nAttr * sizeof(Attribute *));
  this->g = newGraph();

  StringProperty * propName = g->getLocalProperty<StringProperty>(TLPPROP_ENTITY_NAME);
  propName->setAllNodeValue(name);
  
  for(i = 0 ; i < nAttr ; i++) {
    this->attr[i] = attr[i]->clone();
    this->attr[i]->setProperty(g->getLocalProperty(attr[i]->getLabel(), attr[i]->getTypeName()));
    std::string tmp = "oua";
    this->attr[i]->set(&tmp);
  }
}

// Ai modifié GraphImpl : constructeur passé a virtual -> mauvaise idée de modifier les éléments de la librairie, trouver une autre solution
Entity::~Entity() {
  int i;
  for (i = 0 ; i < nAttr ; i++)
    delete attr[i];
  
  delete attr;
  delete g;
}


Graph * Entity::getGraph() const {
  return this->g;
}


/*
const node * Entity::newInstance(const Attribute * const attr[], int nAttr) {
  int i;
  node n = g->addNode();

  if (isValid(attr, nAttr)) {
    for(i = 0 ; i < this->nAttr ; i++)
      property[i]->setNodeStringValue(n, "");
    
    for(int i=0; i<nAttr; i++) {
      while(!property[i]->PropertyInterface::getName().compare(attrNames[i])) {
	property[i]->setNodeStringValue(n, valueProperty[i]);
      } 
    }
  }
  else
    return NULL;
}

int Entity::deleteEntityInstance(const char * attrNames[], const char * valueProperty[], int len)
{
  struct node* l;
  int lenL=this->getEntityInstance(attrNames, valueProperty, len, l);
  for (int i=0; i<lenL; i++)
    {
      this->g->Graph::delNode(l[i],true);
    }
}

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

int Entity::getEntityInstance(const char * attrNames[], const char * valueProperty[], int len, struct node* l)
{
  int lenL =0;
  bool b, b2;
  Iterator<node> *itNodes = this->g->getNodes();
  while(itNodes->hasNext())
    {
      b=true;
      struct node n = itNodes->next(); 
      for(int i=0; i<len; i++)
	{
	  b2=false;
	  int j=0;
	  while(j<this->len && !property[j]->PropertyInterface::getName().compare(attrNames[i]))
	    {
	      j++; 
	    }
	  if(property[j]->PropertyInterface::getNodeStringValue(n) == valueProperty[i] ) 
	    b2=true;
	  b=b2;
	}
      if (b)
        {
          l[lenL]=n;
          lenL++;
        }
    }
  return lenL;
}
*/

bool Entity::isValid(const Attribute * const attr[], int nAttr) const {
  return true;
}
