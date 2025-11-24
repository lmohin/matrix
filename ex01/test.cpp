#include <iostream>
#include "Vector.hpp"

Vector	linearCombination(std::vector<Vector> const &vectors, std::vector<float> const &coefs);

int main(void)
{
	Vector a({1, 2, 3});
	Vector b({0, 10, -100});
	Vector c({0, 0, 1});
	std::vector<Vector> comb;
	comb.push_back(a);
	comb.push_back(b);
	//comb.push_back(c);
	std::cout << linearCombination(comb, {10, -2}) << std::endl;
}
