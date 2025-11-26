#ifndef LINEARALGEBRA_HPP
# define LINEARALGEBREA_HPP

#include <iostream>
#include "Vector.hpp"

Vector	linearCombination(std::vector<Vector> const &vectors, std::vector<float> const &coefs);
Vector	lerp(Vector const &u, Vector const &v, float const &t);
Matrix	lerp(Matrix const &u, Matrix const &v, float const &t);
float	lerp(float const &u, float const &v, float const &t);

#endif
