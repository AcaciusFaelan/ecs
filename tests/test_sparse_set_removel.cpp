#include <cassert>
#include "ecs/sparse_set.hpp"

int main() {
  ecs::SparseSet<int> set;
  set.add(10, 100);
  set.add(20, 200);

  set.remove(10);

  assert(set.contains(10) == false);
  assert(set.contains(20) == true);
  assert(*set.get(20) == 200);
}