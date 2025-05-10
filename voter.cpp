#include<iostream>
#include<string>
#include"voter.h"
#include<fstream>
using namespace std;
int voter::id = 0;
voter::voter(int a)
{
    id = ++id;
    age = a;
    Phasvoted = 0;
    Nhasvoted = 0;
}
void voter::loadLastVoterId() {
    ifstream in("voter_id.txt");
    if (in) {
        in >> id;
    }
    in.close();
}
//void voter::loadLastVoterId() {
//    ofstream out("voter_id.txt");
//    out << id;
//    out.close();
//}
string voter::getcnic() { return cnic; }
void voter::setage(int a) { age = a; }
void voter::setid(int a) { id = a; }
void voter::setNhasvoted(bool hv) { Phasvoted = hv; }
void voter::setPhasvoted(bool hv) { Nhasvoted = hv; }
int voter::getage() { return age; }
int voter::getid() { return id; }
bool voter::getPhasvoted() { return Phasvoted; }
bool voter::getNhasvoted() { return Nhasvoted; }
istream& operator>>(istream& in, voter& v) {
    v.inputUserData();
    cout << "Enter age: ";
    in >> v.age;
    v.Nhasvoted = false;
    v.Phasvoted = false; // Set default
    v.cons.setcode("");
    v.cons.setNcode("");
    return in;
}
void voter::signupToPendingFile() {
    ifstream read;
    read.open("Voter ID.txt");
    if (!read.is_open()) { cout << "Error opening file\n"; }
    read >> id;
    ofstream fout("pending_voters", ios::app);
    if (!fout) {
        cout << "Error: Cannot open pending voter file.\n";
        return;
    }
    cin >> *this;
    fout << id++ << '\n' << name << '\n' << cnic << '\n' << password << '\n'
        << age << '\n' << cons.getcode() << "\n" << cons.getNcode() << "\n" << 0 << "\n" << 0 << '\n';
    fout.close();
    fout.open("Voter ID.txt");
    if (!fout) {
        cout << "Error: Cannot open pending voter file.\n";
        return;
    }
    fout << id;
    read.close();
    fout.close();
}
ostream& operator<<(ostream& out, voter& v) {
    out << "Voter ID: " << v.id << endl;
    v.outputUserData();

    out << "Age: " << v.age << endl;
    out << "Has Voted: " << (v.Phasvoted ? "Yes" : "No") << endl;
    out << "Has Voted: " << (v.Nhasvoted ? "Yes" : "No") << endl;
    out << "Codes: \nMPA code: " << v.cons.getcode() << "\t MNA code: " << v.cons.getNcode();
    return out;
}
void voter::setVoterCode(Code c) { cons = c; }
Code voter::getVoterCode() const { return cons; }