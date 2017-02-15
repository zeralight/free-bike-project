#include <iostream>

#include <tulip/TlpTools.h>
#include <tulip/Graph.h>
#include <tulip/StringProperty.h>

#include "DBTools.hpp"
#include "Entity.hpp"

using namespace std;
using namespace tlp;

template <class T>
void print(const T tab[], int len) {
  int i;
  cout << "[ ";
  for (i = 0; i < len ; i++) {
    cout << tab[i] << " ";
  }
  cout << "]" << endl;
}

template void print(const std::string [], int);
template void print(const int [], int);

int main() {
  //initialize the Tulip lib
  initTulipLib();

  Attribute * attr[3] = {new Attr<STRING>("Prenom"), new Attr<STRING>("Nom"), new Attr<STRING>("Nationalite")};

  Attribute * tst[2] = {new Attr<INT>("banane", 3), new Attr<STRING>("fraise", "charlotte")};

  //create an empty graph
  Entity * e = new Entity("Personne", attr, 3);
  Graph * graph = e->getGraph();

  //add three nodes
  node n1 = graph->addNode();
  node n2 = graph->addNode();
  node n3 = graph->addNode();
  node n4 = graph->addNode();

  //add three edges
  edge e1 = graph->addEdge(n2,n3);
  edge e2 = graph->addEdge(n1,n2);
  edge e3 = graph->addEdge(n3,n1);

  void * _prop = graph->getLocalProperty("Prenom", "string");
  StringProperty * prop = (StringProperty *) _prop;
  prop->setAllNodeValue("César");

  bool tmp = saveGraph(graph, "test.tlp");
  if (!tmp)
    cout << "Erreur lors de la sauvegarde" << endl;

  delete graph;

  return 0;
}
