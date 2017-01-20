#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <tulip/TlpTools.h>
#include <tulip/GraphImpl.h>
#include <tulip/Node.h>

using namespace tlp;

class Entity : public GraphImpl {
private:
  std::string name;
  std::string * attrNames; 
  std::string * attrTypes;
  //PropertyInterface ** properties;
  int nAttr;
  
public: 
  Entity(const std::string, const std::string [], const std::string [], int);
  ~Entity();
  int newEntityInstance(const char * [] , const char * [] , int);
  int deleteEntityInstance(const char * [] , const char * [] , int);
  int editEntityInstance(const char * [] , const char * [] , int);
  int getEntityInstance(const char * [], const char * [], int , struct node*);
};

#endif
