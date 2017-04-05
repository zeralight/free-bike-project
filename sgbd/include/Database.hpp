#ifndef DATABASE_HPP
#define DATABASE_HPP

///@cond USER

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
   * This method creates a new entity in the database, i.e. a particular type of node in the graph. \n
   * An entity has a name, and can have specific attributes. Its kind of a template for a node, it defines
   what are the number, the labels and the types of the attributes. \n
   * For exemple, an entity 'Person' which has three attributes 'name', 'lastname' and 'age' can be created this way:
   * @code
   * Database * db = newDB("DB");
   * Attribute * tab[3] = {new Attr<STRING>("name"), new Attr<STRING>("lastname"), new Attr<INT>("age")};
   * db->newEntity("Person", tab, 3);
   * @endcode
   *
   * @param name entity's name
   * @param attributes list of Attribute objects describing the attributes of the entity, can be NULL
   * @param nAttr number of attributes
   *
   **/
  virtual void newEntity(const std::string &name, const Attribute * const attr[], int nAttr) =0;


  /**
   * @brief Insertion of a new instance of an entity in the database.
   *
   * The attributes indicated in the argument 'attr' must correspond to the description of the entity used, i.e. the label and the type of the value. If one attribute doesn't correspond, the creation of the node will fail. \n
   * Only the attributes for which a value is associated can be given. The other will be initialized with the default value corresponding to their type.
   *
   * @param entityName name of the entity which acts as a model
   * @param attr list of Attribute object describing the attributes and the value which must be assigned to the node, can be NULL
   * @param nVal number of filled attributes (size of 'attr')
   *
   * @return Result * : a pointer to a Result object containing the newly created node
   **/
  virtual Result * newNode(const std::string &entityName, Attribute * attr[], int nVal) =0;


  /**
   * @brief Creation of a relation.
   *
   * This method creates a new relation in the database, i.e. a description of type of edge in the graph. \n
   * A relation has a name, a source entity, a destination entity and can have specific attributes. \n
   * It's kind of a template for an edge, it defines what are the number of attributes, their labels and their types. \n
   * Moreover a relation describes a directed edge, and the type of the source and destination nodes must be indicated.\n
   * For exemple, a relation 'FriendOf' between two 'Person' and which has one attribute 'meetingYear' can be created this way :
   * @code
   * Database * db = newDB("DB");
   * Attribute tab[1] = {new Attr<INT>("meetingDate")};
   * db->newRelation("FriendOf", "Person", "Person", tab, 1);
   * @endcode
   *
   * @param relationName relation's name
   * @param entitySrc name of source entity (must exist in the database)
   * @param entityDst name of destination entity (idem)
   * @param attributes list of Attribute objects describing the attributes of the relation, can be NULL
   * @param nAttr number of attributes
   *
   **/
  virtual void newRelation(const std::string &relationName, const std::string &entitySrc, const std::string &entityDst, const Attribute * const attr[], int nAttr) =0;


  /**
   * @brief Insertion of a new instance of a relation in the database.
   *
   * The attributes indicated in the argument 'attr' must correspond to the description of the relation used, i.e. same labels and same types for the associated values. \n
   * Only the attributes for which a value is associated can be given. The other will be initialized with the default value corresponding to their type. \n
   * For the source and/or the destination, a set of nodes can be given, since they are contained in a Result object. In this case, all nodes in the source set will be linked with all nodes in the destination set. 
   *
   * @param relationName name of the relation acting as the model
   * @param src source node (or set of nodes) 
   * @param dst destination node (or set of nodes)
   * @param attr list of Attributes describing the attributes' values of the edge, can be NULL
   * @param nAttr number of indicated attributes (size of 'attr')
   *
   **/
  virtual void newEdge(const std::string &relationName, const Result * src, const Result * dst, Attribute * attr[], int nAttr) =0;

  
  /**
   * @brief Edition of nodes in the Database
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
   * @warning In case a Pattern is formed by a forest of graphes, the behaviour of this function is unknown (but probably false). The graph of the pattern must be in one chunk, and may not contain isolated nodes.
   * 
   * @sa Pattern to know how to create a pattern \n
   * Result to know how to use a %Result object
   **/
  virtual Result * match(Pattern * p) =0;
};


/**
 * @brief Creation of a new Database object.
 *
 * @param name name of the database to cra
 *
 * @return Database * : pointer to the newly created Database object.
 **/
Database * newDB(const std::string &name);


/**
 * @brief Deletion of a Database object
 *
 * All associated resources are freeed, so the pointer db is invalidated.
 * This function doesn't save the database before deleting the object.
 * One must ensure to have saved it with the Database::save() method before calling this function.
 * If db is NULL, nothing will be done.
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

///@endcond

#endif
