#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <string>
#include <tulip/Node.h>
#include <tulip/Edge.h>

#include "DBTools.hpp"
#include "Result.hpp"

/**
 * @brief This class is the core of the Database Management System.
 *
 * Remark : The file <DBTools.hpp> must be inserted in order to use certain data types like : Attr, AttrType and AttrValue.
 *          See this file for more details on its use.
 *
 **/
class Database {
public:
  /**
   * @brief Creation of an entity.
   *
   * This method creates a new entity in the database, i.e. a particular type of node in the graph.
   * An entity has a name, and can have specific attributes. Its kind of a template for a node, it defines
   what are the number, the labels and the types of the attributes.
   * For exemple, an entity 'Person' which has three attributes 'name', 'lastname' and 'age' can be created this way:
   * @code
   * Database * db = newDB("DB");
   * AttrType tab[3] = {AttrType("name", STRING), AttrType("lastname", STRING), AttrType("age", INT)};
   * db->newEntity("Person", tab, 3);
   * @endcode
   *
   * @param name entity's name
   * @param attributes list of couples (label, type) describing the attributes of the entity, could be NULL
   * @param nAttr number of attributes
   *
   **/
  virtual void newEntity(std::string name, const Attribute attributes[], int nAttr) =0;


  /**
   * @brief Insertion of a new instance of an entity in the database.
   *
   * The attributes indicated in the argument 'values' must correspond to the description of the entity used, i.e. the label and the type of the value.
   *
   * @param entityName name of the entity which acts as a model
   * @param values list of couples (label, value) describing the attributes of the node, could be NULL
   * @param nVal number of filled attributes (size of 'value')
   *
   * @return const node * : a pointer to the newly created node in the database
   **/
  virtual const Result * newNode(std::string entityName, const Attribute values[], int nVal) =0;


  /**
   * @brief Insertion of a new node in the database.
   *
   * This function can be used to insert a singular node which doesn't correspond to an existing entity.
   *
   * @param attributes list of triplets (label, type, value) describing the attributes of the node, cannot be NULL
   * @param nAttr number of attributes
   *
   * @return const node * : a pointer to the newly created node in the database
   **/
  virtual const Result * newNode(const Attribute attributes[], int nAttr) =0;


  /**
   * @brief Creation of a relation.
   *
   * This method creates a new relation in the database, i.e. a particular type of edge in the graph.
   * A relation has a name, a source entity, a destination entity and can have specific attributes.
   * Its kind of a template for an edge, it defines what are the number of attributes and the labels and the types of them.
   * Moreover a relation describes a directed edge, and the type of the source and destination nodes must be indicated.
   * For exemple, an relation 'FriendOf' between two 'Person' which has one attribute 'meetingDate' can be created this way :
   * @code
   * Database * db = newDB("DB");
   * AttrType tab[1] = {AttrType("meetingDate", DATE)};
   * db->newRelation("FriendOf", "Person", "Person", tab, 1);
   * @endcode
   *
   * @param relationName relation's name
   * @param entitySrc name of source entity (must exist in the database)
   * @param entityDst name of destination entity (idem)
   * @param attributes list of couples (label, type) describing the attributes of the relation, could be NULL
   * @param nAttr number of attributes
   *
   **/
  virtual void newRelation(std::string relationName, std::string entitySrc, std::string entityDst, const Attribute attributes[], int nAttr) =0;


  /**
   * @brief Insertion in the database of a new edge shaped on an existing relation.
   *
   * The attributes indicated in the argument 'values' must correspond to the description of the relation used, i.e. same labels and same types for the associated values.
   *
   * @param relationName name of the relation acting as the model
   * @param src source node
   * @param dst destination node
   * @param values list of couples (label, value) describing the attributes' values of the edge, could be NULL
   * @param nVal number of indicated attributes (size of 'values')
   *
   **/
  virtual void newEdge(std::string relationName, const Result * src, const Result * dst, const Attribute values[], int nVal) =0;


  /**
   * @brief Insertion in the database of a new edge.
   *
   * This function can be used to insert a singular edge which doesn't correspond to an existing relation.
   *
   * @param name name of the edge
   * @param src source node
   * @param dst destination node
   * @param attributes list of triplets (label, type, value) describing the attributes' values of the edge, could be NULL
   * @param nAttr number of attributes
   *
   **/
  virtual void newEdge(std::string name, const Result * src, const Result * dst, const Attribute attributes[], int nAttr) =0;


  /**
   * @brief Save the database on disk at a specified location.
   *
   * @param path absolute path to the location where the database must be saved
   *
   * @return
   **/
  virtual int saveDB(std::string path) const =0;


  /**
   * @brief Load a database from a specified location in a Database object.
   *
   * @param path absolute path to the location of the database
   *
   * @return Database * : a pointer to the loaded Database object
   **/
  virtual Database * loadDB(std::string path, const std::string name) const =0;
};


/**
 * @brief Creation of a new database.
 *
 * @param name name of the database
 *
 * @return Database * : pointer to the newly created Database object.
 **/
Database * newDB(std::string name);


/**
 * @brief Deletion of a Database Object, all associated resources are freed.
 *
 * This function doesn't save the database before deleting the object.
 * One must ensure to have saved it with the saveDB() method before calling this function.
 *
 * @param db pointer to the Database object which must be deleted.
 **/
void delDB(Database * db);


#endif
