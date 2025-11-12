#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <vector>
# include <iostream>

class Vector
{
	public:
		Vector(void);
		Vector(Vector const &toCopy);
		Vector(std::vector<float> const &toStock);

		Vector	const &operator=(Vector const &toCopy) const;

		~Vector(void);

		std::vector<float>	const &getValues() const;
		
		Vector	getOppositeVector() const;

		size_t	size() const;
		
		//Matrix		const &getAsMatrix() const;

		bool	isNull() const;
		bool	isId() const;

		void	opposite(void);
		void	add(Vector const &toAdd);
		void	sub(Vector const &toSub);
		void	scale(float const &scalar);


	private:
		std::vector<float> _values;
};

std::ostream	&operator<<(std::ostream &os, Vector const &toPrint);

#endif
