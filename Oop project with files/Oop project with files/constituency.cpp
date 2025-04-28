#include<iostream>
#include<string>
#include"constituency.h"
using namespace std;
Code::Code()
{
	c_code = "0";
	n_code = "null";
}
string Code::getcode() { return c_code; }
string Code::getNcode() { return n_code; }
void Code::setcode(string c){
	c_code = c;
}
void Code::setNcode(string n){
	n_code = n;
}
istream& operator>>(istream& in, Code c){
	cout << "Enter constituency code: ";
	in >> c.c_code;
	cout << "Enter national code: ";
	in >> c.n_code;
	return in;
}
ostream& operator<<(ostream& out, Code c){
	out << "Constituency code: " << c.c_code;
	out << "National code: " << c.n_code;
	return out;
}
void Code::operator=(Code c){
	c.c_code = c_code;
	c.n_code = c_code;
}
bool Code::check_equal(Code* t){
	if (this->c_code == t->c_code)
	{
		return true;
	}
	return false;
}
bool Code::operator==(Code t){
	if (this->c_code == t.c_code)
	{
		return true;
	}
	return false;
}