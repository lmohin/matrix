#include "Vector.hpp"

Vector::Vector(void)
{
	return;
}

Vector::Vector(Vector const &toCopy)
: _values(toCopy.getValues())
{
	return;
}

Vector::Vector(std::vector<float> const &toStock)
: _values(toStock)
{
	return;
}

Vector::~Vector(void)
{
	return;
}

std::vector<float>	const &Vector::getValues() const
{
	return _values;
}

size_t	Vector::size() const
{
	return _values.size();
}

std::ostream	&operator<<(std::ostream &os, Vector const &toPrint)
{
	std::vector<float> const &values = toPrint.getValues();
	os << "(";
	for (std::vector<float>::const_iterator it = values.begin(); it != values.end(); it++)
	{
		os << *it;
		if (it + 1 != values.end())
			os << ",";
	}
	os << ")";
	return os;
}
