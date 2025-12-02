#include "Matrix.hpp"
#include "linearAlgebra.hpp"
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

Matrix::Matrix(std::vector<Vector> const &vectors)
{
	if (vectors.empty())
	{
		_rows = 0;
		_cols = 0;
		return;
	}
	size_t	tmpRows = vectors[0].size();
	for (std::vector<Vector>::const_iterator it = vectors.begin(); it != vectors.end(); it++)
	{
		if (it->size() != tmpRows)
			throw std::invalid_argument("All vectors must have the same size to create a matrix");
		_values.insert(_values.end(), it->getValues().begin(), it->getValues().end());
	}
	_rows = tmpRows;
	_cols = vectors.size();
}

Matrix::Matrix(size_t rows, size_t cols)
: _rows(rows), _cols(cols)
{
	if (SIZE_MAX / rows < cols)
		throw std::invalid_argument("Matrix is too big to be created, overflow detected");
	_values = std::vector<float>(rows * cols, 0);
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
	return _values[_rows * col + row];
}

float 		&Matrix::operator()(size_t row, size_t col)
{
	if (row + 1 > _rows)
		throw std::out_of_range("row is out of range");
	if (col + 1 > _cols)
		throw std::out_of_range("col is out of range");
	return _values[_rows * col + row];
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

Vector	Matrix::getAsVector() const
{
	return Vector(_values);
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
				os << ",";
		}
		os << ")";
		if (j + 1 != matrixShape.second)
			os << " ";
	}
	os << ")";
	return os;
}

void	Matrix::show() const
{
	std::pair<float, float>	matrixShape = shape();
	for (size_t i = 0; i != matrixShape.first; i++)
	{
		std::cout << "|";
		for (size_t j = 0; j != matrixShape.second; j++)
		{
			std::cout << (*this)(i, j);
			if (j + 1 != matrixShape.second)
				std::cout << " , ";
		}
		std::cout << "|" << std::endl;
	}
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

Vector	Matrix::getColVector(size_t const &col) const
{
	if (col > _cols)
		throw std::invalid_argument("Error: col exceed the matrix's total columns");
	
	std::vector<float>	colVectorValues;
	
	for (size_t i = 0; i != _rows; i++)
		colVectorValues.push_back((*this)(col, i));
	
	Vector	colVector(colVectorValues);
	return (colVector);
}

std::vector<Vector>	Matrix::getAllCols() const
{
	std::vector<Vector> allCols;
	
	for (size_t col = 0; col != _cols; col++)
		allCols.push_back(getColVector(col));
	return allCols;
}

Vector	Matrix::multiply(Vector const &vec) const
{
	if (vec.size() != _rows)
		throw std::invalid_argument("Error: if matrix shape is (n,p); you can multiply it only with vectors of size p");
	
	return (linearCombination(getAllCols(), vec.getValues()));
}
