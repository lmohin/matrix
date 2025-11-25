#include "Vector.hpp"
#include <cmath>

Vector	linearCombination(std::vector<Vector> const &vectors, std::vector<float> const &coefs)
{
	if (vectors.size() != coefs.size())
		throw std::invalid_argument("You must provide as much coefs as the number of vectors to do a linear combination");
	if (vectors.size() == 0)
		return (Vector());
	
	size_t	vectorSize = vectors[0].size();
	size_t	numberVectors = vectors.size();
	
	for (size_t i = 0; i != numberVectors; i++)
		if (vectors[i].size() != vectorSize)
			throw std::invalid_argument("All vectors must have the same size to do a linear combination");

	Vector result(vectorSize);
	for (size_t pos = 0; pos != vectorSize; pos++)
		for (size_t vectorIndex = 0; vectorIndex != numberVectors; vectorIndex++)
			result(pos) = std::fma(vectors[vectorIndex](pos), coefs[vectorIndex], result(pos));
	return result;
}

Vector	lerp(Vector const &u, Vector const &v, float const &t)
{
	std::vector<Vector> const	toInterpolate({u, v});
	std::vector<float> const	coeffs({1 - t, t});

	return (linearCombination(toInterpolate, coeffs));
}

float	lerp(float const &u, float const &v, float const &t)
{
	return (u * (1 - t) + v * t);
}

Matrix	lerp(Matrix const &u, Matrix const &v, float const &t)
{
	Matrix	uCopy(u);
	Matrix	vCopy(v);

	uCopy.scale((1 - t));
	vCopy.scale(t);
	uCopy.add(vCopy);
	return (uCopy);
}
