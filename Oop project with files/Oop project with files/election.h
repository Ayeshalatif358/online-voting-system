#pragma once
#pragma once
#ifndef election_H
#define election_H
#include<iostream>
#include<string>
#include"candidate.h"
#include"voter.h"
using namespace std;
class date
{
private:
	int day, month, year;
public:
	date()
	{
		day = 0;
		month = 0;
		year = 0;
	}
	friend istream& operator>>(istream& in, date& d)
	{
		cout << "Enter day: ";
		in >> d.day;
		cout << "Enter month: ";
		in >> d.month;
		cout << "Enter year: ";
		in >> d.year;
		return in;
	}
	friend ostream& operator<<(ostream& out,const date& d)
	{
		out << d.day << " - "<<d.month<<" - "<<d.year<<" - \n";
		return out;
	}
};
class election {
protected:
	static int id;
	int candidate_no;
	int candidate_count;
	Code* mCode;
	Code* pCode;
	int mna_count;
	string title;
	candidate** C;
	int voter_no;
	voter** V;
	string area;
	bool isActive;
	date startDate, endDate;
public:
virtual ~election();
	election(int c, int v, string t, string a, bool active);
	election();
	void set_title(string t);
	void set_area(string a);
	void set_startDate();
	void set_endDate();
	//input output -> operatoe overloading
	friend istream& operator>>(istream& in, election& e);
	friend ostream& operator<<(ostream& out, const election& e);
	//Getters
	virtual int get_id();
	int get_candidate_no();
	string get_title();
	int get_voter_no();
	candidate** get_candidate();
	voter** get_voter();
	string get_area();
	date get_startDate();
	date get_endDate();
	Code* selectedMna();
	Code* selectedMpa();
	int getmnaCount();
	//add candidate
	int check(int i, string n);
	int MNcheck(int i, string n);
	void addCandidate();
	void showCand();
	void vote(int index);
	void showMPA();
};
#endif