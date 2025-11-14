#include <iostream>
#include "Vector.hpp"

int main(void)
{
	Vector a;
	Vector b({-4, 5});
	a.scale(5.2);
	try{
		std::cout << a(0) << std::endl;}
	catch (...)
	{
		std::cout << "oops" << std::endl;
	}
}
