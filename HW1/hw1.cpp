/*
File Name: hw1.cpp
Author: genhen
Date Created: 04/01/2014
Description: Creates a Polynomial class and makes a few objects and
             prints them out after using class mutators on them
Run: g++ -std=c++14 -o hw1.exe hw1.cpp && ./hw1.exe && rm hw1.exe
*/

#include <iostream>
#include <vector>

using namespace std;

/** @class Polynomial
	 (1. stores polynomials and their corresponding constants in a class using vectors
	  2. has the ability to multiply the polynomials by a constant
	  3. has the ability to take a derivative/transform the polynomial
	  4. has a print function to display the polynomial
	  5. can display the degree of the polynomial as well as the coefficient of a certain power of x
	  6. can initialize with 0 or using a vector of integers)
*/
class Polynomial
{
	public:
		Polynomial();
		Polynomial(const vector<int>& coeffs);
		// Accessors
		int Degree() const;
		int Coefficient(int k) const;
		void print() const;
		bool Is_The_Polynomial_All_Zeroes() const;
		// Mutators
		void constantMultiply(int x);
		void Transform();
	private:
		vector<int> coefficient;
};

// poly1 + poly2
Polynomial Add(const Polynomial& poly1, const Polynomial& poly2);
// poly1 - poly2
Polynomial Subtract(const Polynomial& poly1, const Polynomial& poly2);
// poly1 * poly2
Polynomial Multiply(const Polynomial& poly1, const Polynomial& poly2);

int main()
{
	vector<int> user_input_vector_poly1(1,0), user_input_vector_poly2(1,0);
	int user_input_1, user_input_2;
	int counter = 0, counter_2 = 0;

	cout << "Welcome! Please input the coefficients of the first polynomial." << endl
	     << "When you are finished, enter -1234." << endl;
	do
	{
		cin >> user_input_1;
		if(user_input_1 != -1234 && counter == 0)
		{
			user_input_vector_poly1[counter] = user_input_1;
		}
		else if(user_input_1 != -1234)
		{
			user_input_vector_poly1.push_back(user_input_1);
		}

		counter++;
	} while(user_input_1 != -1234);

	Polynomial user_polynomial_1(user_input_vector_poly1);

	cout << endl << "Your first polynomial is ";
	user_polynomial_1.print();

	cout << endl << "Its transform is ";
	Polynomial transformed_user_poly1 = user_polynomial_1;
	transformed_user_poly1.Transform();
	transformed_user_poly1.print();

	cout << endl << endl << "Please input the coefficients of the second polynomial." << endl;
	do
	{
		cin >> user_input_2;
		if(user_input_2 != -1234 && counter_2 == 0)
		{
			user_input_vector_poly2[counter_2] = user_input_2;
		}
		else if(user_input_2 != -1234)
		{
			user_input_vector_poly2.push_back(user_input_2);
		}

		counter_2++;
	} while(user_input_2 != -1234);

	Polynomial user_polynomial_2(user_input_vector_poly2);

	cout << endl << "Your second polynomial is ";
	user_polynomial_2.print();

	cout << endl << "Its transform is ";
	Polynomial transformed_user_poly2 = user_polynomial_2;
	transformed_user_poly2.Transform();
	transformed_user_poly2.print();

	cout << endl << endl << "The sum of these polynomials is " << endl << endl;
	(Add(user_polynomial_1,user_polynomial_2)).print();

	cout << endl << endl << "The first minus the second is " << endl << endl;
	(Subtract(user_polynomial_1,user_polynomial_2)).print();

	cout << endl << endl << "The first multiplied by the second is " << endl << endl;
	(Multiply(user_polynomial_1,user_polynomial_2)).print();

	cout << endl << endl << "Thanks for using my program!" << endl << endl;

	return 0;
}

/**
	This default constructor creates a '0' polynomial by initializing the private integer vector 'coefficient'
	to have one value of 0

*/
Polynomial::Polynomial()
{
	coefficient.push_back(0);
}

