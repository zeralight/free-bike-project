#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <string>
#include <tulip/Graph.h>
#include <tulip/Node.h>
#include <tulip/Edge.h>

#include "DBTools.hpp"
//#include "Result.hpp"

class Result;
class Pattern;

/**
 * @brief This class is the core of the Database Management System.
 *
 * It describes all the functions used to create, delete, and more generally manipulate a graph database.
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
  virtual void newEntity(const std::string &name, const Attribute * const attr[], int nAttr) =0;


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
  virtual Result * newNode(const std::string &entityName, Attribute * attr[], int nVal) =0;


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
  virtual void newRelation(const std::string &relationName, const std::string &entitySrc, const std::string &entityDst, const Attribute * const attr[], int nAttr) =0;


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
  virtual void newEdge(const std::string &relationName, const Result * src, const Result * dst, Attribute * attr[], int nAttr) =0;

  
  /**
   * @brief Edition of nodes in the Database
   *
   * 
   * This method edits the instances of the entity specified by 'entityName'. The new values with which they are modified are put in the Attribute elements of the array 'attr'. 
   * Only existing attributes for 'entityName' are accepted, if only one argument is incorrect, the method fails.
   *
   * @param entityName name of the edited nodes' entity 
   * @param attr list of the attributes to modify and their new value
   * @param nAttr size of attr
   *
   * @return bool : whether the edition was successful or not
   *
   * @sa Attribute to know how to put a desired value in an Attribute object
   **/
  virtual bool editNodes(const std::string &entityName, Attribute * attr[], int nAttr) =0;

  
  /**
   * @brief Edition of edges in the Database
   *
   *
   * This method edits the instances of the relation specified by 'relationName'. The new values with which they are modified are put in the Attribute elements of the array 'attr'. 
   * Only existing attributes for 'relationName' are accepted, if only one argument is incorrect, the method fails.
   *
   * @param entityName name of the edited nodes' entity 
   * @param attr list of the attributes to modify and their new value
   * @param nAttr size of attr
   *
   * @return bool : whether the edition was successful or not
   *
   * @sa Attribute to know how to put a desired value in an Attribute object
   **/
  virtual bool editEdges(const std::string &relationName, Attribute * attr[], int nAttr) =0;


  /**
   * @brief Save the database on disk at a specified location.
   *
   * @param path absolute path to the location where the database must be saved
   *
   **/
  virtual void save(const std::string &path) const =0;


  /**
   * @brief Loads a database from a specified location in the Database object.
   *
   * @warning the current database will be completely erased, be sure to save before loading a database. It might be prefered to create an empty Database object before loading an existing base.
   * 
   * @param path absolute path to the location of the database
   *
   **/
  virtual void load(const std::string &path) =0;

  
  /**
   * @brief Matching of pattern in the database 
   *
   * Finds in the database the elements which match the pattern passed in argument. All occurencies found are added to the returned result.
   * 
   * @param p the pattern which has to be matched in the database
   * 
   * @return Result * : pointer to the %Result object which contains the the data matched.
   *
   * @warning In the case of a Pattern formed by a forest of graphes, this function won't return a correct result. The graph of the pattern must be in one chunk, and may not contain isolated nodes.
   * 
   * @sa Pattern to know how to create a pattern \n
   * Result to know how to use a %Result object
   **/
  virtual Result * match(Pattern * p) =0;
};


/**
 * @brief Creation of a new database.
 *
 * @param name name of the database
 *
 * @return Database * : pointer to the newly created Database object.
 **/
Database * newDB(const std::string &name);


/**
 * @brief Deletion of a Database Object, all associated resources are freed.
 *
 * This function doesn't save the database before deleting the object.
 * One must ensure to have saved it with the saveDB() method before calling this function.
 *
 * @param db pointer to the Database object which must be deleted.
 **/
void delDB(Database * db);


/**
 * @brief Initialization of the Graph database library
 *
 * In order to correctly use the Graph database API, this function must be called before any other function from this API. 
 **/
void initDB();


#endif
