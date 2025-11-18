#include "Matrix.hpp"
#include <algorithm>

/*Constructors*/

Matrix::Matrix(void)
: _rows(0), _cols(0)
{
	return;
}

Matrix::Matrix(Matrix const &toCopy)
: _values(toCopy.getValues()), _rows(toCopy.shape().first), _cols(toCopy.shape().second)
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
	if (row + 1 > _rows)
		throw std::out_of_range("row is out of range");
	if (col + 1 > _cols)
		throw std::out_of_range("col is out of range");
	return _values[_cols * row + col];
}

float 		&Matrix::operator()(size_t row, size_t col)
{
	if (row + 1 > _rows)
		throw std::out_of_range("row is out of range");
	if (col + 1 > _cols)
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
	return (std::make_pair(_rows, _cols));
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
	{
		if ((*this)(i, i) != 1)
			return false;
		for (size_t j = 0; j != _cols; j++)
			if (i != j && (*this)(i, j) != 0)
				return false;
	}
	return true;
}

/*os overloard*/

std::ostream	&operator<<(std::ostream &os, Matrix const &toPrint)
{
	std::pair<float, float>	matrixShape = toPrint.shape();
	os << "(";
	for (size_t j = 0; j != matrixShape.second; j++)
	{
		os << "(";
		for (size_t i = 0; i != matrixShape.first; i++)
		{
			os << toPrint(i, j);
			if (i + 1 != matrixShape.first)
				os << " , ";
		}
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
	std::pair<float, float>		toAddShape = toAdd.shape();
	std::vector<float> const	&toAddValues = toAdd.getValues();

	if (_rows != toAddShape.first || _cols != toAddShape.second)
		std::cout << "Error\nYou can not sum " << *this << " and " << toAdd << " : matrix must be of the same shape" << std::endl;
	else
	{
		for (size_t i = 0; i != _values.size(); i++)
			_values[i] += toAddValues[i];
	}
}

void	Matrix::sub(Matrix const &toSub)
{
	std::pair<float, float>		toSubShape = toSub.shape();
	std::vector<float> const 	&toSubValues = toSub.getValues();
	if (_rows != toSubShape.first || _cols != toSubShape.second)
		std::cout << "Error\nYou can not sub " << toSub << " to " << *this << " : matrix must be of the same shape" << std::endl;
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
