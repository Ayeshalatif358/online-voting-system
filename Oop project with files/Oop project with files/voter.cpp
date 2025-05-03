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
    age = a;
hasvoted=0;
}
void voter::Register() {

    fstream outFile;
    outFile.open("voter.txt", ios::app);
    string line;
    if (!(outFile.is_open())) {
        cout << "Error! opening the file.." << endl;
    }
    else {        
        cout << "Enter Name: ";
        getline(cin >> ws, name); // ws to skip leading whitespace        
        cout << "Enter Password: ";
        getline(cin, password);    
        cout << "Enter CNIC: ";
        getline(cin, cnic);
        

        outFile << name;
        outFile << password;
        outFile << cnic;
        outFile << "-----------" << endl;
        cout << "Registration successful!" << endl;
    }
    outFile.close();
    
}
bool voter::login() {
    ifstream inFile;
    inFile.open("voter.txt");

      
        voter d;
        d.inputUserData(); 
        inFile>>name;
        inFile>>cnic;
        inFile>>password;
        if(name==d.name&&cnic==d.cnic&&password==d.password)
        return 1;
    else
    return 0;
}

string voter::getcnic() { return cnic; }
void voter::setage(int a) { age = a; }
void voter::sethasvoted() { hasvoted = 1; }
int voter::getage() { return age; }
int voter::getid() { return id; }
bool voter::gethasvoted() { return hasvoted; }
istream& operator>>(istream& in, voter& v) {
    cout << "Enter age: ";
    in >> v.age;

    v.hasvoted = false; // Set default

    return in;
}
ostream& operator<<(ostream& out, const voter& v) {
    out << "Voter ID: " << v.id << endl;
    out << "Age: " << v.age << endl;
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