/**
	This constructor creates a polynomial by initializing the private integer vector 'coefficient' using a for loop

	@param coeffs is a vector that is copied over to the private integer vector in this polynomial
*/
Polynomial::Polynomial(const vector<int>& coeffs)
{
	for(int counter = 0, number_of_terms = coeffs.size(); counter < number_of_terms; counter++)
		coefficient.push_back(coeffs[counter]);
}

// ACCESSORS
/**
	This function calculates the degree of a polynomial by analyzing the highest slot in the vector coefficient
	that is a non-zero integer and can be considered the highest degree

	@return returns the highest degree of x in the polynomial, with a constant or 0 being degree '0'
*/
int Polynomial::Degree() const
{
	int degree_of_polynomial = 0,
		size_of_vector = coefficient.size();

	for(int counter = 0; counter < size_of_vector; counter++)
		if(coefficient[counter] != 0)
			degree_of_polynomial = counter;

	return degree_of_polynomial;
}
/**
	This function returns a certain integer from the integer vector 'coefficient' at the degree/slot specified
	by the user

	@return takes the specified coefficient from the vector and returns the int values
*/
int Polynomial::Coefficient(int k) const
{
	return coefficient[k];
}
/**
	The function prints the polynomial by checking powers (in order for weird cases like
	x^0 or x^1 not to be displayed), checking negatives (for displaying -'s), and checking
	the counter in a for loop (used to display each coefficient of the polynomial from the
	'coefficient' vector) in order to figure out if it is the first coefficient or not

*/
void Polynomial::print() const
{
	int number_of_terms = coefficient.size(),
		first_term = 0;
	
	for(int counter_2 = 0; (first_term == 0) && (counter_2 < (number_of_terms + 1)); counter_2++)
		if(coefficient[counter_2] != 0)
			first_term = (counter_2 + 1);

	for(int counter = 0; counter < number_of_terms; counter++)
	{
		if(coefficient[counter] != 0)
		{
			if(counter == 0)
				cout << coefficient[counter];
			else if(counter == 1)
			{
				if((first_term - 1) != counter)
					cout << '+';
				
				if(coefficient[counter] == 1)
					cout << 'x';
				else if(coefficient[counter] == -1)
					cout << '-' << 'x';
				else
					cout << coefficient[counter] << 'x';
			}
			else
			{
				if((first_term - 1) != counter)
					cout << '+';
				
				if(coefficient[counter] == 1)
					cout << 'x' << '^' << counter;
				else if(coefficient[counter] == -1)
					cout << '-' << 'x' << '^' << counter;
				else
					cout << coefficient[counter] << "x^" << counter;
			}
		}
		else if(coefficient[counter] == 0 && (counter == 0) && (Is_The_Polynomial_All_Zeroes() == true))
			cout << coefficient[counter];
	}

	return;
}

/**
	This function quickly loops through the private integer vector 'coefficient' in order to figure
	out if all of the coefficients are zero and stops/returns 0 if even one coefficient is 0

	@return depending on whether the vector is all 0's (true) or not (false), returns the appropriate bool value
*/
bool Polynomial::Is_The_Polynomial_All_Zeroes() const
{
	int number_of_terms = coefficient.size();
	bool polynomial_all_zeroes = true;

	for(int counter = 0; ((polynomial_all_zeroes == true) && (counter < number_of_terms)); counter++)
	{
		if(coefficient[counter] == 0)
			polynomial_all_zeroes = true;
		else
			polynomial_all_zeroes = false;
	}

	return polynomial_all_zeroes;
}

