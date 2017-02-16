#include <tulip/TlpTools.h>
#include <tulip/Node.h>
#include <tulip/Edge.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <string.h>

#include "DBTools.hpp"
#include "Database.hpp"
#include "DatabaseImpl.hpp"
#include "Entity.hpp"
#include "Relation.hpp"
#include "Result.hpp"

#define LEN 1000
using namespace std;

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

void DatabaseImpl::newEntity(string name, const Attribute attributes[], int nAttr){
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

Result * DatabaseImpl::newNode(string entityName, const Attribute values[], int nVal){
  try{
    Entity e = getEntity(E, nbE, entityName);
    Result * r = e.newEntityInstance(values, nVal);
    return r;
  }th, 0600);

  catch(string const& chaine)
  {
     cerr << chaine << endl;
  }
}



Database * DatabaseImpl::loadDB(string path, const string name){
      try{
        PluginProgress * p;
        string pathG ("/Graph");
        string pathE ("/Entities");
        string pathR ("/Relations");
        G = loadGraph(path+pathG,	p);
              if (G==NULL)
            throw  string("ERREUR : Graph no load");

        this->name.assign(name);
        nbE = loadE(E, path+pathE );
        nbR = loadR(R, path+pathR );
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

void saveE(Entity * E, int nbE, char * path ){
  int fd=creat(path, 0600);
  int err, err2, i;
  if (fd==-1)
    throw string("ERREUR : create save E");

  char * c;
  sprintf(c,"%d",nbE);
  string nb (c);
  err = write(fd, nb+"\n", string::size(nb)+2);
  if (err==-1)
    throw string("ERREUR : nb entities no save");

  for(i=0;i<nbE; i++)
  {
    err = writeR(fd, E[i]); //a coder dans entity
    err2 = write(fd, "\n", 2);
    if (err==-1 || err2==-1)
      throw string("ERREUR : one entity isn't save");
  }
  err=close(fd);
  if (fd==-1)
    throw string("ERREUR : close save E");
}


void saveR(Relation * R, int nbR, char * path ){
    int fd=creat(path, 0600);
    int err, err2, i;
    if (fd==-1)
      throw string("ERREUR : create save R");

    char * c;
    sprintf(c,"%d",nbR);
    string nb (c);
    err = write(fd, nb+"\n", string::size(nb)+2);
    if (err==-1)
      throw string("ERREUR : nb relation no save");

    for(i=0;i<nbR; i++)
    {
      err = writeR(fd, R[i]); //a coder dans relation
      err2 = write(fd, "\n", 2);
      if (err==-1 || err2==-1)
        throw string("ERREUR : one relation isn't save");
    }
    err=close(fd);
    if (fd==-1)
      throw string("ERREUR : close save R");
}

int loadE(Entity * E, char * path ){
  FILE * fd=fopen(path, "r");
  if (fd==NULL)
    throw string("ERREUR : file E not found");

  char b[LEN];
  fgets(b, LEN, fd);
  b[strlen(b)-3]='/0';
  int nbE=atoi(b);
  while (fgets(b, LEN, fd)!=NULL){
    loadEntity(b);
  }

  fclose(fd);
  return nbE;
}

int loadR(Relation * R, char * path ){
}
