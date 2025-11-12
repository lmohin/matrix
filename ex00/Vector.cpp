#include "Vector.hpp"
#include <algorithm>

/*Constructors*/

Vector::Vector(void)
{
	return;
}

Vector::Vector(Vector const &toCopy)
: _values(toCopy.getValues())
{
	return;
}

/*Copy overload*/

Vector::Vector(std::vector<float> const &toStock)
: _values(toStock)
{
	return;
}

/*Destructor*/

Vector::~Vector(void)
{
	return;
}

/*Getters*/

std::vector<float>	const &Vector::getValues() const
{
	return _values;
}

size_t	Vector::size() const
{
	return _values.size();
}

bool	Vector::isNull() const
{
	if (_values.size() == 0)
		return true;
	return (std::all_of(_values.begin(), _values.end(), [](float x){return x == 0;}));
}

/*os overloard*/

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

/*Calculus*/

/*void	Vector::add(Vector const &toAdd)
{
	if isNull()
		
}*/