// Mutators
/**
	This function loops through the 'coefficient' vector and multiplies by an integer specified
	by the user.

	@param takes an integer value in to multiply every coefficient int(integer) by
*/
void Polynomial::constantMultiply(int x)
{
	int number_of_terms = coefficient.size();
	for(int counter = 0; counter < number_of_terms; counter++)
		coefficient[counter] = coefficient[counter] * x;

	return;
}
/**
	This function transforms the polynomial by taking a derivative (aka multiplying by the
	power, lowering the power of each value, and setting the last coefficient (that would
	try to gather information from outside the range if included in the for loop) equal
	to zero(integer 0)
	
*/
void Polynomial::Transform()
{
	int number_of_terms = coefficient.size();
	
	for(int counter = 0; counter < (number_of_terms - 1); counter++)
		coefficient[counter] = coefficient[counter + 1] * (counter + 1);

	coefficient[number_of_terms - 1] = 0;
	
	return;
}


/**
	This function takes two polynomials and adds their respective coefficients by using a
	for loop until you reach the lower-degree polynomial, and only uses the other polynomial
	from there

	@param the two parameters are the two polynomials you want to add, poly1 and poly2
	@return it returns a third polynomial, resulting_added_polynomial, that was created out
	of the integer vector that stored the added coefficient integers
*/
Polynomial Add(const Polynomial& poly1, const Polynomial& poly2)
{
	int largest_polynomial = 0,
	    size_of_poly1 = (poly1.Degree() + 1),
	    size_of_poly2 = (poly2.Degree() + 1);

	if(size_of_poly1 > size_of_poly2)
		largest_polynomial = size_of_poly1;
	else
		largest_polynomial = size_of_poly2;

	vector<int> polynomial_size_allocator(largest_polynomial, 0);

	for(int counter = 0; counter < largest_polynomial; counter++)
	{
		if((size_of_poly1 < size_of_poly2) && ((counter + 1) > size_of_poly1))
			polynomial_size_allocator[counter] = poly2.Coefficient(counter);
		else if((size_of_poly2 < size_of_poly1) && ((counter + 1) > size_of_poly2))
			polynomial_size_allocator[counter] = poly1.Coefficient(counter);
		else
			polynomial_size_allocator[counter] = poly1.Coefficient(counter) + poly2.Coefficient(counter);
	}

	Polynomial resulting_added_polynomial(polynomial_size_allocator);
	return resulting_added_polynomial;
}

/**
	This function uses the add function by adding a negative version of the second polynomial
	and returning the "sum"

	@param the parameters are the polynomials objects passed by reference that will be used
	but not changed 
	@return the returned value is a new polynomial created by the integer vector resulting by
	the addition of the two polynomials
*/
Polynomial Subtract(const Polynomial& poly1, const Polynomial& poly2)
{
	Polynomial poly2_replacement = poly2;
	poly2_replacement.constantMultiply(-1);
	Polynomial resulting_subtracted_polynomial = Add(poly1,poly2_replacement);
	return resulting_subtracted_polynomial;
}

/**
	This function goes through each coefficient of the first polynomial and multiplies each
	coefficient throughout the whole second polynomial using a nested for loop

	@param the parameters are the polynomials objects passed by reference that will be used
	but not changed
	@return the returned value is a new polynomial created by the integer vector resulting by
	the multiplication of the two polynomials
*/
Polynomial Multiply(const Polynomial& poly1, const Polynomial& poly2)
{
	int size_of_poly1 = (poly1.Degree() + 1),
	    size_of_poly2 = (poly2.Degree() + 1);
	vector<int> resulting_polynomial_integers((size_of_poly1 + size_of_poly2), 0);

	for(int counter = 0; counter < size_of_poly2; counter++)
		for(int counter_2 = 0; counter_2 < size_of_poly1; counter_2++)
			resulting_polynomial_integers[counter + counter_2] = resulting_polynomial_integers[counter + counter_2] + (poly1.Coefficient(counter_2) * poly2.Coefficient(counter));

	Polynomial resulting_multiplied_polynomial(resulting_polynomial_integers);

	return resulting_multiplied_polynomial;
}
