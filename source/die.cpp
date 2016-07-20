#include "die.hpp"
#include "random.hpp"

dice::Die::Die(int n)
 : dist{1, (n > 0) ? n : (throw bad_num_sides{n})} { }

int dice::Die::num_sides() const {
   return dist.max();
}

int dice::Die::operator()() const {
   return dist(rand_eng);
}
