#pragma once
#pragma once
#ifndef election_H
#define election_H
#include<iostream>
#include<string>
#include"candidate.h"
#include"voter.h"
using namespace std;
class election {
protected:
	static int id;
	int candidate_no;
	int candidate_count;
	string title;
	candidate** C;
	int voter_no;
	voter** V;
	string area;
	bool isActive;
	string startDate, endDate;
public:

	election(int c, int v, string t, string a, bool active, string S_D, string E_D);
	election();
	void set_title(string t);
	void set_area(string a);
	void set_startDate(string S_D);
	void set_endDate(string E_D);
	//input output -> operatoe overloading
	friend istream& operator>>(istream& in, election& e);
	friend ostream& operator<<(ostream& out, const election& e);
	//Getters
	int get_id();
	int get_candidate_no();
	string get_title();
	int get_voter_no();
	candidate** get_candidate();
	voter** get_voter();
	string get_area();
	string get_startDate();
	string get_endDate();
	//add candidate
	//void addCandidate();
	void vote(int index);
	//candidate* getMNA();
	//void  create_election();
	void startElection();
	void endElection();
	bool isactive();
	virtual void addCandidate(string name, string party) = 0;
};
#endif