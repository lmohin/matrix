#include "Vector.hpp"

#include <cmath>
#include <cfloat>

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

float	angleCos(Vector const &u, Vector const &v)
{
	if (u.size() != v.size())
		throw (std::invalid_argument("Vectors must have the same size to evaluate the cosinus of an angle"));

	float	dotProduct = u.dot(v);
	float	normProduct = u.norm() * v.norm();

	if (normProduct == 0)
		throw (std::invalid_argument("Vectors must not be nul to evaluate the cosinus of an angle"));
	
	float	cosResult = dotProduct / normProduct;
	return (cosResult);
}

Vector	crossProduct(Vector const &u, Vector const &v)
{
	if (u.size() != 3 || v.size() != 3)
		throw (std::invalid_argument("Vectors must be 3 dimentional vectors to do a cross product"));
	
	float	xValue = u(1) * v(2) - u(2) * v(1);
	float	yValue = u(2) * v(0) - u(0) * v(2);
	float	zValue = u(0) * v(1) - u(1) * v(0);
	Vector	product({xValue, yValue, zValue});
	return (product);
}
