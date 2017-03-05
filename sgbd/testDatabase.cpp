#include <string>

#include "Database.hpp"
#include "Result.hpp"
#include "DBTools.hpp"

#define N_PERSON 5

int main() {
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

  db->save(".");

  delAttr(attrPerson, 3);
  delAttr(attrFriendOf, 1);

  delDB(db);
}
