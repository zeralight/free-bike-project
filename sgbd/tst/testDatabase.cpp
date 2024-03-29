#include <string>

#include <sys/types.h>
#include <sys/stat.h>

#include "Database.hpp"
#include "Result.hpp"
#include "DBTools.hpp"

#include "tstMacros.h"

#define N_PERSON 5

INIT_OUTPATH("testDatabase");

int main() {
  CREATE_OUTPATH;
  
  initDB();

  Database * db = newDB("Friends");

  Attribute * attrPerson[3] = {new Attr<STRING>("firstname"), new Attr<STRING>("lastname"), new Attr<INT>("age")};
  db->newEntity("Person", attrPerson, 3);

  Attribute * attrFriendOf[1] = {new Attr<INT>("date")};
  db->newRelation("FriendOf", "Person", "Person", attrFriendOf, 1);

  Result * res[N_PERSON];

  STRING pFirstname;
  STRING pLastname;
  INT pAge;
  for (int i = 0 ; i < N_PERSON ; i++) {
    pFirstname = "Roger";
    pLastname = "Hanin" + std::to_string(i);
    pAge = 20 + i;
    attrPerson[0]->setValue(&pFirstname);
    attrPerson[1]->setValue(&pLastname);
    attrPerson[2]->setValue(&pAge);
    res[i] = db->newNode("Person", attrPerson, 3);
  }

  INT foDate;
  for (int i = 0 ; i < N_PERSON ; i++) {
    for (int j = 0 ; j < N_PERSON - 3 ; j++) {
      foDate = ((i + 3 * j) * 7) % 12 + 1;
      attrFriendOf[0]->setValue(&foDate);
      db->newEdge("FriendOf", res[i], res[(i + j + 1) % N_PERSON], attrFriendOf, 1);
    }
  }

  Attribute * modif[1] = {new Attr<STRING>("lastname", "Moore")};
  res[0]->editNodes("Person", modif, 1);
  
  db->save(S_OUTDIR);
  
  Database * dbCopy = newDB("");
  dbCopy->load(S_OUTPATH("Friends.db"));

  mkdirat(AT_FDCWD, C_OUTPATH("cpy"), S_IFDIR | S_IRWXU);
  dbCopy->save(S_OUTPATH("cpy"));
  
  delAttr(attrPerson, 3);
  delAttr(attrFriendOf, 1);

  for (int i = 0 ; i < N_PERSON ; i++)
    delResult(res[i]);

  delDB(db);
  delDB(dbCopy);
}
