#include "Matrix.hpp"
#include "linearAlgebra.hpp"
#include <algorithm>
#include "mathsUtils.hpp"

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

bool	Matrix::isSquared() const
{
	return (_rows == _cols);
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
			if ((*this)(i, j) == 0)
				std::cout << 0;
			else
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
	if (col >= _cols)
		throw std::invalid_argument("Error: col exceed the matrix's total columns");
	
	std::vector<float>	colVectorValues;
	
	for (size_t i = 0; i != _rows; i++)
		colVectorValues.push_back((*this)(i, col));
	
	Vector	colVector(colVectorValues);
	return (colVector);
}

Vector	Matrix::getRowVector(size_t const &row) const
{
	if (row >= _rows)
		throw std::invalid_argument("Error: row exceed the matrix's total rows");
	
	std::vector<float>	rowVectorValues;

	for (size_t i = 0; i != _cols; i++)
		rowVectorValues.push_back((*this)(row, i));

	Vector	rowVector(rowVectorValues);
	return (rowVector);
}

std::vector<Vector>	Matrix::getAllCols() const
{
	std::vector<Vector>	allCols;
	
	for (size_t col = 0; col != _cols; col++)
		allCols.push_back(getColVector(col));
	return allCols;
}

std::vector<Vector>	Matrix::getAllRows() const
{
	std::vector<Vector>	allRows;
	for (size_t row = 0; row != _rows; row++)
		allRows.push_back(getRowVector(row));
	return allRows;
}

Vector	Matrix::multiply(Vector const &vec) const
{
	if (vec.size() != _cols)
		throw std::invalid_argument("Error: if matrix shape is (n,p) you can multiply it only with vectors of size p");
	
	return (linearCombination(getAllCols(), vec.getValues()));
}

Matrix	Matrix::multiply(Matrix const &mat) const
{
	size_t const	matRows = mat.shape().first;
	size_t const	matCols = mat.shape().second;

	if (_cols != matRows)
		throw std::invalid_argument("Error: if matrix shape is (n,m) you can multiply it only with matrices of shape (m, p)");

	std::vector<Vector>	newMatrixCols;
	for (size_t col = 0; col != matCols; col++)
	{
		Vector	newCol = this->multiply(mat.getColVector(col));
		newMatrixCols.push_back(newCol);
	}

	Matrix	result(newMatrixCols);
	
	return result;
}

float	Matrix::trace(void) const
{
	if (_cols != _rows)
		throw std::invalid_argument("Error: you can only calculate the trace of square matrix");
	
	float	traceResult = 0;
	for (size_t col = 0; col != _cols; col++)
		traceResult += (*this)(col, col);
	return traceResult;
}

Matrix	Matrix::transpose(void) const
{
	std::vector<Vector>	allRows = this->getAllRows();

	Matrix	transposeMatrix(allRows);
	return (transposeMatrix);
}

void	Matrix::switchRows(size_t const &firstRow, size_t const &secondRow)
{
	if (firstRow >= _rows || secondRow >= _rows)
		throw std::invalid_argument("Error: you can not swap unexistant rows");
	for (size_t col = 0; col != _cols; col++)
	{
		float	tmp = (*this)(firstRow, col);

		(*this)(firstRow, col) = (*this)(secondRow, col);
		(*this)(secondRow, col) = tmp;
	}
}

void	Matrix::scaleRow(size_t const &row, float const &scalar)
{
	if (row >= _rows)
		throw std::invalid_argument("Error: you can not scale unexistant row");
	for (size_t col = 0; col != _cols; col++)
		(*this)(row, col) *= scalar;
}


void	Matrix::addScaledRow(size_t const &rowToChange, size_t const &rowAdded, float const &scalar)
{
	if (rowToChange >= _rows || rowAdded >= _rows)
		throw std::invalid_argument("Error: you can not use unexistant rows");
	for (size_t col = 0; col != _cols; col++)
		(*this)(rowToChange, col) += (*this)(rowAdded, col) * scalar;
}

void	Matrix::swapToPivot(size_t const &row, size_t const &col)
{
	if (row >= _rows)
		throw std::invalid_argument("Error: row exceeds total rows of the matrix");
	if (col >= _cols)
		throw std::invalid_argument("Error: col exceeds total colums of the matrix");

	size_t	rowMaxIndex = row;
	float	rowMax = maths_utils::abs((*this)(row, col));

	for (size_t rowIndex = row + 1; rowIndex < _rows; rowIndex++)
	{
		if (maths_utils::abs((*this)(rowIndex, col)) > rowMax)
		{
			rowMaxIndex = rowIndex;
			rowMax = maths_utils::abs((*this)(rowIndex, col));
		}
	}
	switchRows(rowMaxIndex, row);
}

