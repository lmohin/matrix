#include <iostream>
#include "Vector.hpp"
#include "linearAlgebra.hpp"
#include <iomanip>
int main(void)
{
	Matrix a({2, -2, -2, 2}, 2, 2);
	Vector c({4, 2});
	std::cout << a.multiply(c) << std::endl;
}
