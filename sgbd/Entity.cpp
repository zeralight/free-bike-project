#include <iostream>
#include <string.h>
#include "Entity.hpp"
#include <tulip/TlpTools.h>
#include <tulip/Graph.h>
#include <tulip/Node.h>

using namespace tlp;

Entity::Entity(Graph* G, const std::string name, const char * nameProperty[], const char * typeProperty[], int len)
{
  this->len = len;
  for(int i=0; i<len; i++)
    {
      strcpy(this->nameProperty[i],nameProperty[i]);
      strcpy(this->typeProperty[i],typeProperty[i]);
    }
  g= G->Graph::addSubGraph(name);
  for(int i=0; i<len; i++)
    property[i]=g->getLocalProperty(nameProperty[i], typeProperty[i]);
}

Entity::~Entity()
{
  g->clear();
}
  
int Entity::newEntityInstance(const char * nameProperty[], const char * valueProperty[], int len)
{
  struct node n = g->addNode();
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

int Entity::deleteEntityInstance(const char * nameProperty[], const char * valueProperty[], int len)
{
  struct node* l;
  int lenL=this->getEntityInstance(nameProperty, valueProperty, len, l);
  for (int i=0; i<lenL; i++)
    {
      this->g->Graph::delNode(l[i],true);
    }
}

int Entity::editEntityInstance(const char * nameProperty[], const char * valueProperty[], int len)
{
  struct node* l;
  int lenL=this->getEntityInstance(nameProperty, valueProperty, len, l);
  for (int j=0; j<lenL; j++)
    {
      for(int i=0; i<len; i++)
	{
	  while(!property[i]->PropertyInterface::getName().compare(nameProperty[i]))
	    {
	      property[i]->setNodeStringValue(l[i], valueProperty[i]);
	    } 
	  
	}
    }
}

int Entity::getEntityInstance(const char * nameProperty[], const char * valueProperty[], int len, struct node* l)
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
	  while(j<this->len && !property[j]->PropertyInterface::getName().compare(nameProperty[i]))
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

