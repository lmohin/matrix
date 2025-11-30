#ifndef LINEARALGEBRA_HPP
# define LINEARALGEBRA_HPP

#include <iostream>
#include <cfloat>
#include "Vector.hpp"

Vector	linearCombination(std::vector<Vector> const &vectors, std::vector<float> const &coefs);
Vector	lerp(Vector const &u, Vector const &v, float const &t);
Matrix	lerp(Matrix const &u, Matrix const &v, float const &t);
float	lerp(float const &u, float const &v, float const &t);

float	angleCos(Vector const &u, Vector const &v);
#endif
