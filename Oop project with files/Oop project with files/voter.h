#pragma once
#ifndef voting_H
#define voting_H
#include<iostream>
#include<string>
#include"user.h"
#include"code.h"
using namespace std;
class voter :public user {
protected:
	static int id;
	bool Phasvoted = 0;
	bool Nhasvoted = 0;
	int age;
	Code cons;
public:
	Code getVoterCode()const;
	void signupToPendingFile();
	voter(int a = 0);
	string getcnic() override;
	void setage(int a);
	void setPhasvoted(bool hv);
	void setNhasvoted(bool hv);
	void setid(int a);
	void setVoterCode(Code c);
	int getage();
	int getid();
	static void loadLastVoterId();
	voter login();
	bool getNhasvoted();
	bool getPhasvoted();
	friend istream& operator>>(istream& in, voter& v);
	friend ostream& operator<<(ostream& out, voter& v);
	//void loadLastVoterId();

};
#endif