/*
File Name: hw7.cpp
Author: genhen
Date Created: 05/12/2014
Description: Create a BinaryInteger class that mimics the way integers are stored in a computer,
             but which represents negative numbers in the `sign and magnitude' form (i.e., the
             binary representation for -19 would be the same as 19 but with the signed bit `1').
             It should have a private member variable which is a vector of bools, and another
             private member variable of type bool which determines whether the integer is positive
             or negative.
Run: g++ -std=c++14 -o hw7.exe hw7.cpp && ./hw7.exe && rm hw7.exe
*/

#include <algorithm>
//#include <cctype>
// #include <cmath>
//#include <conio.h>
//#include <cstring>
//#include <cstdio>
//#include <cstdlib>
//#include <ctime>
//#include <ctype.h>
// #include <fstream>
//#include <iomanip>
#include <iostream>
//#include <math.h>
//#include <sstream>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string>
//#include <string.h>
//#include <time.h>
#include <vector>
//#include <windows.h>

using namespace std;

/**
	@class BinaryInteger
	1. Takes a degree and a negative operator and creates an integer out of it.
	2. Can alternate between negative nad positive numbers using multiples.
	3. Can perform operations of addition, subtraction, and, or , and istream/ostream operator
	   operations.
*/
class BinaryInteger
{
	public:
		// Constructors
		BinaryInteger();
		BinaryInteger(const vector<bool> &input_bools, const bool sign);
		BinaryInteger(int integer_to_construct);

		// Accessors
		vector<bool> get_powers_of_two() const;
		bool get_positive() const;
		void print() const;

		// Operator Functions
		BinaryInteger operator<<(int shift_amount) const;
		BinaryInteger operator>>(int shift_amount) const;
		BinaryInteger& operator<<=(int shift_amount);
		BinaryInteger& operator>>=(int shift_amount);
		BinaryInteger operator~();
		friend ostream& operator<<(ostream& outstream, const BinaryInteger &binaryinteger_out);
		friend istream& operator>>(istream& intstream, BinaryInteger &binaryinteger_in);

	private:
		vector<bool> powers_of_two;
		bool positive;
		void CleanUp();
};

// BinaryInteger non-member Operator Functions
BinaryInteger operator+(const BinaryInteger &int1, const BinaryInteger &int2);
BinaryInteger operator-(const BinaryInteger &int1, const BinaryInteger &int2);
BinaryInteger operator&(const BinaryInteger &int1, const BinaryInteger &int2);
BinaryInteger operator|(const BinaryInteger &int1, const BinaryInteger &int2);
BinaryInteger operator^(const BinaryInteger &int1, const BinaryInteger &int2);

int main()
{
	int user_entry;
	bool negative = false;
	vector<bool> r_binary;

	cout << "Please input an integer n: ";
	BinaryInteger binary_n;
	cin >> binary_n;
	// cout << endl; BinaryInteger binary_n({1,0,0,1,1}, 1); // DEBUG

	cout << "The binary representation for n is: ";
	binary_n.print();

	cout << endl << "Please input an integer m: ";
	BinaryInteger binary_m;
	cin >> binary_m;
	// cout << endl; BinaryInteger binary_m({1,0,0,1,0,1}, 0); // DEBUG

	cout << "The binary representation for m is: ";
	binary_m.print();

	cout << endl << "Please input binary representation, first bit indicates sign(enter"
	             << " -1 when finished): " << endl;
	cin >> negative;
	while((cin >> user_entry) && (user_entry != -1))
		r_binary.push_back((bool)user_entry);

	BinaryInteger r(r_binary, (!negative));
	// BinaryInteger r({1,0,0,1,1,0}, 0); // DEBUG

	cout << "Your integer value for r is: " << r << endl
	     << "n = "     << binary_n              << " = "; binary_n.print();              cout << endl
	     << "~n = "    << (~binary_n)           << " = "; (~binary_n).print();           cout << endl
	     << "n+m = "   << (binary_n + binary_m) << " = "; (binary_n + binary_m).print(); cout << endl
	     << "n&m = "   << (binary_n & binary_m) << " = "; (binary_n & binary_m).print(); cout << endl
	     << "n^r = "   << (binary_n ^ r)        << " = "; (binary_n ^ r).print();        cout << endl
	     << "2r = "    << (r + r)               << " = "; (r + r).print();               cout << endl
	     << "n-m = "   << (binary_n - binary_m) << " = "; (binary_n - binary_m).print(); cout << endl
	     << "n | m = " << (binary_n | binary_m) << " = "; (binary_n | binary_m).print(); cout << endl
	     << "256*n = " << (binary_n << 8)       << " = "; (binary_n << 8).print();       cout << endl
	     << "n/8 = "   << (binary_n >> 3)       << " = "; (binary_n >> 3).print();       cout << endl;

	return 0;
}


