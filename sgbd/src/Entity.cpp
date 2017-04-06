#include <iostream>
#include <fstream>
#include <cstring>
#include <unordered_map>
#include <vector>
#include <iterator>
#include <unistd.h>

#include <tulip/TlpTools.h>
#include <tulip/Graph.h>
#include <tulip/Node.h>
#include <tulip/StringProperty.h>

#include "Database.hpp"
#include "Entity.hpp"
#include "DBTools.hpp"
#include "Tools.hpp"

using namespace tlp;


Entity::Entity() {
  this->nameProp = NULL;
  this->g = NULL;
  this->nAttr = 0;
}


Entity::Entity(const std::string &name, const Attribute * const attr[], int nAttr, Graph * g) {
  this->g = g;
  
  // Initialize nodes with entity's name
  this->name = name;
  this->nameProp = this->g->getProperty<StringProperty>(PROP_ENTITY_NAME);

  // Creation of all properties
  this->nAttr = nAttr;
  for(int i = 0 ; i < nAttr ; i++) {
    this->attr[attr[i]->getLabel()] = attr[i]->clone();
    this->attr[attr[i]->getLabel()]->setProperty(this->g->getLocalProperty(attr[i]->getLabel(), attr[i]->getTypeName()));

    //initialisation ? ou Tulip le fait par défaut ?
  }
}


Entity::~Entity() {
  for (auto it = attr.begin() ; it != attr.end() ; it = attr.erase(it)) 
    delete (*it).second;
  
  nameProp->setAllNodeValue("");

  Graph * supG = g->getSuperGraph();
  if (supG != g)
    supG->delAllSubGraphs(g);
  else
    delete g;
}


Graph * Entity::getGraph() const {
  return this->g;
}


node Entity::newInstance(Attribute * attr[], int nAttr) {
  node n;

  if (isValid(attr, nAttr)) {
    n = this->g->addNode();
    this->nameProp->setNodeValue(n, this->name);
    
    for(int i = 0 ; i < nAttr ; i++)
      attr[i]->setNodeValue(n);
  }

  return n;
}


void Entity::delInstance(const std::vector<node> * nSet) {
  for (auto it = nSet->begin() ; it != nSet->end() ; it++)
    this->g->delNode(*it, true);
}


void Entity::delInstance(const node &n) {
  this->g->delNode(n, true);
}


bool Entity::editInstance(node &n, Attribute * attr[], int nAttr) {
  if (!isInstance(n) || !isValid(attr, nAttr))
    return false;

  for (int i = 0 ; i < nAttr ; i++)
    attr[i]->setNodeValue(n);

  return true;
}


bool Entity::editInstance(std::vector<node> * nSet, Attribute * attr[], int nAttr) {
  bool res = true;
  node n;
  
  for (auto it = nSet->begin() ; it != nSet->end() ; it++) {
    n = *it;
    res = res && editInstance(n, attr, nAttr);
  }

  return res;
}


std::vector<node> * Entity::getInstance(Attribute * attr[], int nAttr, int cmpOp) const {
  if (this->isValid(attr, nAttr)) {
    return getNodes(this->g, attr, nAttr, cmpOp);
  }
  else
    return new std::vector<node>;
}


std::vector<node> * Entity::getInstance(Graph * g, Attribute * attr[], int nAttr, int cmpOp) const {
  std::vector<node> * nodes = getInstance(attr, nAttr, cmpOp);

  for(auto it = nodes->begin() ; it != nodes->end() ; it++) {
    if (!g->isElement(*it)) {
      it = nodes->erase(it);
      it--;
    }
    
  }
  
  return nodes;
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


bool Entity::isInstance(const node &n) const {
  return this->g->isElement(n);
}


std::string Entity::getName() const{
  return name;
}


Attribute * Entity::getAttr(const std::string &name, node n) {
  if (attr.find(name) == attr.end())
    throw std::string("ERROR: the attribute" + name + "doesn't exist");
  
  if (!this->isInstance(n))
    throw std::string("ERROR: the node doesn't belong to the entity '" + this->name + "'");
  
  Attribute * ret = attr[name]->clone();
  ret->getNodeValue(n);

  return ret;
}


void Entity::write(std::fstream &file) const {
  std::string buff;
  Attribute * tmp;

  if (!file)
    return;

  buff += "(entity " + this->name + "\n"; 

  for (auto it = attr.begin() ; it != attr.end() ; it++) {
    tmp = ((*it).second);
    buff += "\t(attr " + tmp->getLabel() + " " + tmp->getTypeName() + ")\n";
  }

  buff += ")\n";

  file << buff.c_str();
}


std::string getWord(std::fstream &file) {
  std::string buff;
  char c;

  if (!file)
    return buff;
  
  while(buff.size() == 0 && !file.eof()) {
    file.get(c);
    if (c == '(' ||
	c == ')')
      buff = c;
    else {
      while (c != ' ' &&
	     c != '\n' &&
	     c != '\t' &&
	     c != '(' &&
	     c != ')' &&
	     !file.eof()) {
	buff += c;
	file.get(c);
      }
      
      if (c == '(' ||
	  c == ')')
	file.unget();  
    }
  }
    
  return buff;
}


void Entity::load(std::fstream &file, Graph * gSrc) {
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
    else if (buff == "entity" && read) {
      this->name = getWord(file);
      this->nameProp = gSrc->getLocalProperty<StringProperty>(PROP_ENTITY_NAME);

      this->g = gSrc->getSubGraph(this->name);
      if (this->g == NULL)
	throw std::string("ERROR: impossible to load the entity " + this->name);
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
      std::cout << "Error loading Entity: bad format '" + buff + "'" << std::endl;
      for (int i = 0 ; i < buff.size() ; i++)
	file.unget();
      break;
    }
  }
}


void Entity::print() {
  std::cout << debug(true) << std::endl;
}


std::string Entity::debug(bool getArgs) {
  std::string ret;
  ret = "ent:'" + this->name + "'";
  
  if (getArgs) {
    ret += " :";
    for (auto it = attr.begin() ; it != attr.end() ; it++)
      ret += "\n" + ((*it).second)->debug();
  }
  
  return ret;
}

