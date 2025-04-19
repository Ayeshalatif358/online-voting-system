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
    int election_no;
public:


    friend ostream& operator<<(ostream& out, admin& a);

    friend istream& operator>>(istream& in, admin& a);
    int getcnic() override;
};
#endif