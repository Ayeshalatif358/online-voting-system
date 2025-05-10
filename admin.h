#pragma once
#ifndef Admin_H
#define Admin_H
#include<iostream>
#include<string>
#include"election.h"
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
    string getcnic() override;
    bool login();
    int getelectionNo();
    election** getelection();
    void createElection();
    void loadElectionsFromFile();
};
#endif
