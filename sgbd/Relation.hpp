#ifndef RELATION_HPP
#define RELATION_HPP

#include <unordered_map>
#include <set>

#include <tulip/TlpTools.h>
#include <tulip/Graph.h>
#include <tulip/Edge.h>

#include "DBTools.hpp"

#define PROP_RELATION_NAME "dbRelationName"

using namespace tlp;

class Relation {
  
private:
<<<<<<< HEAD
  std::string name;
  StringProperty * nameProp;
  Entity * entitySrc;
  Entity * entityDst;
  Graph * g;
  std::unordered_map<std::string, Attribute *> attr;
  int nAttr;
  
public: 
  Relation(const std::string &name, Entity * src, Entity * dst, const Attribute * const attr[], int nAttr, Graph * g);
  ~Relation();

  // Doit disparaitre ou passer private : debug
  Graph * getGraph() const;
  
  const edge * newInstance(const node * src, const node * dst, Attribute * attr[], int nAttr);
  void delInstance(const std::vector<edge> * eSet);
  void delInstance(const edge * e);
  bool editInstance(std::vector<edge> * eSet, Attribute * attr[], int nAttr);
  bool editInstance(edge * e, Attribute * attr[], int nAttr);
  std::vector<edge> * getInstance(Attribute * attr[], int Attr) const;
  std::vector<edge> * getInstance(const node * n, Attribute * attr[], int Attr, direction dir) const;
  std::vector<edge> * getInstance(const node * nA, const node * nB, Attribute * attr[], int Attr, direction dir) const;
  
  bool isInstance(const edge * e) const;
  
private:
  bool isValid(Attribute * attr[], int nAttr) const;
=======
  char * nameProperty[];
  char * typeProperty[];
  PropertyInterface* property[];
  Graph * g;
  int len;
  std::string name;

public:
  Relation(Graph* G, std::string ,const char * [], const char * [], int );
  ~Relation();
  int newRelationInstance(const char *[] , const char *[] , const node, const node, int);
  int deleteRelationInstance(const char *[] , const char *[] , int);
  int editRelationInstance(const char *[] , const char *[] , int);
  int getRelationInstance(const char * [], const char * [], int , struct edge*);
  std::string getName() const;
  int writeRelation(int fd) const;
  int load(char * l);
>>>>>>> dcd4900c4d501b98b1dcc19f3dbc43eab80a31a7
};

#endif
