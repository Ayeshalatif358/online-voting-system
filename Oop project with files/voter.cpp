#include<iostream>
#include<string>
#include"voter.h"
#include<fstream>
#include<windows.h>
using namespace std;
voter::voter(int a)
{
    
    id = 0;
    age = a;
    Phasvoted = 0;
    Nhasvoted = 0;
}

//void voter::loadLastVoterId() {
//    ifstream in("voter_id.txt");
//    if (in) {
//        in >> id;
//    }
//    in.close();
//}
//void voter::loadLastVoterId() {
//    ofstream out("voter_id.txt");
//    out << id;
//    out.close();
//}
void voter::setcode(string n) {
    cons.setcode(n);
}

void voter::setNcode(string n) {
    cons.setNcode(n);
}
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
    v.cons.setcode("null");
    v.cons.setNcode("null");
    return in;
}
bool voter::signupToPendingFile() {
    ifstream read;
    read.open("Voter ID.txt");
    if (!read.is_open()) {
        cout << "Error opening file\n"; return 0;
    }
    read >> id;
    read.close();

    cin >> *this;
    read.open("Voters.txt");
    if (!read.is_open()) {
        cout << "Error opening Voters file\n"; return 0;

    }
    else {

        string vid, vname, vnic, vage, pass, pv, nv, code1, code2;
        while (getline(read, vid)) {
            getline(read, vname);
            getline(read, vnic);
            getline(read, pass);
            getline(read, vage);
            read >> code1;
            read >> code2;
            read >> pv;
            read >> nv;
            if (cnic == vnic) {
                system("cls");
                Sleep(500);
                cout << "Voter With This NIC " << vnic << " Already Present! \n";

                read.close();
                return 0;
            }
        }

    }

    ofstream fout("Voters.txt", ios::app);
    if (!fout) {
        cout << "Error: Cannot open to write pending voter in file.\n";
        return 0;
    }
    if (age >= 18) {
        fout << id++ << '\n' << name << '\n' << cnic << '\n' << password << '\n'
            << age << '\n'
            << cons.getcode() << '\n' << cons.getNcode() << '\n'  // code fields should come here
            << 0 << '\n' << 0 << '\n';
        fout.close();
        fout.open("Voter ID.txt");
        if (!fout) {
            cout << "Error: Cannot open voter id file.\n";
            return 0;
        }
        fout << id << endl;
        return 1;
    }
    else {
        system("cls");
        Sleep(500);
        cout << "Not elligible to vote.\nAge less than 18\n";
        return 0;
    }

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