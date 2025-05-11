#include<iostream>
#include<string>
#include"admin.h"
#include<fstream>
#include"candidate.h"
using namespace std;
candidate::candidate() {
    name = "";
    party = "";
    area = "";
    position = "";
    noOfvotes = 0;
    bio = "";
    c_id = 0;
    code = new Code();
}
void candidate::setc_id(int a) {
    c_id = a;
}
// Constructor with initialization list
candidate::candidate(string n, string p, string a, string pos, int n_votes, string b) {
    name = n;
    party = p;
    area = a;
    position = pos;
    c_id = 0;
    noOfvotes = n_votes;
    bio = b;
    code = new Code();
}

istream& operator>>(istream& in, candidate& c) {
    cout << "Enter Candidate Name: ";
    getline(in >> ws, c.name);

    cout << "Enter CNIC: ";
    getline(in, c.cnic);

    cout << "Enter Bio: ";
    getline(in, c.bio);

    c.noOfvotes = 0;

    return in;
}
void candidate::inputFile(string filename, string idFILE) {
    int last_id = 0;

    ifstream out(idFILE);
    if (out.is_open()) {
        out >> last_id;
        out.close();
    }
    else {
        cout << "Error opening file!!\n";
    }

    c_id = last_id + 1;

    ofstream write(filename, ios::app);
    if (!write.is_open()) {
        cout << "Error opening file!!\n";
    }
    write << position << endl;
    write << "null" << endl;
    write << "null" << endl;
    write << name << endl;
    write << party << endl;
    write << c_id << endl;
    write << area << endl;
    write << bio << endl;
    write << cnic << endl;
    write << noOfvotes << endl;
    write << "###" << endl;
    write.close();
    ofstream in(idFILE);
    if (in.is_open()) {
        in << c_id;
        in.close();
    }
    else {
        cout << "Error opening file!!\n";
    }
}
ostream& operator<<(ostream& out, const candidate& c) {
     out << "Candidate ID: " << c.c_id << endl;
    out << "Name: " << c.name << endl;
    out << "Party: " << c.party << endl;
    out << "Area: " << c.area << endl;
    out << "Position: " << c.position << endl;
    out << "Votes: " << c.noOfvotes << endl;
    out << "Bio: " << c.bio << endl;
    return out;
}

// Setters
void candidate::setName(string n) {
    name = n;
}

void candidate::setcode(string n) {
    if (code == nullptr) {
        code = new Code();
    }
    code->setcode(n);
}

void candidate::setNcode(string n) {
    if (code == nullptr) {
        code = new Code();
    }
    code->setNcode(n);
}

void candidate::setParty(string p) { party = p; }
void candidate::setArea(string a) { area = a; }
void candidate::setPosition(string p) { position = p; }
void candidate::setnoOfvotes(int n) { noOfvotes = n; }
void candidate::setBio(string b) { bio = b; }

// Getters
string candidate::getName() const { return name; }
int candidate::getc_id() const { return c_id; }
string candidate::getParty() const { return party; }
string candidate::getArea() const { return area; }
string candidate::getPosition() const { return position; }
int candidate::getnoOfvotes() const { return noOfvotes; }
string candidate::getBio() const { return bio; }
Code candidate::getcons() { return *code; }
void candidate::setcnic(string n) {
    cnic = n;
}
string candidate::getcnic()const { return cnic; }
void candidate::setcandidate(string n, string p, string a, string P, string b, int no) {
    party = p;
    name = n;
    area = a;
    position = P;
    noOfvotes = no;
    bio = b;
}
void candidate::addVote() {
    noOfvotes++;
}

void candidate::inputPartyinfo(string filename) {
    ofstream write(filename, ios::app);
    if (!write.is_open()) {
        cout << "Error opening file!!\n";
    }
    write << c_id << endl;
    write << name << endl;
    write << party << endl;
    write << noOfvotes << endl;
    write << "###" << endl;
}
void candidate::set_leaders()
{
    int last_id = 0;

    ifstream out("Leader ID.txt");
    if (out.is_open()) {
        out >> last_id;
        out.close();
    }
    else {
        cout << "Error opening file!!\n";
    }

    c_id = last_id + 1;
    cout << "Enter name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter party: ";
    getline(cin, party);
    ofstream in("Leader ID.txt");
    if (in.is_open()) {
        in << c_id;
        in.close();
    }
    inputPartyinfo("LEADER DATA");
}