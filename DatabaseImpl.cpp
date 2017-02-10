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

void DatabaseImpl::newEntity(std::string name, const AttrType attributes[], int nAttr) {
    Entity e = new Entity(G, name, attributes, nAttr);
    nbE ++;
    E=realloc(E, sizeof(Entity)*nbE);
    E[nbE-1]=e;
}

Result * DatabaseImpl::newNode(std::string entityName, const AttrValue values[], int nVal){
    Entity e = getEntity(E, nbE, entityName);
    Result * r = e.newEntityInstance(values, nVal);
    return r;
}



Result * DatabaseImpl::newNode(std::string name, const Attr attributes[], int nAttr){
  //ajout d'un noeud qui n'appartient pas à une entité ?
}


void DatabaseImpl::newRelation(std::string relationName, std::string entitySrc, std::string entityDst, const AttrType attributes[], int nAttr){
    Relation r= new Relation(G, name, entitySrc, entityDst, attributes, nAttr);
    nbR ++;
    R=realloc(R, sizeof(Relation)*nbR);
    R[nbR-1]=r;
}


void DatabaseImpl::newEdge(std::string relationName, const Result * src, const Result * dst, const AttrValue values[], int nVal){
    Relation r = getRelation(R, nbR, relationName); //attention on ne stocke pas les noms dans les retations et entité : a modifier
    r.newRelationInstance(values, src, dst, nVal);
}


void DatabaseImpl::newEdge(std::string name, const Result * src, const Result * dst, const Attr attributes[], int nAttr){
  //ajout d'un arc qui n'appartient pas à une relation ?
}



int DatabaseImpl::saveDB(std::string path) const {
    PluginProgress * p;
    bool i = saveGraph(G, path, p);
    //lever erreur graph non sauvegardé
}



Database * DatabaseImpl::loadDB(std::string path, const std::string name) {
        PluginProgress * p;
        G = loadGraph(path,	p);
        this->name.assign(name);
        //comment recuperer E et R ?
}

Relation getRelation(Relation * R, int nbR, std::string relationName)
{
  int i;
  for(i=0; i<nbR; i++)
  {
    if ((R[i].getName()).compare(relationName)==0)
      return R[i];
  }
  //si pas trouver lever une erreur
}

Entity getEntity(Entity * E, int nbE, std::string entityName)
{
  int i;
  for(i=0; i<nbE; i++)
  {
    if ((E[i].getName()).compare(entityName)==0)
      return E[i];
  }
  //si pas trouver lever une erreur
}
