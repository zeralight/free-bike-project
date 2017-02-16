#include <iostream>
#include <cstring>
#include <set>

#include <tulip/TlpTools.h>
#include <tulip/Graph.h>
#include <tulip/StringProperty.h>
#include <tulip/Node.h>

#include "DBTools.hpp"
#include "Entity.hpp"

#define N_NODE 4

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

  T_STRING prenom;
  T_STRING nom;
  T_STRING nationalite;
  
  //create new instancies of the entity
  const node * nList[N_NODE];
  for (int i = 0 ; i < N_NODE ; i++) {
    prenom = "Roger";
    nom = "Hanin" + to_string(i);
    nationalite = "Israelienne";
    attr[0]->setValue(&prenom);
    attr[1]->setValue(&nom);
    attr[2]->setValue(&nationalite);
    
    nList[i] = e->newInstance(attr, 3);
  }
  
  bool tmp = saveGraph(graph, "test.tlp");
  if (!tmp)
    cout << "Erreur lors de la sauvegarde" << endl;

  // Get instancies corresponding to the specified conditions
  Attribute * cond[1] = {new Attr<STRING>("Nom", "Hanin0")}; 
  set<node> * res = e->getInstance(cond, 1);
  
  tmp = saveGraph(graph->inducedSubGraph(*res), "test1.tlp");
  if (!tmp)
    cout << "Erreur lors de la sauvegarde" << endl;

  for (int i = 0 ; i < 1 ; i++)
    e->delInstance(nList[i]);

  tmp = saveGraph(graph, "test2.tlp");
  if (!tmp)
    cout << "Erreur lors de la sauvegarde" << endl;

  delete graph;

  return 0;
}
