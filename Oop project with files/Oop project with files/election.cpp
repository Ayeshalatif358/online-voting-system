#include<iostream>
#include<string>
#include"election.h"
#include"candidate.h"
#include"voter.h"
using namespace std;

int election::id = 0;

election::election(int c, int v, string t, string a, bool active)
{
    if (id == 0) {  // Only increment id the first time
        id = 1;
    }
    else {
        id = ++id;
    }

    candidate_no = c;
    title = t;
    area = a;
    voter_no = v;
    isActive = active;
    C = nullptr;
    V = nullptr;
    pCode = nullptr;
    mCode = nullptr;
    candidate_count = 0;
}

election::election()
{
    if (id == 0) {  // Only increment id the first time
        id = 1;
    }
    else {
        id = ++id;
    }

    candidate_count = 0;
    candidate_no = 0;
    title = "";
    voter_no = 0;
    area = "";
    isActive = 0;
}

void election::set_title(string t) { title = t; }
void election::set_area(string a) { area = a; }
void election::set_startDate() { cin >> startDate; }
void election::set_endDate() { cin >> endDate; }

// Getters
int election::get_id() { return id; }
int election::get_candidate_no() { return candidate_no; }
int election::get_voter_no() { return voter_no; }
string election::get_title() { return title; }
candidate** election::get_candidate() { return C; }
voter** election::get_voter() { return V; }
string election::get_area() { return area; }
date election::get_startDate() { return startDate; }
date election::get_endDate() { return endDate; }

Code* election::selectedMna() { return mCode; }
Code* election::selectedMpa() { return pCode; }

istream& operator>>(istream& in, election& e) {
    cout << "Enter Election Title: ";
    getline(in, e.title);

    cout << "Enter Area: ";
    getline(in, e.area);

    cout << "Enter Start Date (DD-MM-YYYY): ";
    in >> e.startDate;

    cout << "Enter End Date (DD-MM-YYYY): ";
    in >> e.endDate;

    in.ignore(); // ✅ important: ignore leftover newline

    char status;
    cout << "Is the election active? (y/n): ";
    in >> status;
    e.isActive = (status == 'y' || status == 'Y');

    return in;
}

ostream& operator<<(ostream& out, const election& e) {
    out << "Election ID: " << election::id << endl;
    out << "Title: " << e.title << endl;
    out << "Area: " << e.area << endl;
    out << "Start Date: " << e.startDate << endl;
    out << "End Date: " << e.endDate << endl;
    out << "Is Active: " << (e.isActive ? "Yes" : "No") << endl;
    out << "Number of Candidates: " << e.candidate_no << endl;

    for (int i = 0; i < e.candidate_no; ++i) {
        if (e.C[i] != nullptr)
            out << "\nCandidate " << (i + 1) << ":\n" << *e.C[i];
    }

    out << "Number of Voters: " << e.voter_no << endl;

    for (int i = 0; i < e.voter_no; i++) {
        if (e.V[i] != nullptr)
            out << "\nVoter " << (i + 1) << ":\n" << *e.V[i];
    }

    return out;
}

void election::addCandidate()
{
    int size = candidate_no + 1;
    candidate** newCand = new candidate * [size];

    // Copy old candidates
    for (int i = 0; i < candidate_no; i++) {
        newCand[i] = C[i];
    }

    // Add new candidate
    newCand[size - 1] = new candidate();
    cin >> *newCand[size - 1];

    // Clean up old candidate array
    delete[] C;

    // Update candidate pointer and count
    C = newCand;
    candidate_no = size;
}

void election::showCand()
{
    for (int i = 0; i < candidate_no; i++)
    {
        if (C[i] != nullptr) {
            cout << *C[i];
        }
    }
}

int election::MNcheck(int i, string n)
{
    int k = 0;
    for (int j = 0; j < i; j++)
    {
        if (C[j]->getcons().getNcode() == n) {
            k++;
            if (k > 1) {
                return -1;
            }
        }
    }
    return -3;
}

int election::check(int i, string n)
{
    int k = 0;
    string temp;
    for (int j = 0; j < i; j++)
    {
        if (C[j]->getcons().getNcode() == n) {
            k++;
            if (k > 2) {
                return -1;
            }
            else if (k < 2) {
                return -2;
            }
        }
    }
    return -3;
}

void election::vote(int index) {
    if (index >= 1 && index <= candidate_count) {
        C[index - 1]->addVote();
    }
    else {
        cout << "Invalid choice.\n";
    }
}

void election::showMPA()
{
    for (int i = 0; i < candidate_no; i++)
    {
        if (C[i]->getcons() == pCode[i])
        {
            cout << C[i];
        }
    }
}

int election::getmnaCount()
{
    return mna_count;
}
