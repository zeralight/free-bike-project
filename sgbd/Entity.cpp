#include <iostream>
#include <cstring>
#include "Entity.hpp"
#include <tulip/TlpTools.h>
#include <tulip/Graph.h>
#include <tulip/Node.h>

#include <tulip/StringProperty.h>

using namespace tlp;

Entity::Entity(const std::string name, const std::string attrNames[], const std::string attrTypes[], int nAttr) {
  int i;
  //Affichage : voir src newGraph() (semble non nécessaire)

  this->name = name;
  this->nAttr = nAttr;
  this->attrNames = new std::string [nAttr];
  this->attrTypes = new std::string [nAttr];

  for(i = 0 ; i < nAttr ; i++) {
    this->attrNames[i] = attrNames[i];
    this->attrTypes[i] = attrTypes[i];
    // Création de la propriété dans 'this'
    getLocalProperty(attrNames[i], attrTypes[i]);
  }  
}

// Ai modifié GraphImpl : constructeur passé a virtual -> mauvaise idée de modifier les éléments de la librairie, trouver une autre solution
Entity::~Entity() {
  int i;
  delete [] attrNames;
  delete [] attrTypes;
}

/*
int Entity::newEntityInstance(const char * attrNames[], const char * valueProperty[], int nAttr)
{
  struct node n = g->addNode();
  for(int i=0; i<this->nAttr; i++)
    property[i]->setNodeStringValue(n,"");
  for(int i=0; i<nAttr; i++)
    {
      while(!property[i]->PropertyInterface::getName().compare(attrNames[i]))
	{
	  property[i]->setNodeStringValue(n, valueProperty[i]);
	} 
    }
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
