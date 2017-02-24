#include "Result.hpp"

using namespace tlp;

Result::Result(Graph * gra, Database * dat):G(gra), db(dat){};

void Result::removeResult(){
  Graph * global = G->getSuperGraph();
  global->delAllSubGraphs(G);
}

bool Result::editResultNodes(Entity& e, Attribute * attr[], int nAttr){
  std::vector<node> * nodes = e.getInstance(attr, nAttr);
  bool res = e.editInstance(nodes, attr, nAttr);
  return res;
}

bool Result::editResultEdges(Relation& r, Attribute * attr[], int nAttr){
  std::vector<edge> * edges = r.getInstance(attr, nAttr);
  bool res = r.editInstance(edges, attr, nAttr);
  return res;
}
