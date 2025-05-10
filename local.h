#pragma once
#ifndef Local_H
#define Local_H
#include<iostream>
#include<string>
#include "election.h"
#include "code.h"
#include<fstream>
using namespace std;
class local_election :public election
{
private:
    int mna_count;
public:
    Code* getUniquecode();
    int getmnaCount();
    int checkMNAexist(string n);
    void select_mna();
    int MNcheck(int i, string n);
    int MNcheckCons(int i, string c);
    void assignCodeToMNA();

};
#endif