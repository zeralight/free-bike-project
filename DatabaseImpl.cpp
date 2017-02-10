#include <tulip/TlpTools.h>
#include <tulip/Node.h>
#include <tulip/Edge.h>

#include "DBTools.hpp"
#include "Database.hpp"
#include "DatabaseImpl.hpp"
#include "Entity.hpp"
#include "Relation.hpp"
#include "Result.hpp"

DatabaseImpl::DatabaseImpl(std::string name){
  Graph *G = newGraph();
  this->name.assign(name);
  nbE=0;
  nbR=0;
}

void DatabaseImpl::newEntity(std::string name, const AttrType attributes[], int nAttr){
    int i;
    try{
      for(i=0; i<nbE; i++)
      {
        if ((E[i].getName()).compare(name)==0)
          throw string("ERREUR : Entity is already exist");
      }
    }

    Entity e = new Entity(G, name, attributes, nAttr);
    nbE ++;
    E=realloc(E, sizeof(Entity)*nbE);
    E[nbE-1]=e;

    catch(string const& chaine)
    {
      cerr << chaine << endl;
    }
}

Result * DatabaseImpl::newNode(std::string entityName, const AttrValue values[], int nVal){
    Entity e = getEntity(E, nbE, entityName);
    Result * r = e.newEntityInstance(values, nVal);
    return r;

    catch(string const& chaine)
    {
      cerr << chaine << endl;
    }
}

Result * DatabaseImpl::newNode(std::string name, const Attr attributes[], int nAttr){
  //ajout d'un noeud qui n'appartient pas à une entité ?
}

void DatabaseImpl::newRelation(std::string relationName, std::string entitySrc, std::string entityDst, const AttrType attributes[], int nAttr){
    try{
      for(i=0; i<nbE; i++)
      {
        if ((R[i].getName()).compare(name)==0)
          throw string("ERREUR : Relation is already exist");
      }
    }

    Relation r= new Relation(G, name, entitySrc, entityDst, attributes, nAttr);
    nbR ++;
    R=realloc(R, sizeof(Relation)*nbR);
    R[nbR-1]=r;

    catch(string const& chaine)
    {
      cerr << chaine << endl;
    }
}

void DatabaseImpl::newEdge(std::string relationName, const Result * src, const Result * dst, const AttrValue values[], int nVal){
    Relation r = getRelation(R, nbR, relationName);
    r.newRelationInstance(values, src, dst, nVal);

    catch(string const& chaine)
    {
      cerr << chaine << endl;
    }
}

void DatabaseImpl::newEdge(std::string name, const Result * src, const Result * dst, const Attr attributes[], int nAttr){
  //ajout d'un arc qui n'appartient pas à une relation ?
}



int DatabaseImpl::saveDB(std::string path) const{
    PluginProgress * p;
    bool i = saveGraph(G, path, p);
    try{
      if (!i)
        throw string("ERREUR : Graph no save");
    }
    catch(string const& chaine)
    {
       cerr << chaine << endl;
    }
}



Database * DatabaseImpl::loadDB(std::string path, const std::string name){
        PluginProgress * p;
        G = loadGraph(path,	p);
        try{
          if (!i)
            throw string("ERREUR : Graph no load");
        }
        this->name.assign(name);
        //comment recuperer E et R ?
        catch(string const& chaine)
        {
           cerr << chaine << endl;
        }
}





Relation getRelation(Relation * R, int nbR, std::string relationName){
  try{
    int i;
    for(i=0; i<nbR; i++)
    {
      if ((R[i].getName()).compare(relationName)==0)
        return R[i];
    }
    throw string("ERREUR : Relation doesn't exist");
  }
}

Entity getEntity(Entity * E, int nbE, std::string entityName){
  try{
    int i;
    for(i=0; i<nbE; i++)
    {
      if ((E[i].getName()).compare(entityName)==0)
        return E[i];
    }
    throw string("ERREUR : Entity doesn't exist");
  }
}
