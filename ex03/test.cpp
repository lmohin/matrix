#include <iostream>
#include "Vector.hpp"
#include "linearAlgebra.hpp"

int main(void)
{
	Vector a({2, 1});
	Vector b({0, 10, -100});
	Vector c({4, 2});
	Matrix aa({2, 1, 3, 4}, 2, 2);
	Matrix bb({20, 10, 30, 40}, 2, 2);
	std::vector<Vector> comb;
	std::cout << lerp(aa, bb, 0.5) << std::endl;
	std::cout << a.dot(c) << std::endl;
	std::cout << a.dot(b) << std::endl;
}
