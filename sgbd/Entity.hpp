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
  Entity(const std::string &name, const Attribute * const attributes[], int nAttr);
  ~Entity();

  // Doit disparaitre ou passer private : debug
  Graph * getGraph() const;

  const node * newInstance(Attribute * attr[], int nAttr);
  int delInstance(Attribute * attr[], int nAttr);
  int delInstance(const node * n);
  int editInstance(const char * [] , const char * [] , int);
  const node * getInstance(Attribute * attr[], int nAttr) const;

private:
  bool isValid(const Attribute * const attr[], int nAttr) const;
};

#endif
