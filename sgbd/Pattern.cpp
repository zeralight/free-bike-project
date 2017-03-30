#include "DatabaseImpl.hpp"

#include "Pattern.hpp"
#include "PatternImpl.hpp"


Pattern * newPattern(Database * db) {
  Pattern * ret = new PatternImpl((DatabaseImpl *) db);
  return ret;
}


void delPattern(Pattern * p) {
  delete ((PatternImpl *) p);
}

