/*#include
 */

class Request{
private:
  Graph * g;
  string name;
public:
  Request(Graph *);
  /*
    Fonction in order to get all the nodes of the graph g
   */
  Result getAllNodes();
  
  /*
    Fonction in order to get all the nodes of the graph which are instance of an specific Entity
   */
  Result getAllNodes(const Entity &);
  
  /*
    Fonction in order to get all the edged of the graph g
   */
  Result getAllEdges();
  
  /*
    Fonction in order to get all the edges of the graph which are instance of an specific Relation
  */
  Result getAllEgdes(const Relation &);

  /*
    Fonctions in order to get the nodes of the instance of entity which label is label and with attribute value is "value"
   */
  Result getNodes(const Entity &, const int value);
  Result getNodes(const Entity &, const double value);
  Result getNodes(const Entity &, const bool value);
  Result getNodes(const Entity &, const string value);

  /*
    Fonction in order to get the edges of the instance of relation which label is label and with attribute value is "value"
  */
  Result getEdges(const Relation &, const int value);
  Result getEdges(const Relation &, const double value);
  Result getEdges(const Relation &, const bool value);
  Result getEdges(const Relation &, const string value);

  /*
    Fonction in order to get the nodes which are instance a an Entity and which value is between v1 and v2 
  */
  Result getNodes(const Entity &, const int v1, const int v2);
  Result getNodes(const Entity &, const double v1, const double v2);
  Result getNodes(const Entity &, const string v1, const string v2);

  /*
    Fonction in order to get the edges which are instance a an Relation and which value is between v1 and v2 
  */
  Result getEdges(const Entity &, const int v1, const int v2);
  Result getEdges(const Entity &, const double v1, const double v2);
  Result getEdges(const Entity &, const string v1, const string v2);

  /*
    Fontion in order to get the nodes which are instance a an Entity and which value is superior to value
   */
  Result getNodesSup(const Entity &, const int value);
  Result getNodesSup(const Entity &, const double value);
  Result getNodesSup(const Entity &, const string value);
  
  /*
    Fontion in order to get the edges which are instance a an Relation and which value is superior to value
   */
  Result getEdgesSup(const Relation &, const int value);
  Result getEdgesSup(const Relation &, const double value);
  Result getEdgesSup(const Relation &, const string value);
  
  /*
    Fontion in order to get the nodes which are instance a an Entity and which value is inferior to value
  */
  Result getNodesInf(const Entity &, const int value);
  Result getNodesInf(const Entity &, const double value);
  Result getNodesInf(const Entity &, const string value);
  
  /*
    Fontion in order to get the edges which are instance a an Relation and which value is inferior to value
  */
  Result getEdgesInf(const Relation &, const int value);
  Result getEdgesInf(const Relation &, const double value);
  Result getEdgesInf(const Relation &, const string value);

  /*
    Fonction in order to get the subGraph composed of specified Entities and Relations
   */
  Result getSubGraph(Entity&[], Relation&[]);
};
