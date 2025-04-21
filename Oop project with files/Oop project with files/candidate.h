#pragma once
#pragma once
#ifndef candidate_H
#define candidate_H
#include<iostream>
#include<string>
using namespace std;
#include"constituency.h"
class candidate {
private:
	static int id;
	int c_ID;
	string name;
	string party;
	string area;
	string position;
	int noOfvotes;
	string bio;
	Code* code;
public:
	candidate();
	candidate(string n, string p, string a, string pos, int n_votes, string b);
	void setName(string n);
	void setParty(string p);
	void set_ID();
	void setArea(string a);
	void setPosition(string p);
	void setnoOfvotes(int n);
	void setBio(string b);
	string getName() const;
	string getParty() const;
	string getArea() const;
	string getPosition() const;
	int getnoOfvotes() const;
	string getBio() const;
	Code* getcons();
	void setcandidate(string n, string p, string a, string P, string b, int no);
	friend istream& operator >>(istream& in, candidate& c);

	friend ostream& operator<<(ostream& out, const candidate& c);
	void addVote();

};
#endif