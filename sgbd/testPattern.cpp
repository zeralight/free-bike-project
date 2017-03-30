#include "Database.hpp"
#include "Pattern.hpp"


int main () {
  initDB();
  
  Database * db = newDB("dbTestPattern");
  Pattern * p = newPattern(db);

  p->addNode("pA", "Person");
  p->addNode("pB", "Person");
  p->addNode("pA", "Doge"); // erreur

  p->addEdge("pB", "friendOf", "pA", "pB"); // erreur
  p->addEdge("f1", "petOf", "pA", "pC");  // erreur
  p->addEdge("f", "friendOf", "pA", "pB");
  
  p->debug();

  delPattern(p);
  delDB(db);
}
