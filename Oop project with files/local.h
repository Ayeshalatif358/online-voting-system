#pragma once
#ifndef local_H
#define local_H
#include<iostream>
#include<string>
#include"election.h"
#include"general.h"
#include"admin.h"
using namespace std;
class local_election :public election
{
	private:
	int mna_count;
public:
	Code* getUniquecode();
	int getmnaCount();
	int checkMNAexist(string n);
	void select_mna();
	int MNcheck(int i, string n);
	int MNcheckCons(int i,string c);
	void assignCodeToMNA();
	
};
#endif