//
// BINARYINTEGER CONSTRUCTORS
//
/**
	This default constructor creates a '0' BinaryInteger by initializing the
	private integer vector 'powers_of_two' to have one value of false
*/
BinaryInteger::BinaryInteger()
{
	powers_of_two.clear();
	powers_of_two.push_back(0);
	positive = true;
}

/**
	This constructor creates a BinaryInteger by initializing the private bool vector 'powers_of_two' using a for loop

	@param input_bools is a vector that is copied over to the private bool vector in this BinaryInteger
*/
BinaryInteger::BinaryInteger(const vector<bool> &input_bools, const bool sign) : powers_of_two(input_bools), positive(sign)
{
	this->CleanUp();
}

/**
	This constructor creates a vector of bool values for each power of two using an integer
	as a parameter

	@param the parameter is an int value to be used as a bool interpretation
*/
BinaryInteger::BinaryInteger(int integer_to_construct)
{
	if(integer_to_construct < 0)
	{
		positive = false;
		integer_to_construct *= -1;
	}
	else
		positive = true;

	// reserving enough room in vector for log_2(intmax) boolean numbers
	powers_of_two.reserve(min(integer_to_construct, 32));
	while(integer_to_construct > 0)
	{
		powers_of_two.push_back(integer_to_construct & 0x1);
		integer_to_construct >>= 1;
	}

	reverse(powers_of_two.begin(), powers_of_two.end());
}

//
// BINARYINTEGER ACCESSORS
//
/**
	This function prints the vector of bools as a vector of 0s and
	1s, and prepends a '-' symbol if it is negative
*/
void BinaryInteger::print() const
{
	string output = "";

	if(positive == false)
		output += "-";

	output += "(";

	int len_powers_of_two = powers_of_two.size();
	for(int i = 0; i < len_powers_of_two; ++i)
		output += to_string(powers_of_two[i]) + ",";

	output.pop_back();
	output += ")";

	cout << output;
	return;
}

/**
	@return the private variable powers_of_two
*/
vector<bool> BinaryInteger::get_powers_of_two() const
{
	return powers_of_two;
}

/**
	@return the positive/negative status of the object
*/
bool BinaryInteger::get_positive() const
{
	return positive;
}

//
// BINARYINTEGER MEMBER OPERATOR FUNCTIONS
//
/**
	Bit shifts the 'integer' by moving the vector's units to the left

	@param specifies how much to shift
	@return BinaryInteger with shifted object powers_of_two
*/
BinaryInteger BinaryInteger::operator<<(int shift_amount) const
{
	vector<bool> powers_of_two_copy = powers_of_two;
	powers_of_two_copy.reserve(shift_amount + powers_of_two.size());

	while(shift_amount > 0)
	{
		powers_of_two_copy.push_back(0);
		shift_amount -= 1;
	}

	BinaryInteger result(powers_of_two_copy, positive);
	return result;
}

/**
	Bit shifts the 'integer' by moving the vector's units to the left

	@param specifies how much to shift
	@return (this) BinaryInteger object
*/
BinaryInteger& BinaryInteger::operator<<=(int shift_amount)
{
	powers_of_two.reserve(shift_amount + powers_of_two.size());

	while(shift_amount > 0)
	{
		powers_of_two.push_back(0);
		shift_amount -= 1;
	}

	return (*this);
}

/**
	Bit shifts the 'integer' by moving the vector's units to the right

	@param specifies how much to shift
	@return BinaryInteger with shifted object powers_of_two
*/
BinaryInteger BinaryInteger::operator>>(int shift_amount) const
{
	vector<bool> powers_of_two_copy = powers_of_two;
	powers_of_two_copy.reserve(shift_amount + powers_of_two.size());

	while(shift_amount > 0)
	{
		powers_of_two_copy.pop_back();
		shift_amount -= 1;
	}

	BinaryInteger result(powers_of_two_copy, positive);
	return result;
}

