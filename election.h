#pragma once
#ifndef Election_H
#define Election_H
#include<iostream>
#include<string>
#include "date.h"
#include "candidate.h"
#include "voter.h"
using namespace std;
class election {
protected:
    int id;
    int candidate_no;
    Code* winCode;
    string title;
    candidate** C;
    int voter_no;
    voter** V;
    string area;
    bool isActive;
    date startDate, endDate;
public:

    election(int c, int v, string t, string a, bool active);
    election();
    void set_title(string t);
    void set_area(string a);
    void set_startDate();
    void set_endDate();
    //input output -> operatoe overloading
    friend istream& operator>>(istream& in, election& e);
    friend ostream& operator<<(ostream& out, const election& e);
    //Getters
    int get_id();
    int get_candidate_no();
    string get_title();
    int get_voter_no();
    candidate** get_candidate();
    voter** get_voter();
    string get_area();
    date get_startDate();
    date get_endDate();
    Code* selectedCand();
    //add candidate
    void addCandidate(string filename);
    virtual void regCandidate(string filename, string id);
    virtual void showCand();
    int checkCity(string c, int k);
    void winnerCand(string filename);


    void listVotersWithoutCodes();
    void assignCodeToVoterById(int id);
    void adminAssignCodesFlow();
    void saveVotersToFile(string filename);
    void loadVotersFromFile(const string& filename);
    void set_startDate(date d);
    voter* login(const string& nic, const string& password);
    bool isactive();
    bool get_isActive();
    void set_endDate(date d);
    virtual void castVoteP(voter* v);
    void set_isActive(bool b);
    virtual ~election();
};
#endif