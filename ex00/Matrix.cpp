#include "Matrix.hpp"
#include <algorithm>

/*Constructors*/

Matrix::Matrix(void)
: _rows(0), _cols(0)
{
	return;
}

Matrix::Matrix(Matrix const &toCopy)
: _values(toCopy.getValues()), _rows(toCopy.shape()[0]), _cols(toCopy.shape()[1])
{
	return;
}

Matrix::Matrix(std::vector<float> const &toStock, size_t rows, size_t cols)
: _values(toStock), _rows(rows), _cols(cols)
{
	if (rows == 0 && toStock.size() != 0)
		throw std::invalid_argument("invalid shapes");
	if (rows == 0)
		return;
	if (_values.size() / rows != cols)
		throw std::invalid_argument("invalid shapes");
	return;
}

/*Destructor*/

Matrix::~Matrix(void)
{
	return;
}

/*Getters*/

std::vector<float>	const &Matrix::getValues() const
{
	return _values;
}

float const	&Matrix::operator()(size_t row, size_t col) const
{
	if (row + 1 > this->shape()[0])
		throw std::out_of_range("row is out of range");
	if (col + 1 > this->shape()[1])
		throw std::out_of_range("col is out of range");
	return _values[_cols * row + col];
}

float 		&Matrix::operator()(size_t row, size_t col)
{
	if (row + 1 > this->shape()[0])
		throw std::out_of_range("row is out of range");
	if (col + 1 > this->shape()[1])
		throw std::out_of_range("col is out of range");
	return _values[_cols * row + col];
}

Matrix	Matrix::getOppositeMatrix() const
{
	Matrix oppositeMatrix(*this);
	
	oppositeMatrix.opposite();
	return (oppositeMatrix);
}

std::pair<float, float>	Matrix::shape() const
{
	return (_rows, _cols);
}

bool	Matrix::isNull() const
{
	if (_values.size() == 0)
		return true;
	return (std::all_of(_values.begin(), _values.end(), [](float x){return x == 0;}));
}

bool	Matrix::isId() const
{
	if (_rows != _cols || _rows == 0)
		return false;
	for (size_t i = 0; i != _rows; i++)
		if ((*this)(i, j) != 1)
			return false;
		for (size_t j = 0; j != _cols; j++)
			if (i != j && (*this)(i, j) != 0)
				return false;
	return true;
}

/*os overloard*/

std::ostream	&operator<<(std::ostream &os, Matrix const &toPrint)
{
	os << "(";
	for (size_t j = 0; j != _cols; j++)
	{
		os << "(";
		for (size_t i = 0; i != _rows; i++)
			os << (*this)(i, j);
			if (i + 1 != _rows)
				os << " , ";
		os << ")";
	}
	os << ")";
	return os;
}

/*Calculus*/

void	Matrix::opposite(void)
{
	for (std::vector<float>::iterator it = _values.begin(); it != _values.end(); it++)
		*it *= -1;
}

void	Matrix::add(Matrix const &toAdd)
{
	otherShape = toAdd.shape();
	otherValues = toAdd.getValues();
	if (_rows != otherShape[0] || _cols != otherShape[1])
		std::cout << "Error\nYou can not sum " << *this << " and " << toAdd << " : matrix must be of the same shape" << std::endl;
	else
	{
		for (size_t i = 0; i != _values.size(); i++)
			_values[i] += otherValues[i];
	}
}

void	Matrix::sub(Matrix const &toSub)
{
	toSubShape = toSub.shape();
	toSubValues = toSub.getValues();
	if (_rows != otherShape[0] || _cols != toSubShape[1])
		std::cout << "Error\nYou can not sub " << toAdd << " to " << *this << " : matrix must be of the same shape" << std::endl;
	else
	{
		for (size_t i = 0; i != _values.size(); i++)
			_values[i] -= toSubValues[i];
	}
}

void	Matrix::scale(float const &scalar)
{
	for (std::vector<float>::iterator it = _values.begin(); it != _values.end(); it++)
		*it *= scalar;
}
