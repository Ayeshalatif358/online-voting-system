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
    code = nullptr;
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
    code = nullptr; // initialize code to nullptr
}

istream& operator>>(istream& in, candidate& c) {
    cout << "Enter Candidate Name: ";
    getline(in >> ws, c.name);

    cout << "Enter Party: ";
    getline(in, c.party);

    cout << "Enter Area: ";
    getline(in, c.area);

    cout << "Enter Position: ";
    getline(in, c.position);

    cout << "Enter Bio: ";
    getline(in, c.bio);

    c.noOfvotes = 0;

    return in;
}
void candidate::inputFile(string filename, string idFILE) {
    ifstream out;
    ofstream in;
    out.open(idFILE);
    if (!out.is_open()) {
        cout << "Error opening file!!\n";
    }
    out >> c_id;
    c_id++;
    ofstream write(filename, ios::app);
    if (!write.is_open()) {
        cout << "Error opening file!!\n";
    }
    write << position << endl;
    write << endl << endl;
    write << name << endl;
    write << party << endl;
    write << c_id << endl;
    write << area << endl;
    write << bio << endl;
    write << "###" << endl;
    in.open(idFILE);
    if (!in.is_open()) {
        cout << "Error opening file!!\n";
    }
    write << c_id << endl;
    write.close();
    in << c_id;
    in.close();
    out.close();
}

void candidate::inputWholeData(string filename) {
    ofstream write("temp.txt"); // Overwrite, not append

    if (!write.is_open()) {
        cout << "Error opening temp file!!\n";
        return;
    }

    // Write candidate data
    write << position << endl;
    write << code->getcode() << endl;
    write << code->getNcode() << endl;
    write << name << endl;
    write << party << endl;
    write << c_id << endl;
    write << area << endl;
    write << bio << endl;
    write << "###" << endl;
    write.close();
    // Replace original file with the temp file
    if (remove(filename.c_str()) != 0) {
        cout << "Error deleting original file!\n";
        return;
    }
    if (rename("temp.txt", filename.c_str()) != 0) {
        cout << "Error renaming temp file!\n";
        return;
    }
}

void candidate::inputPartyinfo(string filename) {
    ofstream write(filename, ios::app);
    if (!write.is_open()) {
        cout << "Error opening file!!\n";
    }
    write << name << endl;
    write << party << endl;
    write << area << endl;
    write << bio << endl;
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