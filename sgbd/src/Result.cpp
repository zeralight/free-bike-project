#include "Result.hpp"
#include "ResultImpl.hpp"

void delResult(Result * res) {
  delete ((ResultImpl *) res);
}