/**
	Bit shifts the 'integer' by moving the vector's units to the right

	@param specifies how much to shift
	@return (this) BinaryInteger object
*/
BinaryInteger& BinaryInteger::operator>>=(int shift_amount)
{
	while(shift_amount > 0)
	{
		powers_of_two.pop_back();
		shift_amount -= 1;
	}

	return (*this);
}

/**
	This member function outputs a BinaryInteger as a base 10 number by using a base change to change the
	class objects boolean values into their respective base 2

	@param ostream object (usually cout) that will collect the correct total_value_of_integer
	       and output it as an ostream object.
	@param a BinaryInteger that the user wants to print out and has used with
	       an ostream object.
	@return returns an ostream object that is filled with the correct
	        base 10 BinaryInteger value
*/
ostream& operator<<(ostream &outstream, const BinaryInteger &binaryinteger_out)
{
	int total_value_of_integer = 0,
	    power_of_two = 1;

	for(int i = binaryinteger_out.powers_of_two.size()-1; i >= 0; --i)
	{
		// if(binaryinteger_out.powers_of_two[i] == 1)
		// 	total_value_of_integer += power_of_two;

		total_value_of_integer += binaryinteger_out.powers_of_two[i] ? power_of_two : 0;

		// total_value_of_integer += ((int)(!(binaryinteger_out.powers_of_two[i]))-1) & power_of_two;

		power_of_two <<= 1;
	}

	if(binaryinteger_out.positive == false)
		total_value_of_integer *= -1;

	outstream << total_value_of_integer;
	return outstream;
}

/**
	Will receive an output from the user and convert the integer into binary components

	@return returns an istream object filled with the user's integer input
*/
istream& operator>>(istream &instream, BinaryInteger &binaryinteger_in)
{
	int user_integer_input;

	instream >> user_integer_input;
	binaryinteger_in.positive = true;
	if(user_integer_input < 0)
	{
		user_integer_input *= (-1);
		binaryinteger_in.positive = false;
	}

	binaryinteger_in.powers_of_two.clear();
	// reserving enough room in vector for log_2(intmax) boolean numbers
	binaryinteger_in.powers_of_two.reserve(min(user_integer_input, 32));
	while(user_integer_input > 0)
	{
		binaryinteger_in.powers_of_two.push_back((bool)(user_integer_input & 0x1));
		user_integer_input >>= 1;
	}

	reverse(binaryinteger_in.powers_of_two.begin(), binaryinteger_in.powers_of_two.end());

	return instream;
}

/**
	Flips all 1's to 0 and vice versa

	@return object that is not the object that called it with all bits flipped
*/
BinaryInteger BinaryInteger::operator~()
{
	vector<bool> copy_of_powers_of_two;
	int size_of_powers_of_two = powers_of_two.size();
	copy_of_powers_of_two.reserve(size_of_powers_of_two);
	bool copy_positive = !positive;

	for(int i = 0; i < size_of_powers_of_two; ++i)
	{
		// copy_of_powers_of_two.push_back(1);
		copy_of_powers_of_two.push_back(!(powers_of_two[i]));
	}

	BinaryInteger copy_of_integer(copy_of_powers_of_two, copy_positive);
	return copy_of_integer;
}

/**
	Removes the bits in the front of the private member vector
	in order to make the vector of bool objects cleaner
*/
void BinaryInteger::CleanUp()
{
	auto vector_len = powers_of_two.size();
	vector<bool> new_powers_of_two;
	new_powers_of_two.reserve(vector_len);
	bool collect = false;

	for(auto i = 0; i < vector_len; ++i)
	{
		if(powers_of_two[i] == 1)
			collect = true;

		if(collect == true)
			new_powers_of_two.push_back(powers_of_two[i]);
	}

	powers_of_two = new_powers_of_two;
	return;
}

