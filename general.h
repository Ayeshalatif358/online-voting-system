#pragma once
#ifndef General_H
#define General_H
#include<iostream>
#include<string>
#include "election.h"
#include<fstream>
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
    void assignMpa(string n, int i);
    void castVoteP(voter* v);
    void showCandidatesMPA(string code);
};

#endif