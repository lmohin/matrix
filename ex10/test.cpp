#include <iostream>
#include "Vector.hpp"
#include "linearAlgebra.hpp"
#include <iomanip>
int main(void)
{
	Matrix a({0, 0, 0, 6, 8, 2, 5, 2, 2, 1, 7, 2, 12, 10, 2, 16, 18, 2}, 3, 6);
	std::cout << a << std::endl;
	a.show();
	a.gaussianElimination().show();
}
