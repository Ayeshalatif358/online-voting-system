#pragma once
#ifndef national_H
#define national_H
#include<iostream>
#include<string>
#include"election.h"
using namespace std;
class national_election :public election {
protected:
    string country;
    int totalseats;
    string* partynames;
    int* partyseats;
    string* partyleaders;
    int partycount;
    string pm;
public:
    national_election();
    national_election(const string& c, int totalSeats, int partyCount);
    void setCountry(string& c);
    void setTotalSeats(int seats);
    string getCountry() const;
    int getTotalSeats() const;

    int getPartyCount() const;
    string getPartyName(int index);
    int getPartySeats(int index);

    string getPartyLeader(int index);

    string getPrimeMinister();
    void cast_vote(int ID);
    ~national_election();
};
#endif