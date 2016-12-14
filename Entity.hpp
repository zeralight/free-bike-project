#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <tulip/TlpTools.h>
#include <tulip/Graph.h>
#include <tulip/Node.h>

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
  Entity(Graph* G, std::string ,const char * [], const char * [], int );
  ~Entity();
  int newEntityInstance(const char *[] , const char *[] , int);
  int deleteEntityInstance(const char *[] , const char *[] , int);
  int editEntityInstance(const char *[] , const char *[] , int);
  int getEntityInstance(const char * [], const char * [], int , struct node*);
};

#endif
