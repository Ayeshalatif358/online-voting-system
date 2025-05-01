#pragma once
#ifndef admin_H
#define admin_H
#include<iostream>
#include<string>
#include "election.h"
#include "candidate.h"

#include "voter.h"
#include "user.h"
using namespace std;
class admin : public user {
    election** e;
    static int mna_count;
    int election_no;
public:
    admin();
    ~admin();
    friend ostream& operator<<(ostream& out, admin& a);
    friend istream& operator>>(istream& in, admin& a);
    int getcnic() override;
    void addCandidateMNA();
    void addCandidateMPA();
    void assignMpa();
    bool login();
    int check(candidate** ca,string m);
    void createElection();
    void CMelection();
    void PMelection();
};
#endif