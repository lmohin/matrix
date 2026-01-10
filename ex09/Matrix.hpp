#ifndef MATRIX_HPP
# define MATRIX_HPP
# include "Vector.hpp"
# include <vector>
# include <iostream>

class Vector;

class Matrix
{
	public:
		Matrix(void);
		Matrix(Matrix const &toCopy);
		Matrix(std::vector<float> const &toStock, size_t rows, size_t cols);
		Matrix(size_t rows, size_t cols);
		Matrix(std::vector<Vector> const &vectors);

		Matrix	const &operator=(Matrix const &toCopy) const;

		~Matrix(void);

		std::vector<float>	const &getValues() const;
		
		float const	&operator()(size_t row, size_t col) const;
		float		&operator()(size_t row, size_t col);

		Matrix	getOppositeMatrix() const;

		std::pair<float, float>	shape() const;
		
		Vector	getAsVector() const;

		bool	isNull() const;
		bool	isId() const;

		void	show() const;

		void	opposite(void);
		void	add(Matrix const &toAdd);
		void	sub(Matrix const &toSub);
		void	scale(float const &scalar);

		Vector	getColVector(size_t const &col) const;
		Vector	getRowVector(size_t const &row) const;
		std::vector<Vector>	getAllCols() const;
		std::vector<Vector>	getAllRows() const;

		Vector	multiply(Vector const &vec) const;
		Matrix	multiply(Matrix const &mat) const;

		float	trace() const;

		Matrix	transpose(void) const;

	private:
		std::vector<float> _values;
		size_t	_rows;
		size_t	_cols;
};

std::ostream	&operator<<(std::ostream &os, Matrix const &toPrint);

#endif