//
// BINARYINTEGER NON-MEMBER FUNCTIONS
//
/**
	Adds BinaryIntegers using one's complement addition
	answer = binary_left + binary_right

	@param a BinaryInteger to be added on left
	@param a BinaryInteger to be added on right
	@return the result in one's complement after being added
*/
BinaryInteger operator+(const BinaryInteger &binary_left, const BinaryInteger &binary_right)
{
	vector<bool> binary_added_result,
	             boolean_left = binary_left.get_powers_of_two(),
	             boolean_right = binary_right.get_powers_of_two();
	bool positive_left = binary_left.get_positive(),
	     positive_right = binary_right.get_positive(),
	     result_positive;
	int size_left = boolean_left.size(),
	    size_right = boolean_right.size();

	// adding 0's in front of the bits to
	// create an easy addition environment
	reverse(boolean_right.begin(), boolean_right.end());
	reverse(boolean_left.begin(),  boolean_left.end());
	if(size_left > size_right)
	{	
		while(size_left > size_right)
		{
			boolean_right.push_back(0);
			++size_right;
		}
	}
	else if(size_left < size_right)
	{	
		while(size_left < size_right)
		{
			boolean_left.push_back(0);
			++size_left;
		}
	}

	binary_added_result.reserve(size_left);

	if(positive_left == positive_right)
	{
		short int sum;
		bool carry_bit = 0;
		for(int i = 0; i < size_left; ++i)
		{
			sum = (boolean_left[i] + boolean_right[i] + carry_bit);
			carry_bit = (sum >= 2);
			binary_added_result.push_back(sum % 2);
		}

		if(carry_bit == 1)
			binary_added_result.push_back(1);

		result_positive = positive_left;
	}
	// positive_left != positive_right
	else
	{
		// finding out if left boolean is bigger or
		// right, or equal one's complement numbers
		bool leftMagnitudeIsLarger,
		     equal_boolean = false;
		for(int i = size_left-1; i >= 0; --i)
		{
			if(boolean_left[i] > boolean_right[i])
			{
				leftMagnitudeIsLarger = true;
				equal_boolean = false;
				break;
			}
			else if(boolean_left[i] < boolean_right[i])
			{
				leftMagnitudeIsLarger = false;
				equal_boolean = false;
				break;
			}
			else if((i+1) == size_left)
				equal_boolean = true;
		}

		if(equal_boolean == true)
		{
			binary_added_result.clear();
			binary_added_result.push_back(0);
			result_positive = true;
		}
		else
		{
			// actual subtraction happens here O(n)
			if(leftMagnitudeIsLarger == true)
			{
				bool borrow_bit = false;
				result_positive = positive_left;
				for(int i = 0; i < size_left; ++i)
				{
					if(borrow_bit == true)
					{
						if(boolean_left[i] == 1)
						{
							boolean_left[i] = 0;
							borrow_bit = false;
						}
						// boolean_left[i] == 0
						else
							boolean_left[i] = 1;
					}

					if(boolean_left[i] == 0 && boolean_right[i] == 1)
					{
						borrow_bit = true;
						binary_added_result.push_back(1);
					}
					else
						binary_added_result.push_back(boolean_left[i] - boolean_right[i]);
				}
			}
			// leftMagnitudeIsLarger == false
			else
			{
				bool borrow_bit = false;
				result_positive = positive_right;
				for(int i = 0; i < size_right; ++i)
				{
					if(borrow_bit == true)
					{
						if(boolean_right[i] == 1)
						{
							boolean_right[i] = 0;
							borrow_bit = false;
						}
						// boolean_left[i] == 0
						else
							boolean_right[i] = 1;
					}

					if(boolean_right[i] == 0 && boolean_left[i] == 1)
					{
						borrow_bit = true;
						binary_added_result.push_back(1);
					}
					else
						binary_added_result.push_back(boolean_right[i] - boolean_left[i]);
				}
			}
		}
	}

	reverse(binary_added_result.begin(),  binary_added_result.end());
	BinaryInteger result(binary_added_result, result_positive);
	return result;
}

/**
	Subtracts BinaryIntegers using one's complement subtraction
	answer = binary_left - binary_right

	@param BinaryInteger binary_left known as minuend
	@param BinaryInteger binary_right known as subtrahend
	@return the result after subtracted
*/
BinaryInteger operator-(const BinaryInteger &binary_left, const BinaryInteger &binary_right)
{
	vector<bool> boolean_right = binary_right.get_powers_of_two();
	bool positive_right = !(binary_right.get_positive());

	BinaryInteger number_to_subtract(boolean_right, positive_right),
	              answer = (binary_left + number_to_subtract);
	return answer;
}

