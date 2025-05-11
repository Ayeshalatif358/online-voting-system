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
    void select_cand()override;
    string getPrimeMinister();
    void addVoter();
    bool cast_Voteforpm()override;
    void selectVoter();
    void regCandidate(string filename, string id, string pos)override;
    void readparty();
    bool loginMNA(string c)override;
    ~national_election();
};

#endif
