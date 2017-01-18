#ifndef DATABASE_HPP
#define DATABASE_HPP

#define DB_NB_ENTITIES_DEFAULT 1
#define DB_NB_RELATIONS_DEFAULT 1

class DataBase {
  Entity ** entities;
  Relation ** relations;
  Graph * graph;

  DataBase(char *);
  ~DataBase();
  
  public:
  addEntity();
  delEntity();
  addRelation();
  delRelation();
  insert();
  remove();
  int importDataBase();
  int exportDataBase();

};

#endif
