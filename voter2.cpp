#include<iostream>
#include<fstream>
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
    hasvoted = false;
}

string voter::getcnic() { return cnic; }
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

    v.hasvoted = false; 

    return in;
}
ostream& operator<<(ostream& out, const voter& v) {
    out << "Voter ID: " << v.id << endl;
    out << "Age: " << v.age << endl;
    out << "Status: " << (v.status ? "Active" : "Inactive") << endl;
    out << "Has Voted: " << (v.hasvoted ? "Yes" : "No") << endl;
    return out;
}

bool voter::login() {
    fstream inFile;
    inFile.open("voter.txt");
    string line;
    //entering login info
    //cout << "Enter Name: ";
    //getline(cin >> ws, name); // ws to ignore leading spaces
    //cout << "Enter Password: ";
    //getline(cin, password);
    //cout << "Enter CNIC: ";
    //cin >> cnic;

    user::inputUserData();

    bool found = false;

    if (!inFile.is_open()) {
        cout << "Error! Opening file..." << endl;
        return;
    }
    else {

        while (getline(inFile, line)) {
            if (line == password) {
                getline(inFile, line);
                if (line == cnic)
                    found = true;
                else
                    continue;
                break;
            }
        }
    }
    inFile.close();

    if (found) {
        cout << "Login successful!" << endl;
        return 1;
    }
    else {
        cout << "User not found!" << endl;
        return 0;
    }
}


void voter::Register() {

    fstream outFile;
    outFile.open("voter.txt", ios::app);
    string line;
    if (!(outFile.is_open())) {
        cout << "Error! opening the file.." << endl;
    }
    else {
        //cout << "Enter Name: ";
        //getline(cin >> ws, name); // ws to skip leading whitespace        
        //cout << "Enter Password: ";
        //getline(cin, password);
        //cout << "Enter CNIC: ";
        //getline(cin, cnic);

        user::inputUserData();

        outFile << name;
        outFile << password;
        outFile << cnic;
        outFile << "-----------" << endl;
        cout << "Registration successful!" << endl;
    }
    outFile.close();

}

void voter::showCandidates() {
    fstream read;
    read.open("candidates.txt");
    if (!read.is_open()) {
        cout << "Error opening file..!" << endl;
        return;
    }
    else {
        string line;
        while (getline(read, line))
        {
            cout << line << endl;
        }
    }
    read.close();
}

void voter::castVote() {
    if (hasvoted) {
        cout << "You have already casted your vote..!!!" << endl;
    }
    else {
        string tempName;
        showCandidates();
        cout << "Enter the name of the candidate you want to cast your vote for :" << endl;
        cin.ignore();
        getline(cin, tempName);
        
        //fstream write;
        fstream read_c;
        fstream read_v;
        fstream out_c;
        fstream out_v;
        //candidate c;

        //write.open("votes.txt");
        read_c.open("candidates.txt"); //for reading candidate names from file
        read_v.open("votes.txt");     //for reading votes against each candidate name
        out_c.open("temp_c.txt");    //for writing candidate names into a temp file
        out_v.open("temp_v.txt");   //for writing votes against each candidate name inro a temp file

        string name;
        int votescount;

        if (read_c.is_open() && read_v.is_open()) {
            if (out_c.is_open() && out_v.is_open()) {
                while (getline(read_c, name) && (read_v >> votescount)) {
                    if (name == tempName) {
                        //c.setName(name);
                        out_c << name << endl;
                        out_v << ++votescount << endl;
                        hasvoted = true;
                        /*tempOut << line << endl;
                        getline(read, line);
                        tempOut << (int)line << endl;*/
                        //noOfvotes++;
                    }
                    else {
                        out_c << name << endl;  
                        out_v << votescount << endl;
                    }
                }
            }
        }
        else { cout << "Error Opening Files!"; }

        remove("candidates.txt");  //renaming temp files
        rename("temp_c.txt", "candidates.txt");
        remove("votes.txt");
        rename("temp_v.txt", "votes.txt");
    }

}



