#pragma once
#ifndef user_H
#define user_H
#include<iostream>
#include<string>
using namespace std;

class user
{
protected:
	int cnic;
	string name;
	string password;
public:
	user(int c = 0, string n = "", string p = "");
	virtual int getcnic() = 0;
	string getname()const;
	string getpass()const;
	void setcnic(int c);
	void setname(string n);
	void setpass(string n);
	void inputUserData();

	void outputUserData()const;
};
#endif