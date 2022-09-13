#include <iostream>
#include <string>

using namespace std;

string operator*(const string,const string); // overloading the multiplication operator
string operator+(const string,const string); // overloading the addition operator
string operator-(const string,const string); // overloading the substraction operator
bool operator>(const string, const string); // overloading the comprasion operators
bool operator<(const string, const string);
bool operator==(const string, const string);

string multiplication_by_10(string&, size_t); // multiplication by 10 to the power
void to_equal_size(string&, string&); // adding strings to the same length


int main() {

	string a = "3141592653589793238462643383279502884197169399375105820974944592";
	string b = "2718281828459045235360287471352662497757247093699959574966967627";

	cout << "a:\t" << a << endl;
	cout << "b:\t" << b << endl;

	cout << "a-b: \t" << a - b << endl;
	
	cout << "a+b: \t" << a + b << endl;

	cout << "a*b: \t" << a * b << endl;

	return EXIT_SUCCESS;
}

// overloading the multiplication operator
string operator*(const string Str1,const string Str2) {
	// Making a decision depending on the sign
	if (Str1.at(0) == '-' && Str2.at(0) == '-') return Str1.substr(1) * Str2.substr(1);
	else if (Str1.at(0) == '-' && Str2.at(0) != '-') return (Str1.substr(1) * Str2).insert(0, 1, '-');
	else if (Str1.at(0) != '-' && Str2.at(0) == '-') return (Str1 * Str2.substr(1)).insert(0, 1, '-');

	string XY;

	// Base case
	if (Str1.size() <= 2 && Str2.size() <= 2) {
		XY = to_string(stoi(Str1) * stoi(Str2));
		return XY;
	}

	// Recursion case
	else {
		// We complement one of the multipliers to the same even length by adding zeros to the beginning
		string X = Str1, Y = Str2;
		to_equal_size(X, Y);
		size_t n = X.size(); // Size of multipliers
		string a, b, c, d, p, q, ac, bd, pq, adbc;
		
		// Split first multipliers on 2 parts (a and b)
		
		for (size_t i = 0; i < n / 2; ++i) {
			a.push_back(X.at(i));
			b.push_back(X.at(n / 2 + i));
		}
		// Split second multipliers on 2 parts (c and d)
		for (size_t i = 0; i < n / 2; ++i) {
			c.push_back(Y.at(i));
			d.push_back(Y.at(n / 2 + i));
		}

		p = a + b;
		q = c + d;
		// Recursively calculate
		ac = a * c;
		bd = b * d;
		pq = p * q;
		adbc = pq - ac - bd;

		// final formula
		XY = multiplication_by_10(ac, n) + multiplication_by_10(adbc, n / 2) + bd;
	}

	return XY;
}

// overloading the addition operator
string operator+(const string Str1,const string Str2){
	// Making a decision depending on the sign
	if (Str1.at(0) == '-' && Str2.at(0) != '-')	return Str2 - Str1.substr(1);
	else if (Str1.at(0) != '-' && Str2.at(0) == '-') return Str1 - Str2.substr(1);
	else if (Str1.at(0) == '-' && Str2.at(0) == '-') return (Str1.substr(1) + Str2.substr(1)).insert(0, 1, '-');

	string Sum;
	int addition = 0;

	for (int i = (int)Str1.size() - 1, j = (int)Str2.size() - 1; i >= 0 || j >= 0; --i, --j) {
		char number1 = i < 0 ? 0 : Str1.at(i) - '0'; // We complement the numbers to the same length with additional zeros
		char number2 = j < 0 ? 0 : Str2.at(j) - '0'; // And we translate from characters to numbers by subtracting '0'
		char result = number1 + number2 + addition; // We begin the addition with smaller digits
		if (result > 9) {
			result = result - 10;
			addition = 1;
		}
		else {
			addition = 0;
		}
		Sum.push_back(result + '0');
	}

	if (addition == 1) Sum.push_back('1');

	// We change the digits of the number among themselves
	for (size_t i = 0; i < Sum.size() / 2; ++i) {
		swap(Sum.at(i), Sum.at(Sum.size() - i - 1));
	}

	return Sum;
}

