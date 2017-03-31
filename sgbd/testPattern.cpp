#include "Database.hpp"
#include "Pattern.hpp"
#include "PatternImpl.hpp"


int main () {
  initDB();
  
  Database * db = newDB("dbTestPattern");

  db->newEntity("Person", NULL, 0);
  db->newRelation("friendOf", "Person", "Person", NULL, 0);
  
  Pattern * p = newPattern(db);

  p->addNode("pA", "Person");
  p->addNode("pB", "Person");
  p->addNode("pA", "Person"); // erreur : pA existe 
  p->addNode("pC", "Doge"); // erreur : Doge n'existe pas
    
  p->addEdge("pB", "friendOf", "pA", "pB"); // erreur : pB existe
  p->addEdge("f1", "friendOf", "pA", "pC");  // erreur : pC n'existe pas
  p->addEdge("f1", "petOf", "pA", "pB");  // erreur : petOf n'existe pas
  p->addEdge("f", "friendOf", "pA", "pB");

  std::cout << std::endl << "Pattern created with :" << std::endl;
  std::cout << "\tnode pA : Person" << std::endl;
  std::cout << "\tnode pB : Person" << std::endl;
  std::cout << "\tedge f : friendOf" << std::endl << std::endl;

  PatternImpl * pi = (PatternImpl *) p;

  node n, nErr;
  edge e, eErr;

  try {
    n = pi->getNode("pA");
    nErr = pi->getNode("pC");
  }
  catch (std::string &errMessage) {
    std::cout << errMessage << std::endl;
  }

  try {      
    e = pi->getEdge("f");
    eErr = pi->getEdge("f1");
  }
  catch (std::string &errMessage) {
    std::cout << errMessage << std::endl;
  }


  Entity * ent = pi->getEntity(n);
  std::cout << "pA : " << ent->getName() << std::endl;

  Relation * rel = pi->getRelation(e);
  std::cout << "f : " << rel->getName() << std::endl;

  std::cout << "pA checked : " << (pi->isChecked(n) ? "yes" : "no") << std::endl;
  std::cout << "f checked : " << (pi->isChecked(n) ? "yes" : "no") << std::endl;

  std::cout << "pA is node : " << (pi->isNode("pA") ? "yes" : "no") << std::endl;
  std::cout << "pA is edge : " << (pi->isEdge("pA") ? "yes" : "no") << std::endl;

  std::cout << "f is node : " << (pi->isNode("f") ? "yes" : "no") << std::endl;
  std::cout << "f is edge : " << (pi->isEdge("f") ? "yes" : "no") << std::endl;

  std::cout << "label pA available : " << (pi->isAvailable("pA") ? "yes" : "no") << std::endl;
  std::cout << "label F6 available : " << (pi->isAvailable("F6") ? "yes" : "no") << std::endl;
  
  pi->debug();

  delPattern(p);
  delDB(db);
}
