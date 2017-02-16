#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <unordered_map>
#include <set>

#include <tulip/TlpTools.h>
#include <tulip/GraphImpl.h>
#include <tulip/Node.h>

#include "DBTools.hpp"

using namespace tlp;

class Entity {
private:
  std::string name;
  Graph * g;
  std::unordered_map<std::string, Attribute *> attr;
  int nAttr;
  //PropertyInterface ** properties;
  
public: 
  Entity(const std::string &name, const Attribute * const attributes[], int nAttr);
  ~Entity();

  // Doit disparaitre ou passer private : debug
  Graph * getGraph() const;

  const node * newInstance(Attribute * attr[], int nAttr);
  int delInstance(Attribute * attr[], int nAttr);
  int delInstance(const node * n);
  int editInstance(const char * [] , const char * [] , int);
  std::set<node> * getInstance(Attribute * attr[], int nAttr) const;

private:
  bool isValid(Attribute * attr[], int nAttr) const;
};

#endif
