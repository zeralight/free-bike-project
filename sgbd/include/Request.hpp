#include "DBTools.hpp"
#include "Result.hpp"
#include "DatabaseImpl.hpp"
#include "ResultImpl.hpp"

using namespace tlp;
using namespace std;

class Request{
private:
  DatabaseImpl *db;
  Graph * g;
  string name;
public:
  Request(Graph *, string, DatabaseImpl*);
  /*
    Fonction in order to get all the nodes of the graph g
   */
  Result* getAllNodes();
  
  /*
    Fonction in order to get all the nodes of the graph which are instance of an specific Entity
   */
  Result* getAllNodes(string entityName);
  
  /*
    Fonction in order to get all the edged of the graph g
   */
  Result* getAllEdges();
  
  /*
    Fonction in order to get all the edges of the graph which are instance of an specific Relation
  */
  Result* getAllEdges(string relationName);

  /*
    Fonctions in order to get the nodes of the instance of entity which label is label and with attribute value is "value"
   */
  Result* getNodes(string entityName, Attribute * attr[], int nAttr);


  /*
    Fonction in order to get the edges of the instance of relation which label is label and with attribute value is "value"
  */
  Result* getEdges(string relationName, Attribute * attr[], int nAttr);

  /*
    Fonction in order to get the nodes which are instance a an Entity and which attribute value is a value of type T and is between v1 and v2
  */
  template<class T>
  Result* getNodes(string entityName, Attribute * attr, T v1, T v2);

  /*
    Fonction in order to get the edges which are instance a an Relation and which value is between v1 and v2 
  */
  template<class T>
  Result* getEdges(string relationName, Attribute * attr, T v1, T v2);
  
  /*
    Fontion in order to get the nodes which are instance a an Entity and which value is superior to value
   */
  template<class T>
  Result* getNodesSup(string entityName, Attribute * attr, T v1);
  
  /*
    Fontion in order to get the edges which are instance a an Relation and which value is superior to value
   */
  template<class T>
  Result* getEdgesSup(string relationName, Attribute * attr, T v1);
  
  /*
    Fontion in order to get the nodes which are instance a an Entity and which value is inferior to value
  */
  template<class T>
  Result* getNodesInf(string entityName, Attribute * attr, T v1);  
  /*
    Fontion in order to get the edges which are instance a an Relation and which value is inferior to value
  */
  template<class T>
    Result* getEdgesInf(string relationName, Attribute * attr, T v1);  
  /*
    Fonction in order to get the subGraph composed of specified Entities and Relations
   */
  Result* getSubGraph(Entity[], Relation[]);
};

