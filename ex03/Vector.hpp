#ifndef VECTOR_HPP
# define VECTOR_HPP
# include "Matrix.hpp"
# include <vector>
# include <iostream>

class Matrix;
class Vector
{
	public:
		Vector(void);
		Vector(Vector const &toCopy);
		Vector(std::vector<float> const &toStock);
		Vector(size_t size);

		Vector	const &operator=(Vector const &toCopy) const;

		~Vector(void);

		std::vector<float>	const &getValues() const;
		
		Vector	getOppositeVector() const;

		float &operator()(size_t index);
		float const &operator()(size_t index) const;

		size_t	size() const;
		
		Matrix	getAsMatrix() const;

		bool	isNull() const;
		bool	isId() const;

		void	opposite(void);
		void	add(Vector const &toAdd);
		void	sub(Vector const &toSub);
		void	scale(float const &scalar);

		float	dot(Vector const &otherVector) const;

	private:
		std::vector<float> _values;
};

std::ostream	&operator<<(std::ostream &os, Vector const &toPrint);

#endif
