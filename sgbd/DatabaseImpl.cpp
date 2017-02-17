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

void DatabaseImpl::newEntity(string name, const Attribute * const attributes[], int nAttr){
    int i;
    try{
      for(i=0; i<nbE; i++)
      {
        if ((E[i].getName()).compare(name)==0)
          throw string("ERREUR : Entity is already exist");
      }
      Entity * e = new Entity(name, attributes, nAttr);
      nbE ++;
      E=(Entity *)realloc(E, sizeof(Entity)*nbE);
      E[nbE-1]=*e;
    }
    catch(string const& chaine)
    {
      cerr << chaine << endl;
    }
}

Result * DatabaseImpl::newNode(string entityName, Attribute * attributes[], int nVal){
  try{
    Entity e = getEntity(E, nbE, entityName);
    Result * r = e.newInstance(attributes, nVal);
    return r;
  }
  catch(string const& chaine)
  {
     cerr << chaine << endl;
  }
}



Database * DatabaseImpl::loadDB(char * path, const string name){
      try{
        PluginProgress * p;
        char * pathG ="/Graph";
        char * pathE ="/Entities";
        char * pathR ="/Relations";
        char * result;
        strcpy(result,path);
        strcat(result,pathG);
        G = loadGraph(result,	p);
        if (G==NULL)
            throw  string("ERREUR : Graph no load");

        char * result1;
        strcpy(result1,path);
        strcat(result1,pathE);
        char * result2;
        strcpy(result2,path);
        strcat(result2,pathR);

        this->name.assign(name);
        nbE = loadE(E, result1);
        nbR = loadR(R, result2 );
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
  sprintf(c,"%d\n",nbE);
  err = write(fd, c,strlen(c)+2);
  if (err==-1)
    throw string("ERREUR : nb entities no save");

  for(i=0;i<nbE; i++)
  {
    err = E[i].writeEntity(fd); //a coder dans entity
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
    sprintf(c,"%d\n",nbR);
    err = write(fd, c,strlen(c)+2);
    if (err==-1)
      throw string("ERREUR : nb relation no save");

    for(i=0;i<nbR; i++)
    {
      err = R[i].writeRelation(fd); //a coder dans relation
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
  b[strlen(b)-3]='\0';
  int nbE=atoi(b);
  int i=0;
  while (fgets(b, LEN, fd)!=NULL){
    E[i].load(b);
    i++;
  }

  fclose(fd);
  return nbE;
}

int loadR(Relation * R, char * path ){
  FILE * fd=fopen(path, "r");
  if (fd==NULL)
    throw string("ERREUR : file R not found");

  char b[LEN];
  fgets(b, LEN, fd);
  b[strlen(b)-3]='\0';
  int nbR=atoi(b);
  int i=0;
  while (fgets(b, LEN, fd)!=NULL){
    R[i].load(b);
    i++;
  }

  fclose(fd);
  return nbR;
}
