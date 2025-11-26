#include <iostream>
#include "Vector.hpp"
#include "linearAlgebra.hpp"
#include <iomanip>
int main(void)
{
	Vector a({-1, -2});
	Vector b({0, 10, -100});
	Vector c({3, 2});
	std::cout << std::setprecision(20) << a.norm1() << " " << a.norm() << " " << a.normInfinity() << std::endl;
}
