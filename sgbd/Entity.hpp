#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <unordered_map>
#include <vector>
#include <fstream>

#include <tulip/TlpTools.h>
#include <tulip/Graph.h>
#include <tulip/Node.h>

#include "DBTools.hpp"

#define PROP_ENTITY_NAME "dbEntityName"

using namespace tlp;

class Entity {
private:
  std::string name;
  StringProperty * nameProp;
  Graph * g;
  std::unordered_map<std::string, Attribute *> attr;
  int nAttr;

public:
  Entity();
  Entity(const std::string &name, const Attribute * const attributes[], int nAttr, Graph * g);
  ~Entity();

  // Doit disparaitre ou passer private : debug
  Graph * getGraph() const;

  node newInstance(Attribute * attr[], int nAttr);
  void delInstance(const std::vector<node> * nSet);
  void delInstance(const node &n); // redondant ?
  bool editInstance(std::vector<node> * nSet, Attribute * attr[], int nAttr);
  bool editInstance(node &n, Attribute * attr[], int nAttr);
  std::vector<node> * getInstance(Attribute * attr[], int nAttr) const;
  bool isInstance(const node &n) const;
  std::string getName() const;
  void write(std::fstream &file) const;
  void load(std::fstream &file, Graph * gSrc);
  void print();

private:
  bool isValid(Attribute * attr[], int nAttr) const;
};

std::string getWord(std::fstream &file);

#endif
