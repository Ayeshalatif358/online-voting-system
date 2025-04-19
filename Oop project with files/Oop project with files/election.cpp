#include<iostream>
#include<string>
#include"election.h"
#include"candidate.h"
#include"voter.h"
using namespace std;
int election::id = 0;
election::election(int c = 0, int v = 0, string t = " ", string a = " ", bool active = 0, string S_D = "0", string E_D = "0")
{
    id = ++id;
    candidate_no = c;
    title = t;
    area = a;
    voter_no = v;
    isActive = active;
    startDate = S_D;
    endDate = E_D;
}
election::election() {

    id = ++id;
    candidate_count = 0;
    candidate_no = 0;
    title = "";
    voter_no = 0;
    area = "";
    isActive = 0;
    startDate = "";
    endDate = "";
}

void election::set_title(string t) { title = t; }
void election::set_area(string a) { area = a; }
void election::set_startDate(string S_D) { startDate = S_D; }
void election::set_endDate(string E_D) { endDate = E_D; }
//Getters
int election::get_id() { return id; }
int election::get_candidate_no() { return candidate_no; }
int election::get_voter_no() { return voter_no; }
string election::get_title() { return title; }
candidate** election::get_candidate() { return C; }
voter** election::get_voter() { return V; }
string election::get_area() { return area; }
string election::get_startDate() { return startDate; }
string election::get_endDate() { return endDate; }

istream& operator>>(istream& in, election& e) {
    cout << "Enter Election Title: ";
    getline(in >> ws, e.title);

    cout << "Enter Area: ";
    getline(in, e.area);

    cout << "Enter Start Date (DD-MM-YYYY): ";
    getline(in, e.startDate);

    cout << "Enter End Date (DD-MM-YYYY): ";
    getline(in, e.endDate);

    char status;
    cout << "Is the election active? (y/n): ";
    in >> status;
    e.isActive = (status == 'y' || status == 'Y');

    cout << "Enter number of candidates: ";
    in >> e.candidate_no;
    e.C = new candidate * [e.candidate_no];
    for (int i = 0; i < e.candidate_no; ++i) {
        e.C[i] = new candidate;
    }
    for (int i = 0; i < e.candidate_no; ++i) {
        e.C[i] = nullptr; // placeholder: actual object should be passed by admin
    }

    cout << "Enter number of voters to link: ";
    in >> e.voter_no;
    e.V = new voter * [e.voter_no];
    for (int i = 0; i < e.voter_no; ++i) {
        e.V[i] = nullptr; // same, to be assigned externally
    }

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
    for (int i = 0; i < candidate_no; i++)
    {
        C[i] = new candidate();
        cout << "Enter details for candidate " << i + 1 << ": ";
        cin >> *C[i];
    }
}
void election::vote(int index) {
    if (index >= 1 && index <= candidate_count) {
        C[index - 1]->addVote();
    }
    else {
        cout << "Invalid choice.\n";
        }
}

//candidate* election :: getMNA(){}
void election:: create_election()
{
}