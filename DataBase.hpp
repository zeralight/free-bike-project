#ifndef DATABASE.HPP
#define DATABASE.HPP


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
