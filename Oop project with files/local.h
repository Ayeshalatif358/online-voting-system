#pragma once
#ifndef Local_H
#define Local_H
#include<iostream>
#include<string>
#include "election.h"
#include "code.h"
#include<fstream>
using namespace std;
class local_election :public election
{
private:
    int mna_count=0;
public:
    Code* getUniquecode();
    int getmnaCount();
    int checkcandexist(string n,string filename)override;
    void select_cand();
    int MNcheck(int i, string n);
    int MNcheckCons(int i, string c);
    void assignCode()override;
    void showCandidates(string code)override;
    void castVote(voter* v);

};
#endif