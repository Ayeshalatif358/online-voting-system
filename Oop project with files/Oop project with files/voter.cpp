#include<iostream>
#include<string>
#include"user.h"
#include"voter.h"
using namespace std;
int voter::id = 0;
voter::voter(bool s, int a)
{
    id = ++id;
    status = s;
    age = a;

}

int voter::getcnic() { return cnic; }

void voter::setstatus(bool s) { status = s; }
void voter::setage(int a) { age = a; }
void voter::sethasvoted(bool s) { hasvoted = s; }
bool voter::getstatus() { return status; }
int voter::getage() { return age; }
bool voter::gethasvoted() { return hasvoted; }
istream& operator>>(istream& in, voter& v) {
    cout << "Enter age: ";
    in >> v.age;

    char s;
    cout << "Is the voter active? (y/n): ";
    in >> s;
    v.status = (s == 'y' || s == 'Y');

    v.hasvoted = false; // Set default

    return in;
}
ostream& operator<<(ostream& out, const voter& v) {
    out << "Voter ID: " << v.id << endl;
    out << "Age: " << v.age << endl;
    out << "Status: " << (v.status ? "Active" : "Inactive") << endl;
    out << "Has Voted: " << (v.hasvoted ? "Yes" : "No") << endl;
    return out;
}