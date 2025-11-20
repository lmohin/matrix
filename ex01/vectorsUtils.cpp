#include "Vector.hpp"
#include <cmath>

Vector	linearCombination(std::vector<Vector> const &vectors, std::vector<float> const &coefs)
{
	if (vectors.size() == 0)
		return (Vector());
	Vector result(vectors[0].size());
	for (size_t i = 0; i != result.size(); i++)
		for (size_t j = 0; j != vectors.size(); j++)
			result(i) = std::fma(vectors[j](i), coefs[j], result(i));
	return result;
}
