#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <tulip/TlpTools.h>
#include <tulip/GraphImpl.h>
#include <tulip/Node.h>

#include "DBTools.hpp"

using namespace tlp;

class Entity {
private:
  std::string name;
  Graph * g;
  Attribute ** attr;
  int nAttr;
  //PropertyInterface ** properties;
  
public: 
  Entity(const std::string name, const Attribute * const attributes[], int nAttr);
  ~Entity();

  // Doit disparaitre ou passer private : debug
  Graph * getGraph() const;

  const node * newInstance(const Attribute * const attr[], int nAttr);
  int delInstance(const char * [] , const char * [] , int);
  int editInstance(const char * [] , const char * [] , int);
  int getInstance(const char * [], const char * [], int , struct node*) const;

private:
  bool isValid(const Attribute * const attr[], int nAttr) const;
};

#endif
