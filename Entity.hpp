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
  Entity(std::string , char * [],char * [], int );
  ~Entity();
  int newEntityInstance(char *[] , char *[] , int);
  int deleteEntityInstance(char * nameProperty[], char * valueProperty[], int len);
  int editEntityInstance(char * nameProperty[], char * valueProperty[], int len);
};

#endif
