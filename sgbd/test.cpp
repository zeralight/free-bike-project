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

  //create an entity
  Attribute * attr[3] = {new Attr<STRING>("Prenom"), new Attr<STRING>("Nom"), new Attr<STRING>("Nationalite")};
  Entity * e = new Entity("Personne", attr, 3);
  Graph * graph = e->getGraph();

  //create new instancies of the entity
  
  bool tmp = saveGraph(graph, "test.tlp");
  if (!tmp)
    cout << "Erreur lors de la sauvegarde" << endl;

  delete graph;

  return 0;
}
