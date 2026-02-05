#ifndef MATRIX_HPP
# define MATRIX_HPP
# include "Vector.hpp"
# include <vector>
# include <iostream>

class Vector;

template <class T>
class Matrix
{
	public:
		Matrix(void);
		Matrix(Matrix<T> const &toCopy);
		Matrix(std::vector<T> const &toStock, size_t rows, size_t cols);
		Matrix(size_t rows, size_t cols);
		Matrix(std::vector<Vector<T>> const &vectors);

		Matrix	const &operator=(Matrix<T> const &toCopy) const;

		~Matrix(void);

		std::vector<T>	const &getValues() const;
		
		T const	&operator()(size_t row, size_t col) const;
		float	&operator()(size_t row, size_t col);

		Matrix<T>	getOppositeMatrix() const;

		std::pair<T, T>	shape() const;
		
		Vector<T>	getAsVector() const;

		bool	isNull() const;
		bool	isId() const;
		bool	isSquared() const;

		void	show() const;

		void	opposite(void);
		void	add(Matrix<T> const &toAdd);
		void	sub(Matrix<T> const &toSub);
		void	scale(float const &scalar);

		Vector<T>	getColVector(size_t const &col) const;
		Vector<T>	getRowVector(size_t const &row) const;
		std::vector<Vector<T>>	getAllCols() const;
		std::vector<Vector<T>>	getAllRows() const;

		Vector<T>	multiply(Vector<T> const &vec) const;
		Matrix<T>	multiply(Matrix<T> const &mat) const;

		T	trace() const;

		Matrix<T>	transpose(void) const;

		void	switchRows(size_t const &firstRow, size_t const &secondRow);
		void	scaleRow(size_t const &row, float const &scalar);
		void	addScaledRow(size_t const &rowToChange, size_t const &rowAdded, float const &scalar);
		void	swapToPivot(size_t const &row, size_t const &col);

		bool	colIsPartiallyNull(size_t const &row, size_t const &col) const;

		Matrix	gaussianElimination(void) const;
		
		Matrix	getSubMatrix(size_t const &rowToRemove, size_t const &colToRemove) const;
		float	determinant(void) const;

		Matrix	inverse(void) const;

	private:
		std::vector<float> _values;
		size_t	_rows;
		size_t	_cols;
	
		Matrix	getAugmentedMatrix(void) const;
		Matrix	getInverseFromAugmentedMatrix(void) const;
};

std::ostream	&operator<<(std::ostream &os, Matrix const &toPrint);

#endif
