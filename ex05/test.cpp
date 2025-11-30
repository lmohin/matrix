#include <iostream>
#include "Vector.hpp"
#include "linearAlgebra.hpp"
#include <iomanip>
int main(void)
{
	Vector a({1, 2, 3});
	Vector b({0, 10, -100});
	Vector c({4, 5, 6});
	std::cout << a.norm1() << " " << a.norm() << " " << angleCos(a, c) << std::endl;
}
