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
public:
	general_election();
	//void setcandidate();
	Code* getUniquecode();
	void select_mpa();
};
#endif
