
#include<iostream>
#include<string>
#include "user.h"
#include "voter.h"
#include"admin.h"
#include "election.h"
#include "candidate.h"
using namespace std;

int admin::getcnic() { return cnic; }
istream& operator>>(istream& in, admin& a) {
    a.inputUserData();

    cout << "Enter number of elections managed: ";
    in >> a.election_no;
    a.e = new election * [a.election_no];  // Dynamically allocate election array
    for (int i = 0; i < a.election_no; ++i) {
        a.e[i] = nullptr; // Placeholder, actual assignments will be done later
    }
    return in;
}


ostream& operator<<(ostream& out, admin& a) {
    a.outputUserData();

    cout << "Admin manages " << a.election_no << " election(s)." << endl;
    return out;
}

