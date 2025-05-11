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
    date startDate, endDate;
public:

    election(int c, int v, string t, string a, bool active);
    election();
    void selectVoter();
    virtual bool loginMNA(string c);
    virtual bool cast_Voteforpm();
    void set_title(string t);
    void outputCand();
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
    void set_id(int i);
    date get_startDate();
    date get_endDate();
    Code* selectedCand();
    //add candidate
    virtual void viewVoteCountIfElectionEnded(const date& today);
    void addCandidate(string filename);
    virtual void regCandidate(string filename, string id, string pos);
    virtual void showCand(string filename);

    int checkCity(string c, int k);
    void winnerCand(string filename);
    bool login(int id, string pass, string filename);
    bool listVotersWithoutCodes();
    void assignCodeToVoterById(int id);
    void adminAssignCodesFlow();
    void saveVotersToFile(string filename);
    virtual int checkcandexist(string n, string filename);
    bool loadVotersFromFile(const string& filename);
    void set_startDate(date d);
    virtual void showCandidates(string code);
    voter* login(const string& nic, const string& password);
    bool isactive(date d);
    bool checkParty(string filename, string area, string party);
    void deleteCandidateById(int targetId, string filename);
    string checkNcode(int i);
    void set_endDate(date d);
    virtual void assignCode();
    virtual void assignMpa(string n, int i);
    virtual void select_cand();
    int check(string n);
    virtual void castVote(voter* v);
    void inputalldata(string filename);
    virtual ~election();
};
#endif
