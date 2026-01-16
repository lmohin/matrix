#include <iostream>
#include "Vector.hpp"
#include "linearAlgebra.hpp"
#include <iomanip>
int main(void)
{
	Matrix a({3, -5, 2, 6, 8, 2, 5, 2, 2, 1, 7, 2, 12, 10, 2, 16, 18, 2}, 3, 6);
	Vector v({4, 2});
	Matrix b({2, -5, 0, 4, 3, 7, -2, 3, 4, 10}, 2, 5);
	std::cout << a << std::endl;
	std::cout << a << std::endl;
	a.addScaledRow(1, 2, 3); 
	std::cout << a << std::endl;
}
