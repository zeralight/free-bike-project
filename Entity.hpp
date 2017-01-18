#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <tulip/TlpTools.h>
#include <tulip/Graph.h>

using namespace tlp;

class Entity
{
private:
  char * nameProperty[]; 
  char * typeProperty[];
  PropertyInterface* property[];
  Graph * g;
  int len;
  
public: 
  Entity(std::string , const char * [], const char * [], int);
  ~Entity();
  int newEntityInstance(const char *[] ,const char *[] , int);
  int deleteEntityInstance(const char * nameProperty[], const char * valueProperty[], int len);
  int editEntityInstance(const char * nameProperty[], const char * valueProperty[], int len);
private:
  int getEntityInstance(const char * nameProperty[], const char * valueProperty[], int len, node[] l)
};

#endif
