#pragma once
#ifndef National_H
#define National_H
#include<iostream>
#include<string>
#include "election.h"
#include<fstream>
using namespace std;
class national_election :public election {
protected:
    int* partyseats;
    string pm;
public:
    national_election();
    int getPartySeats(int index);
    void getwinnerParty();
    string getPrimeMinister();
    void cast_vote(int ID);
    void addVoter();
    void regvoter();
    void cast_Vote(voter* v);
    ~national_election();
};

#endif