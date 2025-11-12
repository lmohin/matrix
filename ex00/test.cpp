#include <iostream>
#include "Vector.hpp"

int main(void)
{
	Vector a({0, 1});
	Vector b({-4, 5});
	a.sub(b);
	std::cout << a << std::endl;
}
