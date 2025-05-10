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
    election** e; bool status;
    static int mna_count;
    int election_no;
public:
    admin();
    ~admin();
    friend ostream& operator<<(ostream& out, admin& a);
    friend istream& operator>>(istream& in, admin& a);
    string getcnic() override;
    bool login();
    int getelectionNo();
    election** getelection();
    void createElection();
    void loadElectionsFromFile();
};
#endif