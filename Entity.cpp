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
  
int Entity::newEntityInstance(char * nameProperty[], char * valueProperty[], int len)
{
  node n = g->addNode();
  for(int i=0; i<this->len; i++)
    property[i]->setNodeStringValue(n,"");
  for(int i=0; i<len; i++)
    {
      while(!property[i]->PropertyInterface::getName().compare(nameProperty[i]))
	  {
	    property[i]->setNodeStringValue(n, valueProperty[i]);
	  } 
    }
}

int Entity::deleteEntityInstance(char * nameProperty[], char * valueProperty[], int len)
{
  bool b, b2;
  Iterator<node> *itNodes = graph->getNodes();
  while(itNodes->hasNext())
    {
      b=true;
      node n = itNodes->next(); 
      for(int i=0; i<len; i++)
	  {
	    b2=false;
        int j=0;
        while(j<this.len && !property[j]->PropertyInterface::getName().compare(nameProperty[i]))
	     {
	       j++; 
	      }
        if() //test si la val prop=prop du noeud
          b2=true;
	    b=b2;
	  }
      if (b)
	    delNode(n,true);
    }
}

int Entity::editEntityInstance(char * nameProperty[], char * valueProperty[], int len)
{

}

