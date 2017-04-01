#include <iostream>
#include <string>
#include <cstdlib>

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include <tulip/TlpTools.h>
#include <tulip/Node.h>
#include <tulip/Edge.h>

#include "DBTools.hpp"
#include "Database.hpp"
#include "DatabaseImpl.hpp"
#include "Entity.hpp"
#include "Relation.hpp"
#include "Result.hpp"
#include "ResultImpl.hpp"


using namespace std;


DatabaseImpl::DatabaseImpl(const string &name): GraphWriteAbstract(newGraph(), this) {
  this->g->setName(name);
  this->gRelations = this->g->addSubGraph("Relations");
  this->gEntities = this->g->addSubGraph("Entities");
  this->gResults = this->g->addSubGraph("Results");
  this->name = name;
  this->gEntities->getLocalProperty<StringProperty>(PROP_ENTITY_NAME);
  this->gRelations->getLocalProperty<StringProperty>(PROP_RELATION_NAME);
}


DatabaseImpl::~DatabaseImpl(){
  for (auto it = entities.begin() ; it != entities.end() ; it = entities.erase(it))
    delete (*it).second;

  for (auto it = relations.begin() ; it != relations.end() ; it = relations.erase(it))
    delete (*it).second;
}


void DatabaseImpl::newEntity(const string &name, const Attribute * const attributes[], int nAttr) {
  try{
    if (entities.find(name) != entities.end())
      throw string("ERROR: Entity " + name + " already exists");
    
    Graph * entityGraph = this->gEntities->addSubGraph(name);
    Entity * e = new Entity(name, attributes, nAttr, entityGraph);
    entities[name] = e;
  }
  catch(const string &errMessage) {
    cerr << errMessage << endl;
  }
}


Result * DatabaseImpl::newNode(const string &entityName, Attribute * attr[], int nAttr){
  try {
    Entity * e = getEntity(entityName);
    Graph * rG;
    
    const node n = e->newInstance(attr, nAttr);
    if (!n.isValid())
      throw string("ERROR: impossible to create an instance of " + entityName);

    // Add new node in all Relation graphs
    Iterator<Graph *> * it = this->gRelations->getSubGraphs();
    while (it->hasNext()) {
      rG = it->next();
      rG->addNode(n);
    }

    delete it;
    
    // ajout de n dans r
    ResultImpl * r = new ResultImpl(entityName, this->gResults->addSubGraph(), this);
    r->addNode(n);

    return r;
  }
  catch(const string &errMessage) {
     cerr << errMessage << endl;
  }

  return NULL;
}


void DatabaseImpl::newRelation(const std::string &name, const std::string &entitySrc, const std::string &entityDst, const Attribute * const attr[], int nAttr) {
  try {
    if (relations.find(name) != relations.end())
      throw string("ERROR: Relation " + name + " already exists");

    Entity * src = getEntity(entitySrc);
    Entity * dst = getEntity(entityDst);

    Graph * relationGraph = this->gRelations->addSubGraph(name);
    
    Relation * r = new Relation(name, src, dst, attr, nAttr, relationGraph);
    relations[name] = r;
  }
  catch(const string &errMessage) {
    cerr << errMessage << endl;
  }
}


void DatabaseImpl::newEdge(const std::string &relationName, const Result * src, const Result * dst, Attribute * attr[], int nAttr) {
  node nSrc;
  node nDst;
  Relation * r = getRelation(relationName);
  Iterator<node> * itSrc = ((const ResultImpl *) src)->getNodes();
  
  while(itSrc->hasNext()) {
    nSrc = itSrc->next();
    Iterator<node> * itDst = ((const ResultImpl *) dst)->getNodes();
    
    while(itDst->hasNext()) {
      nDst = itDst->next();
      r->newInstance(nSrc, nDst, attr, nAttr);
    }

    delete itDst;
  }
  
  delete itSrc;
}


