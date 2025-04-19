#pragma once
#ifndef general_H
#define general_H
#include<iostream>
#include<string>
#include"election.h"
using namespace std;
class general_election :public election
{
	string level;
	string province;
	string contituency_code;
	string position;
	string seat_type;
public:
	general_election(string l, string p);
	void set_level(string l);
	void set_province(string p);
	string get_level();
	string get_province();
	string getposition();
};

#endif