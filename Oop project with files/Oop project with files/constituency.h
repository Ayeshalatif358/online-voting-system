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
	void setcode(string n);
	string getcode();
	void operator=(Code c)
	{
		c.c_code = c_code;
	}
	friend istream& operator>>(istream& in, Code c);
	friend ostream& operator<<(ostream& out, Code c);
};
#endif