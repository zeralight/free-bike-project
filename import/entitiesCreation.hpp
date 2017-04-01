#ifndef ENTITIESCREATION_HPP
#define ENTITIESCREATION_HPP

#include "Database.hpp"


enum values_gender {
  GENDER_MALE,
  GENDER_FEMALE,
  GENDER_NO_INFO,
};

enum values_type {
  TYPE_CUSTOMER,
  TYPE_SUBSCRIBER,
  TYPE_NO_INFO
};


void entitiesCreation(Database *);

#endif //ENTITIESCREATION_HPP