bool	Matrix::colIsPartiallyNull(size_t const &row, size_t const &col) const
{
	for (size_t tmpRow = row; tmpRow < _rows; tmpRow++)
	{
		if ((*this)(tmpRow, col) != 0)
			return (false);
	}
	return (true);
}

Matrix	Matrix::gaussianElimination(void) const
{
	Matrix	result(*this);
	size_t	currentCol = 0;

	for (size_t row = 0; row != _rows; row++)
	{
		while (currentCol < _cols && result.colIsPartiallyNull(row, currentCol))
			currentCol++;
		if (currentCol == _cols)
			break;
		result.swapToPivot(row, currentCol);
		if (result(row, currentCol) != 0)
			result.scaleRow(row, 1 / result(row, currentCol));
		for (size_t rowIndex = 0; rowIndex != _rows; rowIndex++)
		{
			if (rowIndex != row)
				result.addScaledRow(rowIndex, row, -((result)(rowIndex, currentCol)));
		}
		currentCol++;
	}
	return (result);
}

Matrix	Matrix::getSubMatrix(size_t const &rowToRemove, size_t const &colToRemove) const
{
	std::vector<float>	newValues;

	if (rowToRemove >= _rows || colToRemove >= _cols)
		throw (std::invalid_argument("rowToRemove and colToRemove must be lower than the matrix shape"));
	for (size_t i = 0; i != _rows * _cols; i++)
	{
		if (i % _cols != rowToRemove && i / _cols != colToRemove)
			newValues.push_back(_values[i]);
	}

	Matrix	result(newValues, _cols - 1, _rows - 1);
	return (result);
}

float	Matrix::determinant(void) const
{
	if (!isSquared())
		throw(std::logic_error("You can only compute the determinant of squared matrices"));
	if (_rows > 10)
		throw(std::logic_error("You can only use determinant method with small matrices"));
	switch (_rows)
	{
		case 0:
			return (1);

		case 1:
			return (_values[0]);
		case 2:
			return ((*this)(0, 0) * (*this)(1, 1) - (*this)(0, 1) * (*this)(1, 0));
		default:
			float	det = 0;
			int	sign = 1;
			for (size_t i = 0; i != _rows; i++)
			{
				det += sign * (*this)(i, 0) * getSubMatrix(i, 0).determinant();
				sign *= -1;
			}
			return (det);
	}
}

Matrix	Matrix::getAugmentedMatrix(void) const
{
	Matrix	augmentedMatrix(_rows, _cols * 2);
	
	for (size_t row = 0; row != _rows; row++)
	{
		for (size_t col = 0; col != _cols; col++)
			augmentedMatrix(row, col) = (*this)(row, col);
		augmentedMatrix(row, _rows + row) = 1;
	}
	return (augmentedMatrix);
}

Matrix	Matrix::getInverseFromAugmentedMatrix(void) const
{
	std::vector<Vector>	inverseColumns;
	
	for (size_t col = 0; col != _cols / 2; col++)
		inverseColumns.push_back(this->getColVector(_cols / 2 + col));
	
	Matrix	inverseMatrix(inverseColumns);
	return (inverseMatrix);
}

Matrix	Matrix::inverse(void) const
{
	if (_rows != _cols)
		throw(std::logic_error("only squared matrices are inversible"));
	if (_rows == 0)
		throw(std::logic_error("You can not inverse a void matrix"));

	Matrix	augmentedMatrix = getAugmentedMatrix();
	size_t	currentCol = 0;

	for (size_t row = 0; row != _rows; row++)
	{
		if (augmentedMatrix.colIsPartiallyNull(row, currentCol))
			throw(std::logic_error("Matrix is singular, it has no inverse"));
		if (currentCol == _cols)
			break;
		augmentedMatrix.swapToPivot(row, currentCol);
		if (augmentedMatrix(row, currentCol) != 0)
			augmentedMatrix.scaleRow(row, 1 / augmentedMatrix(row, currentCol));
		else
			throw (std::logic_error("Matrix is singular, it has no inverse"));
		for (size_t rowIndex = 0; rowIndex != _rows; rowIndex++)
		{
			if (rowIndex != row)
				augmentedMatrix.addScaledRow(rowIndex, row, -((augmentedMatrix)(rowIndex, currentCol)));
		}
		currentCol++;
	}
	Matrix inverseMatrix = augmentedMatrix.getInverseFromAugmentedMatrix();
	return (inverseMatrix);
}
