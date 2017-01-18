#ifndef RELATION_HPP
#define RELATION_HPP
#include <tulip/TlpTools.h>
#include <tulip/Graph.h>
#include <tulip/Edge.h>
#include <tulip/Node.h>

using namespace tlp;

class Relation
{
private:
  char * nameProperty[]; 
  char * typeProperty[];
  PropertyInterface* property[];
  Graph * g;
  int len;
  
public: 
  Relation(Graph* G, std::string ,const char * [], const char * [], int );
  ~Relation();
  int newRelationInstance(const char *[] , const char *[] , const node, const node, int);
  int deleteRelationInstance(const char *[] , const char *[] , int);
  int editRelationInstance(const char *[] , const char *[] , int);
  int getRelationInstance(const char * [], const char * [], int , struct edge*);
};

#endif
