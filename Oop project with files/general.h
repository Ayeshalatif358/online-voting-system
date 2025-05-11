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
    void select_cand();
    int checkcandexist(string n, string filename)override;
    void assignCode()override;
    int check(string n);
    void assignMpa(string n, int i)override;
    void castVote(voter* v) override;
    void showCandidates(string code) override;
    void viewVoteCountIfElectionEnded(const date& today) override;
};

#endif