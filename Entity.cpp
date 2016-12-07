#include <iostream>
#include <string.h>
#include "Entity.hpp"
#include <tulip/TlpTools.h>
#include <tulip/Graph.h>

using namespace tlp;

Entity::Entity(std::string name, char * nameProperty[], char * typeProperty[], int len)
{
  this->len=len;
  for(int i=0; i<len; i++)
    {
      strcpy(this->nameProperty[i],nameProperty[i]);
      strcpy(this->typeProperty[i],typeProperty[i]);
    }
  g->Graph::addSubGraph(name);
  for(int i=0; i<len; i++)
    property[i]=g->getLocalProperty(nameProperty[i], typeProperty[i]);
}

Entity::~Entity()
{
  g->clear();
}
  
int Entity::newEntityInstance(char ** nameProperty, void * valueProperty, int len)
{
  node n = g->addNode();
  for(int i=0; i<this->len; i++)
    property[i]->setNodeValue(n, NULL);
  for(i=0; i<len; i++)
    {
      while(strcmp(property[i]->PropertyInterface::getName(), nameProperty[i]))
	{
	  property[i]->setNodeValue(n, valueProperty[i]);
	} 
    }
  
}

int Entity::deleteEntityInstance()
{
}

int Entity::editEntityInstance()
{
}

