#include<iostream>
#include<string>
#include"constituency.h"
using namespace std;
Code::Code()
{
	c_code = "0";
	n_code = "";
}
string Code::getcode() { return c_code; }
void Code::setcode(string n)
{
	n_code = n;
}
istream& operator>>(istream& in, Code c)
{
	cout << "Enter constituency code: ";
	in >> c.c_code;
	cout << "Enter national code: ";
	in >> c.n_code;
	return in;
}
ostream& operator<<(ostream& out, Code c)
{
	out << "Constituency code: " << c.c_code;
	out << "National code: " << c.n_code;
	return out;
}