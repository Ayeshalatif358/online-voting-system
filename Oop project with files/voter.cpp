#include<iostream>
#include<string>
#include"user.h"
#include"voter.h"
#include"candidate.h"
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
void voter::cast_vote(candidate* c[], int s)//cast vote to mna/mpa
{
    if(hasvoted)
    {
        cout << "You have already voted.\n";
        return;
    }
    cout << "Candidates List:\n";
    for (int i = 0; i < s; i++) {
        cout << i + 1 << ". ";
        cout << c[i];
    }
    int choice;
    cout << "Enter your choice: ";
    cin >> choice;
    if (choice >= 1 && choice <= s) {
        c[choice - 1]->addVote();
        hasvoted = true;
        cout << "Vote cast successfully.\n";
    }
    else {
        cout << "Invalid choice.\n";
    }
}

