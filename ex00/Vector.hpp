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
		
		size_t	size() const;
		
		//Matrix		const &getAsMatrix() const;

		bool isNull();

	private:
		std::vector<float> _values;
};

std::ostream	&operator<<(std::ostream &os, Vector const &toPrint);

#endif
