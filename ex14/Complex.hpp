#ifndef COMPLEX_HPP
# define COMPLEX_HPP
# include <iostream>

class Complex
{
	public:
		Complex(void);
		Complex(Complex const &toCopy);
		Complex(float const &real, float const &im);

		Complex	const &operator=(Complex const &toCopy) const;

		~Complex(void);

		float const	&getRealPart() const;
		float const	&getImPart() const;

		Complex	getConjugate() const;
	
		Complex const	&operator+=(Complex const &toAdd) const;
		Complex const	&operator-=(Complex const &toSub) const;
		Complex const	&operator*=(Complex const &toMultiply) const;
		Complex const	&operator/=(Complex const &toDivide) const;

		float	getModulus() const;

	private:
		float	_real;
		float	_im;
};

std::ostream	&operator<<(std::ostream &os, Complex const &toPrint);

Complex operator+(Complex const &a, Complex const &b) const;
Complex operator-(Complex const &a, Complex const &b) const;
Complex operator*(Complex const &a, Complex const &b) const;
Complex operator/(Complex const &a, Complex const &b) const;

bool	operator==(Complex const &a, Complex const &b) const;
bool	operator!=(Complex const &a, Complex const &b) const;

#endif
