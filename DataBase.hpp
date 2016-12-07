#ifndef DATABASE_HPP
#define DATABASE_HPP


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

#endif