// overloading the substraction operator
string operator-(const string Str1, const string Str2){
	// Making a decision depending on the sign
	if (Str1.at(0) == '-' && Str2.at(0) != '-')	return (Str1.substr(1) + Str2).insert(0, 1, '-');
	else if (Str1.at(0) != '-' && Str2.at(0) == '-') return Str1 + Str2.substr(1);
	else if (Str1.at(0) == '-' && Str2.at(0) == '-') return Str2.substr(1) - Str1.substr(1);

	// In the case when the second number is greater than the first, we swap the numbers and add '-' to the result
	if (Str2 > Str1) return (Str2 - Str1).insert(0, 1, '-');

	string Sub;
	int substraction = 0;

	for (int i = (int)Str1.size() - 1, j = (int)Str2.size() - 1; i >= 0 || j >= 0; --i, --j) {
		char number1 = i < 0 ? 0 : Str1.at(i) - '0'; // We complement the numbers to the same length with additional zeros
		char number2 = j < 0 ? 0 : Str2.at(j) - '0'; // And we translate from characters to numbers by subtracting '0'
		char result = number1 - number2 - substraction;

		if (result >= 0) {
			substraction = 0;
		}
		else {
			result = result + 10;
			substraction = 1;
		}
		Sub.push_back(result + '0');
	}

	// Removing zeros from the beginning of the number
	for (size_t i = Sub.size() - 1; i > 0; --i) {
		if (Sub.at(i) == '0') Sub.pop_back();
		else break;
	}

	// We change the digits of the number among themselves
	for (size_t i = 0; i < Sub.size() / 2; ++i) {
		swap(Sub.at(i), Sub.at(Sub.size() - i - 1));
	}

	return Sub;
}

// overloading the comprasion operator
bool operator>(const string Str1, const string Str2){
	// Making a decision depending on the sign
	if (Str1.at(0) == '-' && Str2.at(0) != '-')	return false;
	else if (Str1.at(0) != '-' && Str2.at(0) == '-') return true;
	else if (Str1.at(0) == '-' && Str2.at(0) == '-') return Str1.substr(1) > Str2.substr(1);

	// Making a decision depending on the number of digits of numbers
	if (Str1.size() > Str2.size()) return true;
	else if (Str1.size() == Str2.size()) {
		for (size_t i = 0; i < Str1.size(); ++i) {
			if (Str1.at(i) > Str2.at(i)) return true;
			else if (Str1.at(i) < Str2.at(i)) return false;
		}
		return false;
	}
	else return false;
}

// overloading the comprasion operator
bool operator<(const string Str1, const string Str2){
	// Making a decision depending on the sign
	if (Str1.at(0) == '-' && Str2.at(0) != '-')	return true;
	else if (Str1.at(0) != '-' && Str2.at(0) == '-') return false;
	else if (Str1.at(0) == '-' && Str2.at(0) == '-') return Str1.substr(1) < Str2.substr(1);

	// Making a decision depending on the number of digits of numbers
	if (Str1.size() < Str2.size()) return true;
	else if (Str1.size() == Str2.size()) {
		for (size_t i = 0; i < Str1.size(); ++i) {
			if (Str1.at(i) < Str2.at(i)) return true;
			else if (Str1.at(i) > Str2.at(i)) return false;
		}
		return false;
	}
	else return false;
}

// overloading the equality operator
bool operator==(const string Str1, const string Str2){

	if (Str1.size() == Str2.size()) {
		for (size_t i = 0; i < Str1.size(); ++i) {
			if (Str1.at(i) != Str2.at(i)) return false;
		}
		return true;
	}
	else {
		return false;
	}
}

// Multiplying a number by 10 to the power of "power"
string multiplication_by_10(string &number, size_t power){
	// Add to the number the number of zeros equal to the power of 10
	if (number.at(0) != '0') {
		for (size_t i = 0; i < power; ++i) {
			number.push_back('0');
		}
	}

	return number;
}

// We complement the lines to the same length by adding zeros to the beginning
void to_equal_size(string& Str1, string& Str2) {
	size_t n = max(Str1.size(), Str2.size());
	if (n % 2 != 0) ++n;

	Str1.insert(0, n - Str1.size(), '0');
	Str2.insert(0, n - Str2.size(), '0');
}
