#include "die.hpp"
#include "random.hpp"

using namespace dice;

Die::result_type dice::Die::operator()() const {
	return dist(rand_eng);
}
