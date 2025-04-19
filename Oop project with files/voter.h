#pragma once
#pragma once
#ifndef voting_H
#define voting_H
#include<iostream>
#include<string>
#include"user.h"
#include"candidate.h"
using namespace std;
class voter :public user {
protected:
	static int id;
	bool status;
	bool hasvoted=0;
	int age;
public:
	voter(bool s = 0, int a = 0);

	int getcnic() override;
	void setstatus(bool s);
	void setage(int a);
	void sethasvoted(bool s);
	bool getstatus();
	int getage();
	bool gethasvoted();
	friend istream& operator>>(istream& in, voter& v);
	friend ostream& operator<<(ostream& out, const voter& v);

	void cast_vote(candidate* c[], int s);
};
#endif
