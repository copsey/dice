#include "die.hpp"
#include "random.hpp"

dice::Die::result_type dice::Die::operator()() const {
	return dist(rand_eng);
}
