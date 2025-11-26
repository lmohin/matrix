#ifndef LINEARALGEBRA_HPP
# define LINEARALGEBRA_HPP

#include <iostream>
#include "Vector.hpp"

Vector	linearCombination(std::vector<Vector> const &vectors, std::vector<float> const &coefs);

#endif
