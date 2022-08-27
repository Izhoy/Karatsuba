#include <iostream>
#include <string>

using namespace std;

string operator*(const string,const string); // ���������� ��������� ���������
string operator+(const string,const string); // ���������� ��������� ��������
string operator-(const string,const string); // ���������� ��������� ���������
bool operator>(const string, const string); // ���������� ���������� ���������
bool operator<(const string, const string);
bool operator==(const string, const string);

string multiplication_by_10(string&, size_t); // ������� ��������� ����� �� 10 � �������


int main() {

	

	/*string a = "3141592653589793238462643383279502884197169399375105820974944592";
	string b = "2718281828459045235360287471352662497757247093699959574966967627";

	cout << "a:\t" << a << endl;
	cout << "b:\t" << b << endl;

	cout << "a-b: \t" << a - b << endl;
	
	cout << "a+b: \t" << a + b << endl;

	cout << "a*b: \t" << a * b << endl;*/

	return EXIT_SUCCESS;
}

// ��������� ���� ����� ������� ��������
string operator*(const string Str1,const string Str2) {
	// �������� ������� � ����������� �� �����
	if (Str1.at(0) == '-' && Str2.at(0) == '-') return Str1.substr(1) * Str2.substr(1);
	else if (Str1.at(0) == '-' && Str2.at(0) != '-') return (Str1.substr(1) * Str2).insert(0, 1, '-');
	else if (Str1.at(0) != '-' && Str2.at(0) == '-') return (Str1 * Str2.substr(1)).insert(0, 1, '-');

	string Production;

	// ������� ������
	if (Str1.size() == 1 && Str2.size() == 1) {
		Production = to_string(stoi(Str1) * stoi(Str2));
		return Production;
	}

	// ����������� ������
	else {
		string a, b, c, d, ac, bd, bc, ad;
		
		// ��������� ������ ��������� �� 2 ����� (a � b)
		if (Str1.size() == 1) {
			a = Str1;
			b = "0";
		}
		else {
			for (size_t i = 0; i < Str1.size() / 2; ++i) {
				a.push_back(Str1.at(i));
				b.push_back(Str1.at(Str1.size() / 2 + i));
			}
		}

		// ��������� ������ ��������� �� 2 ����� (c � d)
		if (Str2.size() == 1) {
			c = Str2;
			d = "0";
		}
		else {
			for (size_t i = 0; i < Str2.size() / 2; ++i) {
				c.push_back(Str2.at(i));
				d.push_back(Str2.at(Str2.size() / 2 + i));
			}
		}
		// ���������� ���������
		bc = b * c;
		ac = a * c;
		bd = b * d;
		ad = a * d;

		// ��������� �������
		Production = multiplication_by_10(ac, Str1.size()/2 + Str2.size()/2) + 
			multiplication_by_10(ad, Str1.size() / 2) + multiplication_by_10(bc, Str2.size()/2) + bd;
	}

	return Production;
}

// �������� ���� ����� ���������
string operator+(const string Str1,const string Str2){
	// �������� ������� � ����������� �� ������ �����
	if (Str1.at(0) == '-' && Str2.at(0) != '-')	return Str2 - Str1.substr(1);
	else if (Str1.at(0) != '-' && Str2.at(0) == '-') return Str1 - Str2.substr(1);
	else if (Str1.at(0) == '-' && Str2.at(0) == '-') return (Str1.substr(1) + Str2.substr(1)).insert(0, 1, '-');

	string Sum;
	int addition = 0;

	for (int i = (int)Str1.size() - 1, j = (int)Str2.size() - 1; i >= 0 || j >= 0; --i, --j) {
		char number1 = i < 0 ? 0 : Str1.at(i) - '0'; // ��������� ����� �� ���������� ����� ��������������� ������
		char number2 = j < 0 ? 0 : Str2.at(j) - '0'; // � ��������� �� �������� � ����� ���� ��������� '0'
		char result = number1 + number2 + addition; // �������� �������� � ������� ��������
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

	// ������ ������� ����� ����� �����
	for (size_t i = 0; i < Sum.size() / 2; ++i) {
		swap(Sum.at(i), Sum.at(Sum.size() - i - 1));
	}

	return Sum;
}

// ��������� ���� ����� ���������
string operator-(const string Str1, const string Str2){
	// �������� ������� � ����������� �� ������ �����
	if (Str1.at(0) == '-' && Str2.at(0) != '-')	return (Str1.substr(1) + Str2).insert(0, 1, '-');
	else if (Str1.at(0) != '-' && Str2.at(0) == '-') return Str1 + Str2.substr(1);
	else if (Str1.at(0) == '-' && Str2.at(0) == '-') return Str2.substr(1) - Str1.substr(1);

	// � ������, ����� ������ ����� ������ ������� ������ ����� ������� � � ��������� ��������� '-'
	if (Str2 > Str1) return (Str2 - Str1).insert(0, 1, '-');

	string Sub;
	int substraction = 0;

	for (int i = (int)Str1.size() - 1, j = (int)Str2.size() - 1; i >= 0 || j >= 0; --i, --j) {
		char number1 = i < 0 ? 0 : Str1.at(i) - '0'; // ��������� ����� �� ���������� ����� ��������������� ������
		char number2 = j < 0 ? 0 : Str2.at(j) - '0'; // � ��������� �� �������� � ����� ���� ��������� '0'
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

	// ������� ���� �� ������ �����
	for (size_t i = Sub.size() - 1; i > 0; --i) {
		if (Sub.at(i) == '0') Sub.pop_back();
		else break;
	}

	// ������ ������� ����� �����
	for (size_t i = 0; i < Sub.size() / 2; ++i) {
		swap(Sub.at(i), Sub.at(Sub.size() - i - 1));
	}

	return Sub;
}

// ���������� ��������� ���������
bool operator>(const string Str1, const string Str2){
	// �������� ������� � ����������� �� ����� �����
	if (Str1.at(0) == '-' && Str2.at(0) != '-')	return false;
	else if (Str1.at(0) != '-' && Str2.at(0) == '-') return true;
	else if (Str1.at(0) == '-' && Str2.at(0) == '-') return Str1.substr(1) > Str2.substr(1);

	// �������� ������� � ����������� �� ���������� �������� �����
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

// ���������� ��������� ���������
bool operator<(const string Str1, const string Str2){
	// �������� ������� � ����������� �� ����� �����
	if (Str1.at(0) == '-' && Str2.at(0) != '-')	return true;
	else if (Str1.at(0) != '-' && Str2.at(0) == '-') return false;
	else if (Str1.at(0) == '-' && Str2.at(0) == '-') return Str1.substr(1) < Str2.substr(1);

	// �������� ������� � ����������� �� ���������� �������� �����
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

// ���������� ��������� ���������
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

// ��������� ����� �� 10 � ������� power
string multiplication_by_10(string &number, size_t power){
	// ��������� � ����� ���������� ����� ������ ������� 10
	if (number.at(0) != '0') {
		for (size_t i = 0; i < power; ++i) {
			number.push_back('0');
		}
	}

	return number;
}
