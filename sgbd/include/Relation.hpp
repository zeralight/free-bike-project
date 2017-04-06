#ifndef RELATION_HPP
#define RELATION_HPP

#include <unordered_map>
#include <vector>
#include <fstream>

#include <tulip/TlpTools.h>
#include <tulip/Graph.h>
#include <tulip/Edge.h>

#include "DBTools.hpp"

#define PROP_RELATION_NAME "dbRelationName"

using namespace tlp;

class Relation {
  
private:
  std::string name;
  StringProperty * nameProp;
  const Entity * entitySrc;
  const Entity * entityDst;
  Graph * g;
  std::unordered_map<std::string, Attribute *> attr;
  int nAttr;
  
public:
  Relation();
  Relation(const std::string &name, Entity * src, Entity * dst, const Attribute * const attr[], int nAttr, Graph * g);
  ~Relation();

  // Doit disparaitre ou passer private : debug
  Graph * getGraph() const;
  
  edge newInstance(const node &src, const node &dst, Attribute * attr[], int nAttr);
  void delInstance(const std::vector<edge> * eSet);
  void delInstance(const edge &e);
  bool editInstance(std::vector<edge> * eSet, Attribute * attr[], int nAttr);
  bool editInstance(edge &e, Attribute * attr[], int nAttr);
  std::vector<edge> * getInstance(Attribute * attr[], int Attr, int cmpOp) const;
  std::vector<edge> * getInstance(Graph * g, Attribute * attr[] = NULL, int nAttr = 0, int cmpOp = EQUAL) const;
  std::vector<edge> * getInstance(const node &n, Attribute * attr[], int Attr, direction dir, int cmpOp) const;
  std::vector<edge> * getInstance(const node &nA, const node &nB, Attribute * attr[], int Attr, direction dir, int cmpOp) const;
  std::string getName() const;
  Attribute * getAttr(const std::string &name, edge e);
  
  void write(std::fstream &file) const;
  void load(std::fstream &file, Graph * gSrc, std::unordered_map<std::string, Entity *> &entityList);
  void print();
  std::string debug(bool getArgs);

  bool isInstance(const edge &e) const;
  bool isValid(Attribute * attr[], int nAttr) const;
  
  bool verify(const Entity * src, const Entity * dst) const;
  bool verify(const node &src, const node &dst) const;
};

#endif
