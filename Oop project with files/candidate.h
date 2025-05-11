#pragma once
#ifndef Cand_H
#define Cand_H
#include<iostream>
#include<string>
#include "code.h"
class candidate {
private:
	int c_id;
	string name;
	string party;
	string area;
	string position;
	string cnic;
	int noOfvotes;
	string bio;
	Code* code;
public:
	candidate();
	candidate(string n, string p, string a, string pos, int n_votes, string b);
	void setName(string n);
	void setParty(string p);
	void setcode(string c);
	void setNcode(string n);
	void setArea(string a);
	void setcnic(string n);
	void setPosition(string p);
	void setnoOfvotes(int n);
	void setc_id(int a);
	void setBio(string b);
	int getc_id() const;
	string getName() const;
	string getParty() const;
	string getArea() const;
	string getPosition() const;
	int getnoOfvotes() const;

	string getBio() const;
	string getcnic()const;
	Code getcons();
	void inputFile(string filename, string idFILE);
	void setcandidate(string n, string p, string a, string P, string b, int no);
	friend istream& operator >>(istream& in, candidate& c);
	void inputPartyinfo(string filename);
	friend ostream& operator<<(ostream& out, const candidate& c);
	void addVote();
	void set_leaders();

};
#endif