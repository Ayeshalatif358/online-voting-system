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
public:
	//void setcandidate();
	void setn_Code();
	Code* getUniquecode();
	void select_mna();
};
#endif
