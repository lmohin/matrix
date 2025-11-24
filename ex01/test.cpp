#include <iostream>
#include "Vector.hpp"

Vector	linearCombination(std::vector<Vector> const &vectors, std::vector<float> const &coefs);

int main(void)
{
	Vector a({-4, 5, 2, 2});
	Vector b({-2, -1, 3, 7});
	std::vector<Vector> comb;
	comb.push_back(a);
	comb.push_back(b);
	std::cout << "2*" << a << " + 5*" << b << " = " << linearCombination(comb, {2, 5, 7}) << std::endl;
}
