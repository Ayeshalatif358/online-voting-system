#include<iostream>
#include<string>
#include"national.h"
#include"election.h"
using namespace std;
national_election::national_election() {
    country = "";
    totalseats = 0;
    partycount = 0;
    partynames = nullptr;
    partyseats = nullptr;
    partyleaders = nullptr;
    pm = "Not selected";
}

// Parametric constructor
national_election::national_election(const string& c, int totalSeats, int partyCount) {
    country = c;
    totalseats = totalSeats;
    partycount = partyCount;
    pm = "Not selected";

    partynames = new string[partycount];
    partyseats = new int[partycount];
    partyleaders = new string[partycount];

    // Optional: Initialize arrays
    for (int i = 0; i < partycount; ++i) {
        partynames[i] = "Party" + to_string(i + 1);
        partyseats[i] = 0;
        partyleaders[i] = "Leader" + to_string(i + 1);
    }
}

void national_election::setCountry(string& c) {
    country = c;
}

void national_election::setTotalSeats(int seats) {
    totalseats = seats;
}

string national_election::getCountry() const {
    return country;
}

int national_election::getTotalSeats() const {
    return totalseats;
}

int national_election::getPartyCount() const {
    return partycount;
}

string national_election::getPartyName(int index) {
    return partynames[index];
}

int national_election::getPartySeats(int index) {
    return partyseats[index];
}

string national_election::getPartyLeader(int index) {
    return partyleaders[index];
}

string national_election::getPrimeMinister() {
    return pm;
}
void national_election::cast_vote(int ID)
{
    for (int i = 0; i < candidate_no; i++)
    {
    }
}
national_election::~national_election() {}