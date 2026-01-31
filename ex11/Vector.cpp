#include "Vector.hpp"
#include <algorithm>
#include <cmath>
#include "mathsUtils.hpp"

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

Vector::Vector(size_t size)
: _values(std::vector<float>(size, 0))
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

float const	&Vector::operator()(size_t index) const
{
	if (index + 1 > this->size())
		throw std::out_of_range("index is out of range");
	return _values[index];
}

float	&Vector::operator()(size_t index)
{
	if (index + 1 > this->size())
		throw std::out_of_range("index is out of range");
	return _values[index];
}

Vector	Vector::getOppositeVector() const
{
	Vector oppositeVector(*this);
	
	oppositeVector.opposite();
	return (oppositeVector);
}

Matrix	Vector::getAsMatrix() const
{
	return Matrix(_values, _values.size(), 1);
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

bool	Vector::isId() const
{
	if(_values.size() == 0)
		return false;
	return (std::all_of(_values.begin(), _values.end(), [](float x){return x == 1;}));
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

void	Vector::opposite(void)
{
	for (std::vector<float>::iterator it = _values.begin(); it != _values.end(); it++)
		*it *= -1;
}

void	Vector::add(Vector const &toAdd)
{
	size_t	mySize = this->size();

	if (mySize != toAdd.size())
		std::cout << "Error\nYou can not sum " << *this << " and " << toAdd << " : vectors must be of the same size" << std::endl;
	else
	{
		std::vector<float> const &toAddValues = toAdd.getValues();
		for (size_t i = 0; i != mySize; i++)
			_values[i] += toAddValues[i];
	}
}

void	Vector::sub(Vector const &toSub)
{
	size_t	mySize = this->size();

	if (mySize != toSub.size())
		std::cout << "Error\nYou can not sub " << toSub << " to " << *this << " : vectors must be of the same size" << std::endl;
	else
	{
		std::vector<float> const &toSubValues = toSub.getValues();
		for (size_t i = 0; i != mySize; i++)
			_values[i] -= toSubValues[i];
	}
}

void	Vector::scale(float const &scalar)
{
	for (std::vector<float>::iterator it = _values.begin(); it != _values.end(); it++)
		*it *= scalar;
}

float	Vector::dot(Vector const &otherVector) const
{
	size_t	mySize = this->size();
	float	result = 0;

	if (mySize != otherVector.size())
		throw std::invalid_argument("Can not calculate the dot product of vectors of different size");
	std::vector<float> const &otherVectorValues = otherVector.getValues();
	for (size_t i = 0; i != mySize; i++)
		result = std::fma(_values[i], otherVectorValues[i], result);
	return (result);
}

float	Vector::norm1() const
{
	float	norm1 = 0;

	for (std::vector<float>::const_iterator it = _values.begin(); it != _values.end(); it++)
		norm1 += abs(*it);
	return (norm1);
}

float	Vector::norm() const
{
	float	dotProduct = dot(*this);
	float	norm = std::pow(dotProduct, 0.5);
	
	return (norm);
}

float	Vector::normInfinity() const
{
	float	maxValue = 0;

	for (std::vector<float>::const_iterator it = _values.begin(); it != _values.end(); it++)
		if (abs(*it) > maxValue)
			maxValue = maths_utils::abs(*it);
	return (maxValue);
}
