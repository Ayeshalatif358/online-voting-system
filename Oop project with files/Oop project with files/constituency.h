#pragma once
#ifndef code_H
#define code_H
#include<iostream>
#include<string>
using namespace std;
class Code
{
private:
	string c_code, n_code;
public:
	Code();
	void setcode(string c);
	void setNcode(string n);
	string getcode();
	string getNcode();
	void operator=(Code c);

	friend istream& operator>>(istream& in, Code c);
	friend ostream& operator<<(ostream& out, Code c);
	bool check_equal(Code* t);
	bool operator==(Code t);
};
#endif