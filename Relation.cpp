#include <iostream>
#include <string.h>
#include "Relation.hpp"
#include <tulip/TlpTools.h>
#include <tulip/Graph.h>
#include <tulip/Edge.h>
#include <tulip/Node.h>

using namespace tlp;

Relation::Relation(Graph* G, const std::string name, const char * nameProperty[], const char * typeProperty[], int len)
{
  this->len=len;
  for(int i=0; i<len; i++)
    {
      strcpy(this->nameProperty[i],nameProperty[i]);
      strcpy(this->typeProperty[i],typeProperty[i]);
    }
  g= G->Graph::addSubGraph(name);
  for(int i=0; i<len; i++)
    property[i]=g->getLocalProperty(nameProperty[i], typeProperty[i]);
}

Relation::~Relation()
{
  g->clear();
}
  
int Relation::newRelationInstance(const char * nameProperty[], const char * valueProperty[], const node n1, const node n2, int len)
{
  struct edge e = g->addEdge(n1,n2);
  for(int i=0; i<this->len; i++)
    property[i]->setEdgeStringValue(e,"");
  for(int i=0; i<len; i++)
    {
      while(!property[i]->PropertyInterface::getName().compare(nameProperty[i]))
	{
	  property[i]->setEdgeStringValue(e, valueProperty[i]);
	} 
    }
}

int Relation::deleteRelationInstance(const char * nameProperty[], const char * valueProperty[], int len)
{
  struct Edge* l;
  int lenL=this->getRelationInstance(nameProperty, valueProperty, len, l);
  for (int i=0; i<lenL; i++)
    {
      this->g->Graph::delEdge(l[i],true);
    }
}

int Relation::editRelationInstance(const char * nameProperty[], const char * valueProperty[], int len)
{
  struct Edge* l;
  int lenL=this->getRelationInstance(nameProperty, valueProperty, len, l);
  for (int j=0; j<lenL; j++)
    {
      for(int i=0; i<len; i++)
	{
	  while(!property[i]->PropertyInterface::getName().compare(nameProperty[i]))
	    {
	      property[i]->setEdgeStringValue(l[i], valueProperty[i]);
	    } 
	  
	}
    }
}

int Relation::getRelationInstance(const char * nameProperty[], const char * valueProperty[], int len, struct edge* l)
{
  int lenL =0;
  bool b, b2;
  Iterator<Edge> *itEdges = this->g->getEdges();
  while(itEdges->hasNext())
    {
      b=true;
      struct Edge e = itEdges->next(); 
      for(int i=0; i<len; i++)
	{
	  b2=false;
	  int j=0;
	  while(j<this->len && !property[j]->PropertyInterface::getName().compare(nameProperty[i]))
	    {
	      j++; 
	    }
	  if(property[j]->PropertyInterface::getEdgeStringValue(e) == valueProperty[i] ) 
	    b2=true;
	  b=b2;
	}
      if (b)
        {
          l[lenL]=e;
          lenL++;
        }
    }
  return lenL;
}
