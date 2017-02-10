#include <tulip/TlpTools.h>
#include <tulip/Node.h>
#include <tulip/Edge.h>

#include "DBTools.hpp"
#include "Database.hpp"
#include "DatabaseImpl.hpp"
#include "Entity.hpp"
#include "Relation.hpp"
#include "Result.hpp"

using namespace std

DatabaseImpl::DatabaseImpl(string name){
  Graph *G = newGraph();
  this->name.assign(name);
  nbE=0;
  nbR=0;
}

DatabaseImpl::~DatabaseImpl(){
  name.string::~string();
  int i;
  for(i=0; i<nbE; i++)
  {
    E[i].~Entity();
  }
  for(i=0; i<nbR; i++)
  {
    R[i].~Relation();
  }
  G->tlp::Graph::~Graph();
}

void DatabaseImpl::newEntity(string name, const AttrType attributes[], int nAttr){
    int i;
    try{
      for(i=0; i<nbE; i++)
      {
        if ((E[i].getName()).compare(name)==0)
          throw string("ERREUR : Entity is already exist");
      }
      Entity e = new Entity(G, name, attributes, nAttr);
      nbE ++;
      E=realloc(E, sizeof(Entity)*nbE);
      E[nbE-1]=e;
    }
    catch(string const& chaine)
    {
      cerr << chaine << endl;
    }
}

Result * DatabaseImpl::newNode(string entityName, const AttrValue values[], int nVal){
  try{
    Entity e = getEntity(E, nbE, entityName);
    Result * r = e.newEntityInstance(values, nVal);
    return r;
  }
  catch(string const& chaine)
  {
    cerr << chaine << endl;
  }
}

Result * DatabaseImpl::newNode(string name, const Attr attributes[], int nAttr){
  //ajout d'un noeud qui n'appartient pas à une entité ?
}

void DatabaseImpl::newRelation(string relationName, string entitySrc, string entityDst, const AttrType attributes[], int nAttr){
    try{
        for(i=0; i<nbE; i++)
        {
          if ((R[i].getName()).compare(name)==0)
            throw string("ERREUR : Relation is already exist");
        }

        Relation r= new Relation(G, name, entitySrc, entityDst, attributes, nAttr);
        nbR ++;
        R=realloc(R, sizeof(Relation)*nbR);
        R[nbR-1]=r;
    }
    catch(string const& chaine)
    {
      cerr << chaine << endl;
    }
}

void DatabaseImpl::newEdge(string relationName, const Result * src, const Result * dst, const AttrValue values[], int nVal){
    try{
      Relation r = getRelation(R, nbR, relationName);
      r.newRelationInstance(values, src, dst, nVal);
    }
    catch(string const& chaine)
    {
      cerr << chaine << endl;
    }
}

void DatabaseImpl::newEdge(string name, const Result * src, const Result * dst, const Attr attributes[], int nAttr){
  //ajout d'un arc qui n'appartient pas à une relation ?
}



int DatabaseImpl::saveDB(string path) const{
  try{
    PluginProgress * p;
    bool i = saveGraph(G, path, p);
      if (!i)
        throw string("ERREUR : Graph no save");
    }
    catch(string const& chaine)
    {
       cerr << chaine << endl;
    }
}



Database * DatabaseImpl::loadDB(string path, const string name){
      try{
        PluginProgress * p;
        G = loadGraph(path,	p);
              if (G==NULL)
            throw  string("ERREUR : Graph no load");

        this->name.assign(name);
        //comment recuperer E et R ?
      }
      catch( string const& chaine)
      {
         cerr << chaine << endl;
      }
}





Relation getRelation(Relation * R, int nbR,  string relationName){
    int i;
    for(i=0; i<nbR; i++)
    {
      if ((R[i].getName()).compare(relationName)==0)
        return R[i];
    }
    throw string("ERREUR : Relation doesn't exist");
}

Entity getEntity(Entity * E, int nbE,  string entityName){
    int i;
    for(i=0; i<nbE; i++)
    {
      if ((E[i].getName()).compare(entityName)==0)
        return E[i];
    }
    throw string("ERREUR : Entity doesn't exist");
}
