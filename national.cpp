#include<iostream>
#include<string>
#include<fstream>
#include"national.h"
national_election::national_election() {
    partyseats = nullptr;
    pm = "Not selected";
}
//void election::regCandidate(string filename, string id) {
//    int size;
//    size = candidate_no + 1;
//    C = new candidate * [size];
//    candidate** cand = new candidate * [size];
//    if (size > 1) {
//        for (int i = 0;i < size;i++)
//        {
//            cand[i] = C[i];
//        }
//    }
//    cand[size - 1] = new candidate();
//    /*cand[size - 1]->inputPM();*/
//    cand[size - 1]->inputPartyinfo(filename);
//    delete[]cand;
//    C = cand;
//    candidate_no = size;
//}
int national_election::getPartySeats(int index) {
    return partyseats[index];
}

string national_election::getPrimeMinister() {
    return pm;
}
void national_election::cast_vote(int ID)
{
    // regCandidate("Leader Data");//login leaders
}
void national_election::regvoter()
{
    string name, cons;
    cout << "Enter name: ";
    getline(cin, name);
    cout << "Enter Constituency code: ";
    getline(cin, cons);
    for (int i = 0; i < voter_no; i++) {
        if (V[i]->getname() == name && V[i]->getVoterCode().getcode() == cons) {
            cout << "Login successfully!!\n";
            break;
        }
    }
}
void national_election::cast_Vote(voter* v) {
    string p;
    if (v->getPhasvoted()) {
        cout << "You have already voted.\n";
        return;
    }
    int c = 0;
    while (c == 0) {
        cout << "Enter party name to vote: ";
        getline(cin, p);
        for (int i = 0; i < voter_no; i++) {
            if (C[i]->getParty() == p) {
                v->setNhasvoted(1);
                c = 1;
                int a = C[i]->getc_id();
                partyseats[a] += 1;
                break;
            }
        }
        cout << "No such party exist!!\nEnter party name again to vote";
    }
}

void national_election::getwinnerParty()
{
    int max = 0;
    for (int i = 0; i < candidate_no; i++) {
        for (int j = 0; j < candidate_no; j++) {
            if (partyseats[i] > partyseats[i]) {
                max = i;
            }
        }
    }
    pm = C[max]->getName();
}

void national_election::addVoter()
{
    ifstream read;
    read.open("Winner MNA");
    string line;
    voter_no = 1;
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
        int Cnic;
        V = new voter * [candidate_no];
        while (line != a) {
            getline(read, line);
            getline(read, line);
            V[j]->setVoterCode(Code(line, "0"));
            getline(read, line);
            getline(read, line);
            V[j]->setname(line);
            getline(read, line);
            getline(read, line);
            getline(read, line);
        }
    }
    partyseats = new int[candidate_no];
}
national_election::~national_election() {}