#ifndef GESTIONBASE.HPP
#define GESTIONBASE.HPP

Graph* createDataBase();
int deleteDataBase(Graph*);
int importDataBase();
int exportDataBase();

class DataBase{
  static Entity* EntityTab;
  static Relation* RelationTab;

  DataBase();
  ~DataBase();
  
  public:
  addEntity();
  deleteEntity();
  addRelation();
  deleteRelation();
  int importDataBase();
  int exportDataBase();

};


class Entity
{
  Entity();
  
public:
  int newEntityInstance();
  int deleteEntityInstance();
  int editEntityInstance();
};


class Relation
{
  Relation();
  
public:
  int newRelationInstance();
  int editRelationInsatance();
  int deleteRelationInstance();
};



createEdge();
int deleteEdge(Graph *, );
int newEdge();
int editRelationEdge();
int deleteRelationEdge();

#endif
