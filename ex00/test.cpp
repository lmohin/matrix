#include <iostream>
#include "Vector.hpp"
#include "Matrix.hpp"

int main(void)
{
	Vector a;
	Vector b({-4, 5});
	Vector c({-2, -1});
	Vector d(b);
	Vector e(c);
	Vector f(10);
	std::cout << "a: " << a << " b: " << b << " c: " << c << " d: " << d << " e: " << e << " f: " << f << std::endl;
	std::cout << a.getValues() << b.getValues() << std::endl;
	a.scale(5.2);
	std::cout << b(1) << b.getAsMatrix() << std::endl;
	Matrix m({4, 3, 1, 1, 1, 2, 3, 6}, 2, 4);
	std::cout << SIZE_MAX << std::endl;
	Matrix dd(10000, 3000);
	b.add(c);
	b.scale(4.13);
	Vector g({24, 24});
	m.add(m);
	m.scale(44.13);
	b.sub(g);
	std::cout << b << std::endl;
	try{
		std::cout << a.isNull() << std::endl;
		m.show();
		std::cout << m << std::endl;}
	catch (...)
	{
		std::cout << "oops" << std::endl;
	}
}
