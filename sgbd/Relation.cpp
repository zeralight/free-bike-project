#include <iostream>
#include <string.h>

#include <tulip/TlpTools.h>
#include <tulip/Graph.h>
#include <tulip/Edge.h>
#include <tulip/StringProperty.h>

#include "Relation.hpp"
#include "DBTools.hpp"
#include "Tools.hpp"

using namespace tlp;

<<<<<<< HEAD
Relation::Relation(const std::string &name, Entity * src, Entity * dst, const Attribute * const attr[], int nAttr, Graph * g) {
   this->g = g;

   this->entitySrc = src;
   this->entityDst = dst;
  
  // Initialize edges with relation's name
  this->name = name;
  this->nameProp = this->g->getLocalProperty<StringProperty>(PROP_RELATION_NAME);
  this->nameProp->setAllEdgeValue(name);
  
  // Creation of all properties
  this->nAttr = nAttr;
  for(int i = 0 ; i < nAttr ; i++) {
    this->attr[attr[i]->getLabel()] = attr[i]->clone();
    this->attr[attr[i]->getLabel()]->setProperty(this->g->getLocalProperty(attr[i]->getLabel(), attr[i]->getTypeName()));

    //initialisation ? ou Tulip le fait par défaut ?
  } 
}


Relation::~Relation() {
  this->attr.clear();
  delete nameProp;
  delete g;
}


Graph * Relation::getGraph() const {
  return this->g;
}


const edge * Relation::newInstance(const node * src, const node * dst, Attribute * attr[], int nAttr) {
  edge * e = (edge *) malloc(sizeof(edge));
  *e = this->g->addEdge(*src, *dst);

  if (isValid(attr, nAttr)) {
    for(int i = 0 ; i < nAttr ; i++)
      attr[i]->setValue(*e);

    return e;
  }
  else
    return NULL;
}


void Relation::delInstance(const std::vector<edge> * eSet) {
  for (auto it = eSet->begin() ; it != eSet->end() ; it++)
    this->g->delEdge(*it, true);
=======
Relation::Relation(Graph* G, const std::string name, const char * nameProperty[], const char * typeProperty[], int len)
{
  this->name.assign(name);
  this->len=len;
  for(int i=0; i<len; i++)
    {
      strcpy(this->nameProperty[i],nameProperty[i]);
      strcpy(this->typeProperty[i],typeProperty[i]);
    }
  g= G->Graph::addSubGraph(name);
  for(int i=0; i<len; i++)
    property[i]=g->getLocalProperty(nameProperty[i], typeProperty[i]);
>>>>>>> dcd4900c4d501b98b1dcc19f3dbc43eab80a31a7
}


void Relation::delInstance(const edge * e) {
  this->g->delEdge(*e, true);
}


bool Relation::editInstance(edge * e, Attribute * attr[], int nAttr) {
  if (!isInstance(e) || !isValid(attr, nAttr))
    return false;

  for (int i = 0 ; i < nAttr ; i++)
    attr[i]->setValue(*e);

  return true;
}


bool Relation::editInstance(std::vector<edge> * eSet, Attribute * attr[], int nAttr) {
  bool res = true;
  edge * e;
  for (auto it = eSet->begin() ; it != eSet->end() ; it++) {
    *e = *it;
    res = res && editInstance(e, attr, nAttr);
  }

  return res;
}

<<<<<<< HEAD

std::vector<edge> * Relation::getInstance(Attribute * attr[], int Attr) const {
  std::vector<edge> * res = new std::vector<edge>;
  Iterator<edge> * itEdges;
  
  if (this->isValid(attr, nAttr))
    res = getEdges(this->g, attr, nAttr);
  
  return res;
}


std::vector<edge> * Relation::getInstance(const node * nA, const node * nB, Attribute * attr[], int Attr, direction dir) const {
  std::vector<edge> * res = new std::vector<edge>;
  Iterator<edge> * itEdges;

  if (this->isValid(attr, nAttr))
    res = getEdges(this->g, nA, nB, attr, nAttr, dir);
  
  return res;
=======
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
>>>>>>> dcd4900c4d501b98b1dcc19f3dbc43eab80a31a7
}


std::vector<edge> * Relation::getInstance(const node * n, Attribute * attr[], int Attr, direction dir) const {
  std::vector<edge> * res = new std::vector<edge>;
  Iterator<edge> * itEdges;
  
  if (this->isValid(attr, nAttr))
    res = getEdges(this->g, n, attr, nAttr, dir);
  
  return res;
}

<<<<<<< HEAD

bool Relation::isValid(Attribute * attr[], int nAttr) const {
   for (int i = 0 ; i < nAttr ; i++) {
    auto it = this->attr.find(attr[i]->getLabel());
    if (it == this->attr.end())
      return false;

    attr[i]->setProperty((*it).second);
  }

  return true;
}


bool Relation::isInstance(const edge * e) const {
  return this->g->isElement(*e);
=======
int Relation::editRelationInstance(const char * nameProperty[], const char * valueProperty[], int len)
{
  struct edge* l;
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
  Iterator<edge> *itEdges = this->g->getEdges();
  while(itEdges->hasNext())
    {
      b=true;
      struct edge e = itEdges->next();
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
>>>>>>> dcd4900c4d501b98b1dcc19f3dbc43eab80a31a7
}

std::string Relation::getName() const{
  return name;
}

int Relation::writeRelation(int fd) const{}
