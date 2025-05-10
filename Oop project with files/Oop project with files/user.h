#pragma once
#ifndef user_H
#define user_H
#include<iostream>
#include<string>
using namespace std;

class user
{
protected:
	string cnic;
	string name;
	string password;
public:
	user(string c = 0, string n = "", string p = "");
	virtual string getcnic() = 0;
	string getname()const;
	string getpass()const;
	void setcnic(string c);
	void setname(string n);
	void setpass(string n);
	void inputUserData();

	void outputUserData()const;
};
#endif