#pragma once
#ifndef general_H
#define general_H
#include<iostream>
#include<string>
#include"election.h"
#include"constituency.h"
using namespace std;
class general_election :public election
{
	private:
	int mpa_count;
public:
	general_election();
	//void setcandidate();
	Code* getUniquecode();
	void select_mpa();
	string nationalCode();
	void assignCodeToMPA();
	int check(string n);
	void assignMpa(string n,int i);
	
};
#endif
