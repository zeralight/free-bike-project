#include <iostream>
#include <cstring>
#include <set>

#include <tulip/TlpTools.h>
#include <tulip/Graph.h>
#include <tulip/StringProperty.h>
#include <tulip/Node.h>

#include "DBTools.hpp"
#include "Entity.hpp"
#include "Relation.hpp"

#define N_NODE 4
#define N_EDGE 12

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

  Graph * graph = newGraph();
  Graph * graphE = graph->addSubGraph("Entity");

  //graph->getLocalProperty<StringProperty>("dbEntityName");  
  //graph->getLocalProperty<StringProperty>("dbRelationName");  
  
  //create an entity
  Attribute * attr[3] = {new Attr<STRING>("Prenom"), new Attr<STRING>("Nom"), new Attr<STRING>("Nationalite")};
  Entity * e = new Entity("Personne", attr, 3, graphE);

  Graph * graphR = graphE->addSubGraph("Relation");
  
  //create a relation
  Attribute * attrR[1] = {new Attr<INT>("Date")};
  Relation * r = new Relation("FriendOf", e, e, attrR, 1, graphR);
  
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

  set<node> * nSet = e->getInstance(NULL, 0); 
  graphR->addNodes(vector<node>(nSet->begin(), nSet->end()));

  Graph * all = graphR->addCloneSubGraph("getInstanceAll");
  Graph * AiB = graphR->addCloneSubGraph("getInstanceAinB");
  Graph * AoB = graphR->addCloneSubGraph("getInstanceAoutB");
  Graph * AioB = graphR->addCloneSubGraph("getInstanceAinoutB");
  Graph * Ai = graphR->addCloneSubGraph("getInstanceAin");
  Graph * Ao = graphR->addCloneSubGraph("getInstanceAout");
  Graph * Aio = graphR->addCloneSubGraph("getInstanceAinout");

  T_INT date;
  
  //create new instancies of the relation
  const edge * rList[N_NODE * (N_NODE - 1)];
  for (int i = 0 ; i < N_NODE ; i++) {
    for (int j = 0 ; j < N_NODE - 1 ; j++) {
      date = (i * 7) % 12 + 1;
      attrR[0]->setValue(&date);
      
      rList[i * N_NODE + j] = r->newInstance(nList[i % N_NODE], nList[(i + j + 1) % N_NODE], attrR, 1);
    }
  }

  bool tmp = saveGraph(graph, "test.tlp");
  if (!tmp)
    cout << "Erreur lors de la sauvegarde" << endl;

  // Get instancies of the entity corresponding to the specified conditions
  Attribute * cond[1] = {new Attr<STRING>("Nom", "Hanin0")}; 
  set<node> * res = e->getInstance(cond, 1);

  // Get instancies of the relation corresponding to the specified conditions
  date = 1;
  attrR[0]->setValue(&date);
  int nAttrR = 0;

  vector<edge> * resAll = r->getInstance(attrR, nAttrR);
  vector<edge> * resAiB = r->getInstance(nList[0], nList[1 % N_NODE], attrR, nAttrR, IN);
  vector<edge> * resAoB = r->getInstance(nList[0], nList[1 % N_NODE], attrR, nAttrR, OUT);
  vector<edge> * resAioB = r->getInstance(nList[0], nList[1 % N_NODE], attrR, nAttrR, INOUT);
  vector<edge> * resAi = r->getInstance(nList[0], attrR, nAttrR, IN);
  vector<edge> * resAo = r->getInstance(nList[0], attrR, nAttrR, OUT);
  vector<edge> * resAio = r->getInstance(nList[0], attrR, nAttrR, INOUT);

  all->addEdges(*resAll);
  AiB->addEdges(*resAiB);
  AoB->addEdges(*resAoB);
  AioB->addEdges(*resAioB);
  Ai->addEdges(*resAi);
  Ao->addEdges(*resAo);
  Aio->addEdges(*resAio);
  
  tmp = saveGraph(graph, "test1.tlp");
  if (!tmp)
    cout << "Erreur lors de la sauvegarde" << endl;

  e->delInstance(nList[1]);
  e->delInstance(res);

  // Modifies one instance
  // Get all instancies of "Personne" for which 'Prenom' = 'Roger'
  prenom = "Roger";
  cond[0]->setLabel("Prenom");
  cond[0]->setValue(&prenom);
  res = e->getInstance(cond, 1);

  // Change "Nationalite" value for all nodes in res
  nationalite = "péruvienne";
  cond[0]->setLabel("Nationalite");
  cond[0]->setValue(&nationalite);
  e->editInstance(res, cond, 1);

  tmp = saveGraph(graph, "test2.tlp");
  if (!tmp)
    cout << "Erreur lors de la sauvegarde" << endl;

  delete graph;
  //delete graphE;
  //delete graphR;

  return 0;
}