void DatabaseImpl::load(const string &path){
  try {
    ifstream file(path.c_str());
    if (!file)
      throw string("ERROR: the database " + path + " doesn't exist");
    file.close();
    
    string pathG = path + "/graph.tlp";
    string pathE = path + "/entities.sav";
    string pathR = path + "/relations.sav";

    if (this->g)
      delete this->g;
    
    this->g = loadGraph(pathG);
    if (this->g == NULL)
      throw string("ERROR: impossible to load the graph " + pathG);
        
    this->name = this->g->getName();
    this->gEntities = this->g->getSubGraph("Entities");
    this->gRelations = this->g->getSubGraph("Relations");
    this->gResults = this->g->getSubGraph("Results");
    
    this->loadEntities(pathE);
    this->loadRelations(pathR);
  }
  catch(const string &errMessage) {
    cerr << errMessage << endl;
  }
}


void DatabaseImpl::save(const string &path) const {
  try {
    string dbPath = path + "/" + this->name + ".db";
    int ret = mkdirat(AT_FDCWD, dbPath.c_str(), S_IFDIR | S_IRWXU);
    if (ret == -1 && errno != EEXIST)
      throw string("ERROR: impossible to create the database at " + path);    
    string pathG = dbPath + "/graph.tlp";
    string pathE = dbPath + "/entities.sav";
    string pathR = dbPath + "/relations.sav";

    ret = saveGraph(this->g, pathG);
    if (!ret)
      throw string("ERROR: impossible to save the graph at " + pathG);
    
    this->saveEntities(pathE);
    this->saveRelations(pathR);
  }
  catch (const string &errMessage) {
    cerr << errMessage << endl;
  }
}


Relation * DatabaseImpl::getRelation(const string &name) {
  auto rPtr = relations.find(name);
  if (rPtr == relations.end())
    throw string("ERROR: Relation '" + name + "' doesn't exist");

  return (*rPtr).second;
}


Entity * DatabaseImpl::getEntity(const string &name) {
  auto ePtr = entities.find(name);
  if (ePtr == entities.end())
    throw string("ERROR: Entity '" + name + "' doesn't exist");

  return (*ePtr).second;
}


void DatabaseImpl::saveEntities(const string &path) const {
  fstream file;
  string buff;
  Entity * e;
  file.open(path, ios_base::out);
  
  if (!file)
    throw string("ERROR: impossible to create file " + path);

  file.flush();

  buff = to_string(entities.size());
  file << buff.c_str() << endl;
  
  for(auto it = entities.begin() ; it != entities.end() ; it++) {
    e = (*it).second;
    e->write(file);
  }

  file.close();
}


void DatabaseImpl::saveRelations(const string &path) const {
  fstream file;
  string buff;
  Relation * r;
  file.open(path, ios_base::out);
  
  if (!file)
    throw string("ERROR: impossible to create file " + path);

  file.flush();

  buff = to_string(relations.size());
  file << buff.c_str() << endl;
  
  for(auto it = relations.begin() ; it != relations.end() ; it++) {
    r = (*it).second;
    r->write(file);
  }

  file.close();
}


void DatabaseImpl::loadEntities(const string &path){
  fstream file;
  string buff;
  int n;
  file.open(path);

  if (!file)
    throw string("ERROR: impossible to open file " + path);
  
  buff = getWord(file);
  n = stoi(buff);

  for (int i = 0 ; i < n ; i++) {
    Entity * e = new Entity();
    e->load(file, this->gEntities);
    entities[e->getName()] = e;
  }

  file.close();
}

void DatabaseImpl::loadRelations(const string &path) {
  fstream file;
  string buff;
  int n;
  file.open(path);

  if (!file)
    throw string("ERROR: impossible to open file " + path);
  
  buff = getWord(file);
  n = stoi(buff);

  for (int i = 0 ; i < n ; i++) {
    Relation * r = new Relation();
    r->load(file, this->gRelations, this->entities);
    relations[r->getName()] = r;
  }

  file.close();
}


Graph * DatabaseImpl::newGraphResult(const std::string &name) {
  return this->gResults->addSubGraph(name);
}
