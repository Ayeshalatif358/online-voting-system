#include<iostream>
#include<string>
#include"election.h"
#include"candidate.h"
#include"voter.h"
#include<fstream>
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
    winCode = nullptr;
    
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

Code* election::selectedCand() { return winCode; }

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

void election::addCandidate(string filename) {
    ifstream read;
    read.open(filename);
    string line;
    candidate_no = 1;
    line = " ";
    string a = "###";
    while (!read.eof()) {
        getline(read, line);
        if (line == a)
        {
            candidate_no++;
        }
    }
    int k = 0;
    while (!read.eof())
    {
        int j = k++;
        candidate** c;
        int Cnic;
        c = new candidate * [candidate_no];
        while (line != a) {
            getline(read, line);
            c[j]->setcode(line);
            getline(read, line);
            c[j]->setNcode(line);
            getline(read, line);
            c[j]->setName(line);
            getline(read, line);
            c[j]->setParty(line);
            getline(read, line);
            c[j]->setArea(line);
            getline(read, line);
            c[j]->setPosition(line);
            getline(read, line);
            c[j]->setBio(line);
        }

    }
}
void election::winnerCand(string filename)
{
    string* arr;
    ifstream read;
    read.open(filename);
    if(!read.is_open()){
        cout<<"Error opening file!!\n";
    }
    int i=0;
    while(!read.eof()){
        i++;
    }
    arr=new string[i];
    for(int j=0;j<i;j++){
        getline(read,arr[i]);
    }
    for(int k=0;k<candidate_no;k++){
        if(arr[i]==C[i]->getcons().getcode()){
            cout<<*C[i];
        }
    }
}
int election::checkCity(string c, int k)
{
    for (int i = 0;i < candidate_no;i++) {
        if (C[i]->getArea() == C[k]->getArea()) {
            if (C[i]->getcons().getcode() == c) {
                return 1;
            }
            else return -1;
        }
        else return 2;
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
void election::regCandidate(string filename){
    int size;
	size = candidate_no + 1;
	C = new candidate * [size];
	candidate** cand = new candidate * [size];
    if(size>1){
        for (int i = 0;i < size;i++)
	{
		cand[i] = C[i];
	}
    }
	cand[size - 1] = new candidate();
	cin >> *cand[size - 1];
    cand[size - 1]->inputFile(filename);
	delete[]cand;
	C = cand;
	candidate_no = size;
}



