#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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

  //create the main graphes
  Graph * graph = newGraph();
  Graph * graphE = graph->addSubGraph("Entity");
  Graph * graphR = graphE->addSubGraph("Relation");

  graph->setName("graphGet");
  
  //create an entity
  Attribute * attr[3] = {new Attr<STRING>("Prenom"), new Attr<STRING>("Nom"), new Attr<STRING>("Nationalite")};
  Entity * e = new Entity("Personne", attr, 3, graphE);
  
  //create a relation
  Attribute * attrR[1] = {new Attr<INT>("Date")};
  Relation * r = new Relation("FriendOf", e, e, attrR, 1, graphR);

  //create new instancies of the entity
  STRING prenom;
  STRING nom;
  STRING nationalite;
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

  //add node of the main graph in all subgraphes
  //especially in graphR : in order to create edges, nodes must be in the graph
  vector<node> * nSet = e->getInstance(NULL, 0);
  graphR->addNodes(*nSet);

  Graph * tstGetNode = graphR->addSubGraph("testGetNodes");
  
  Graph * all = graphR->addCloneSubGraph("getInstanceAll");
  Graph * AiB = graphR->addCloneSubGraph("getInstanceAinB");
  Graph * AoB = graphR->addCloneSubGraph("getInstanceAoutB");
  Graph * AioB = graphR->addCloneSubGraph("getInstanceAinoutB");
  Graph * Ai = graphR->addCloneSubGraph("getInstanceAin");
  Graph * Ao = graphR->addCloneSubGraph("getInstanceAout");
  Graph * Aio = graphR->addCloneSubGraph("getInstanceAinout");

  //create new instancies of the relation
  INT date;
  const edge * rList[N_EDGE];
  
  for (int i = 0 ; i < N_NODE ; i++) {
    for (int j = 0 ; j < N_NODE - 1 ; j++) {
      date = (i * 7) % 12 + 1;
      attrR[0]->setValue(&date);
      
      rList[i * (N_NODE - 1) + j] = r->newInstance(nList[i % N_NODE], nList[(i + j + 1) % N_NODE], attrR, 1);
    }
  }
  
  // Get instancies of the entity corresponding to the specified conditions
  Attribute * cond[1] = {new Attr<STRING>("Nom", "Hanin0")}; 
  vector<node> * res = e->getInstance(cond, 1);

  tstGetNode->addNodes(*res);

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

  int tmp = saveGraph(graph, "testGet.tlp");
  if (!tmp)
    cout << "Erreur lors de la sauvegarde" << endl;

  graph->setName("graphSet");

  // Modifies one instance
  // Get all instancies of "Personne" for which 'Prenom' = 'Roger'
  prenom = "Roger";
  cond[0]->setLabel("Prenom");
  cond[0]->setValue(&prenom);
  delete res;
  res = e->getInstance(cond, 1);

  // Change "Nationalite" value for all nodes in res
  nationalite = "péruvienne";
  cond[0]->setLabel("Nationalite");
  cond[0]->setValue(&nationalite);
  e->editInstance(res, cond, 1);

  // Change "Date" value for all edges in resAout
  date = 42;
  attrR[0]->setValue(&date);
  r->editInstance(resAo, attrR, 1);
  
  tmp = saveGraph(graph, "testSet.tlp");
  if (!tmp)
    cout << "Erreur lors de la sauvegarde" << endl;

  graph->setName("graphDel");
  
  //delete one node
  e->delInstance(nList[1]);

  //delete a set of nodes
  res->clear();
  res->push_back(*nList[2]);
  e->delInstance(res);

  //delete one edge
  r->delInstance(rList[2]);

  //delete a set of edges
  resAll->clear();
  resAll->push_back(*rList[9]);
  r->delInstance(resAll);

  tmp = saveGraph(graph, "testDel.tlp");
  if (!tmp)
    cout << "Erreur lors de la sauvegarde" << endl;

  // Entity write test  
  std::fstream file;
  file.open("testEnt.sav", ios_base::out);
  e->write(file);
  file.close();

  e->print();

  // Entity load test
  file.open("testEnt.sav");
  e->load(file, graph);
  e->print();

  file.close();

  // Relation write test
  r->print();
  file.open("testRel.sav", ios_base::out);
  r->write(file);
  file.close();

  // Relation load test
  std::unordered_map<std::string, Entity *> eTab;
  eTab[e->getName()] = e;
  file.open("testRel.sav");
  r->load(file, graph, eTab);
  r->print();
  file.close();

  // Memory liberation
  delAttr(attr, 3);
  delAttr(attrR, 1);
  delAttr(cond, 1);
  
  for (int i = 0 ; i < N_NODE ; i++)
    delete nList[i];

  for (int i = 0 ; i < N_EDGE ; i++)
    delete rList[i];
  
  delete nSet;
  delete res;
  delete resAll;
  delete resAiB;
  delete resAoB;
  delete resAioB;
  delete resAi;
  delete resAo;
  delete resAio;

  delete r;
  delete e;

  delete graph;
  
  return 0;
}