/**
	Uses & operator to "AND" the bits of two BinaryInteger objects
	&:
	0 0 -> 0
	0 1 -> 0
	1 0 -> 0
	1 1 -> 1

	@param binary_left that is an object with bits
	@param binary_right that is an object with bits
	@return result with bits anded from both parameters
*/
BinaryInteger operator&(const BinaryInteger &binary_left, const BinaryInteger &binary_right)
{
	vector<bool> boolean_left  = binary_left.get_powers_of_two(),
	             boolean_right = binary_right.get_powers_of_two(),
	             binary_result;
	bool positive_left   = !(binary_left.get_positive()),
	     positive_right  = !(binary_right.get_positive()),
	     result_positive = !(positive_right & positive_left);
	int size_left  = boolean_left.size(),
	    size_right = boolean_right.size(),
	    starting_index = (size_left > size_right) ? size_right : size_left;

	binary_result.reserve(starting_index);
	reverse(boolean_right.begin(), boolean_right.end());
	reverse(boolean_left.begin(),  boolean_left.end());

	for(int i = starting_index; i >= 0; --i)
		binary_result.push_back(boolean_left[i] & boolean_right[i]);

	BinaryInteger answer(binary_result, result_positive);
	return answer;
}

/**
	Uses | operator "OR" to the bits of two BinaryInteger objects
	|:
	0 0 -> 0
	0 1 -> 1
	1 0 -> 1
	1 1 -> 1

	@param binary_left that is an object with bits
	@param binary_right that is an object with bits
	@return result with bits and-ed from both parameters
*/
BinaryInteger operator|(const BinaryInteger &binary_left, const BinaryInteger &binary_right)
{
	vector<bool> boolean_left  = binary_left.get_powers_of_two(),
	             boolean_right = binary_right.get_powers_of_two(),
	             binary_result;
	bool positive_left   = !(binary_left.get_positive()),
	     positive_right  = !(binary_right.get_positive()),
	     result_positive = !(positive_right | positive_left);
	int size_left  = boolean_left.size(),
	    size_right = boolean_right.size();

	reverse(boolean_right.begin(), boolean_right.end());
	reverse(boolean_left.begin(),  boolean_left.end());
	if(size_left > size_right)
	{	
		while(size_left > size_right)
		{
			boolean_right.push_back(0);
			++size_right;
		}
	}
	else if(size_left < size_right)
	{	
		while(size_left < size_right)
		{
			boolean_left.push_back(0);
			++size_left;
		}
	}

	binary_result.reserve(size_left);
	for(int i = size_left-1; i >= 0; --i)
		binary_result.push_back(boolean_left[i] | boolean_right[i]);

	BinaryInteger answer(binary_result, result_positive);
	return answer;
}

/**
	Uses ^ operator to "XOR"/"EXCLUSIVE OR" the bits of
	two BinaryInteger objects
	^:
	0 0 -> 0
	0 1 -> 1
	1 0 -> 1
	1 1 -> 0

	@param binary_left that is an object with bits
	@param binary_right that is an object with bits
	@return result with bits xor-ed from both parameters
*/
BinaryInteger operator^(const BinaryInteger &binary_left, const BinaryInteger &binary_right)
{
	vector<bool> boolean_left  = binary_left.get_powers_of_two(),
	             boolean_right = binary_right.get_powers_of_two(),
	             binary_result;
	bool positive_left   = !(binary_left.get_positive()),
	     positive_right  = !(binary_right.get_positive()),
	     result_positive = !(positive_right ^ positive_left);
	int size_left  = boolean_left.size(),
	    size_right = boolean_right.size();

	reverse(boolean_right.begin(), boolean_right.end());
	reverse(boolean_left.begin(),  boolean_left.end());
	if(size_left > size_right)
	{	
		while(size_left > size_right)
		{
			boolean_right.push_back(0);
			++size_right;
		}
	}
	else if(size_left < size_right)
	{	
		while(size_left < size_right)
		{
			boolean_left.push_back(0);
			++size_left;
		}
	}

	binary_result.reserve(size_left);
	for(int i = size_left-1; i >= 0; --i)
		binary_result.push_back(boolean_left[i] ^ boolean_right[i]);

	BinaryInteger answer(binary_result, result_positive);
	return answer;
}