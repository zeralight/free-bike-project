#include <iostream>
#include <cstring>
//#include <cstdlib>
#include <unordered_map>
#include <vector>
//#include <iterator>    inutile vu qu'on utilise auto ?
#include <fstream>

#include <tulip/TlpTools.h>
#include <tulip/Graph.h>
#include <tulip/Edge.h>
#include <tulip/StringProperty.h>

#include "Entity.hpp"
#include "Relation.hpp"
#include "Database.hpp"
#include "DBTools.hpp"
#include "Tools.hpp"

using namespace tlp;


Relation::Relation() {
  this->nameProp = NULL;
  this->entitySrc = NULL;
  this->entityDst = NULL;
  this->g = NULL;
  this->nAttr = 0;
}


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
  } 
}


Relation::~Relation() {
  for (auto it = attr.begin() ; it != attr.end() ; it = attr.erase(it)) 
    delete (*it).second;

  nameProp->setAllNodeValue("");

  Graph * supG = g->getSuperGraph();
  if (supG != g)
    supG->delAllSubGraphs(g);
  else
    delete g;
}


Graph * Relation::getGraph() const {
  return this->g;
}


edge Relation::newInstance(const node &src, const node &dst, Attribute * attr[], int nAttr) {
  edge e;
  
  if (isValid(attr, nAttr)) {
    e = this->g->addEdge(src, dst);
      
    for(int i = 0 ; i < nAttr ; i++)
      attr[i]->setEdgeValue(e);
  }

  return e;
}


void Relation::delInstance(const std::vector<edge> * eSet) {
  for (auto it = eSet->begin() ; it != eSet->end() ; it++)
    this->g->delEdge(*it, true);
}


void Relation::delInstance(const edge &e) {
  this->g->delEdge(e, true);
}


bool Relation::editInstance(edge &e, Attribute * attr[], int nAttr) {
  if (!isInstance(e) || !isValid(attr, nAttr))
    return false;

  for (int i = 0 ; i < nAttr ; i++)
    attr[i]->setEdgeValue(e);

  return true;
}


bool Relation::editInstance(std::vector<edge> * eSet, Attribute * attr[], int nAttr) {
  bool res = true;
  edge e;
  
  for (auto it = eSet->begin() ; it != eSet->end() ; it++) {
    e = *it;
    res = res && editInstance(e, attr, nAttr);
  }

  return res;
}

std::vector<edge> * Relation::getInstance(Attribute * attr[], int nAttr) const {
  if (this->isValid(attr, nAttr))
    return getEdges(this->g, attr, nAttr);
  else
    return new std::vector<edge>;
}


std::vector<edge> * Relation::getInstance(const node &nA, const node &nB, Attribute * attr[], int nAttr, direction dir) const {
  if (this->isValid(attr, nAttr))
    return getEdges(this->g, nA, nB, attr, nAttr, dir);
  else
    return new std::vector<edge>;
}


std::vector<edge> * Relation::getInstance(const node &n, Attribute * attr[], int nAttr, direction dir) const {
  if (this->isValid(attr, nAttr))
    return getEdges(this->g, n, attr, nAttr, dir);
  else
    return new std::vector<edge>;
}


bool Relation::isValid(Attribute * attr[], int nAttr) const {
  for (int i = 0 ; i < nAttr ; i++) {
    auto it = this->attr.find(attr[i]->getLabel());
    if (it == this->attr.end())
      return false;
    
    attr[i]->setProperty((*it).second);
  }
  
  return true;
}


bool Relation::isInstance(const edge &e) const {
  return this->g->isElement(e);
}

std::string Relation::getName() const{
  return name;
}


void Relation::write(std::fstream &file) const {
  std::string buff;
  Attribute * tmp;
  
  if (!file)
    return;

  buff += "(relation " + this->name + " ";
  buff += entitySrc->getName() + " ";
  buff += entityDst->getName() + "\n";

  for (auto it = attr.begin() ; it != attr.end() ; it++) {
    tmp = ((*it).second);
    buff += "\t(attr " + tmp->getLabel() + " " + tmp->getTypeName() + ")\n";
  }

  buff += ")";

  file << buff.c_str();
}


void Relation::load(std::fstream &file, Graph * gSrc, std::unordered_map<std::string, Entity *> &entityList) {
  std::string buff;
  int openPar = 0;
  bool read = false;

  if (!file)
    return;

  // Load data from file
  while(openPar > 0 || !read) {
    buff = getWord(file);
    read = true;
    
    if (buff == "(")
      openPar++;
    else if (buff == ")")
      openPar--;
    else if (buff == "relation" && read) {
      this->name = getWord(file);
      this->nameProp = gSrc->getLocalProperty<StringProperty>(PROP_RELATION_NAME);
      std::string nameSrc = getWord(file);
      std::string nameDst = getWord(file);
      this->entitySrc = entityList[nameSrc];
      this->entityDst = entityList[nameDst];

      this->g = gSrc->getSubGraph(this->name);
      if (this->g == NULL)
	throw std::string("ERROR: impossible to load the relation " + this->name);
    }
    else if (buff == "attr" && read) {
      std::string name = getWord(file);
      std::string typeName = getWord(file);
      Attribute * tmp = newAttr(name, typeName);
      this->attr[name] = tmp;

      // Initialize property from graph
      this->attr[name]->setProperty(this->g);
    }
    else {
      std::cout << "Error loading Relation: bad format '" + buff + "'" << std::endl;
      for (int i = 0 ; i < buff.size() ; i++)
	file.unget();
      break;
    }
  }
}


void Relation::print() {
  std::cout << "==== rel:" << name << " ====" << std::endl;
  std::cout << entitySrc->getName() << " --> " << entityDst->getName() << std::endl;

  for (auto it = attr.begin() ; it != attr.end() ; it++)
    ((*it).second)->print(); 
}

