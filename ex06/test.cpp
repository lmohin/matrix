#include <iostream>
#include "Vector.hpp"
#include "linearAlgebra.hpp"
#include <iomanip>
int main(void)
{
	Vector a({4, 2, -3});
	Vector c({-2, -5, 16});
	std::cout << crossProduct(a, c) << std::endl;
}
