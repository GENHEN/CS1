/*
File Name: hw5.cpp
Author: genhen
Description: Create a function that computes the number
             of integer partitions of n with each element
             at most k. The program should allow the user
             to input a positive integer m (you may assume
             the input will indeed be a positive integer,
             no need to error check), print out p(k,m) for
             k = 1, 2,3,...,m, and then create a file named
             pknTable.txt that creates a table of all values
             for 1 <= k <= m and 1 <= n <= m.
Run: g++ -std=c++14 -o hw5.exe hw5.cpp && ./hw5.exe && rm hw5.exe
*/

#include <cmath>
#include <fstream>
#include <iostream>
// #include <string>
// #include <vector>

using namespace std;

int integer_partition(int k, int n);

int main()
{
	int m_entered,
	    m_entered_plus;

	cout << "Welcome! Please input a number m: ";
	cin >> m_entered;
	m_entered_plus = m_entered+1;


	for(int i = 1; i < m_entered_plus; ++i)
		cout << endl << "p(" << i << ',' << m_entered << ") = " << integer_partition(i, m_entered);

	ofstream output;
	output.open("pknTable.txt");
	cout << endl << endl << "Creating file ... ";

	for(int i = 1; i < m_entered_plus; ++i)
	{
		for(int j = 1; j < m_entered_plus; ++j)
			output << integer_partition(i, j) << ' ';

		if(i != m_entered)
			output << endl;
	}

	output.close();
	cout << "Done." << endl;

	return 0;
}

int integer_partition(int k, int n)
{
	if(k >= 1 && k <= n)
		return (integer_partition(k, (n - k)) + integer_partition((k - 1), n));
	else if(k > n)
		return integer_partition(n,n);
	else if(k >= 0 && n == 0)
		return 1;
	else
		return 0;
}
