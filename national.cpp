#include<iostream>
#include<string>
#include<fstream>
#include"national.h"
using namespace std;

national_election::national_election() {
    partyseats = nullptr;
    pm = "Not selected";
}

// For candidate file reading
bool isIntCandidate(const std::string& s) {
    if (s.empty()) return false;
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] < '0' || s[i] > '9') {
            return false;
        }
    }
    return true;
}
bool national_election::loginMNA(string c) {
    ifstream read;
    read.open("Winner MNA.txt");
    if (!read.is_open()) {
        cout << "Error opening file!!\n";
        return false;
    }
    int i = 0;
    string temp;
    while (getline(read, temp)) {
        i++;
    }

    read.clear();
    read.seekg(0, ios::beg);
    string* arr = new string[i];
    for (int j = 0; j < i; j++) {
        getline(read, arr[j]);
    }

    read.close();

    for (int k = 0; k < candidate_no; k++) {
        for (int m = 0; m < i; m++) {
            if (arr[m] == C[k]->getcons().getcode()) {
                if (C[k]->getcnic() == c) {
                    // if not work delete this cond 
                    return true;
                }

            }
        }
    }
    delete[] arr;
    return false;
}
int national_election::getPartySeats(int index) {
    return partyseats[index];
}

string national_election::getPrimeMinister() {
    return pm;
}

void national_election::readparty() {
    ifstream read("Leader DATA.txt");
    if (!read.is_open()) {
        cout << "Error opening file: " << "Leader DATA.txt " << "\n";
        return;
    }

    if (C != nullptr) {
        for (int i = 0; i < candidate_no; i++) {
            delete C[i];
        }
        delete[] C;
        C = nullptr;
    }

    candidate_no = 0;
    string line;
    while (getline(read, line)) {
        if (line == "###") {
            candidate_no++;
        }
    }

    if (candidate_no == 0) {
        cout << "---------No candidates found in file.---------\n";
        cout << candidate_no;
        return;
    }
    C = new candidate * [candidate_no];
    for (int i = 0; i < candidate_no; i++) {
        C[i] = new candidate();
    }
    read.clear();
    read.seekg(0, ios::beg);

    int index = 0;
    int fieldCount = 0;

    while (getline(read, line)) {
        if (index >= candidate_no) break;

        switch (fieldCount) {
        case 0:
            if (isIntCandidate(line))
                C[index]->setc_id(stoi(line));
            else {
                cout << "Invalid candidate ID at candidate #" << index + 1 << ": " << line << endl;
                return;
            }
            break;
        case 1:
            C[index]->setName(line);
            break;
        case 2:
            C[index]->setParty(line);
            break;
        case 3:
            if (isIntCandidate(line))
                C[index]->setnoOfvotes(stoi(line));
            else {
                cout << "Invalid no of votes for candidate #" << index + 1 << ": " << line << endl;
                return;
            }
            break;
        }
        fieldCount++;
        if (fieldCount == 4) {
            if (!getline(read, line) || line != "###") {
                cout << "Error: Missing or invalid separator after candidate #" << index + 1 << endl;
                return;
            }
            fieldCount = 0;
            index++;
        }
    }
    read.close();
    cout << "---------Successfully loaded " << candidate_no << " candidate(s).---------\n";
}

void national_election::regCandidate(string filename, string id, string pos) {
    int size = candidate_no + 1;
    candidate** cand = new candidate * [size];
    for (int i = 0; i < candidate_no; i++) {
        cand[i] = C[i];
    }

    cand[size - 1] = new candidate();
    cand[size - 1]->set_leaders();
    delete[] C;

    C = cand;
    candidate_no = size;
}

bool national_election::cast_Voteforpm() {
    int j;
    if (C == nullptr) { readparty(); }
    partyseats = new int[candidate_no];
    cout << "Enter Leader ID: ";
    cin >> j;
    for (int i = 0; i < candidate_no; i++) {
        if (C[i]->getc_id() == j) {
            C[i]->addVote();
            partyseats[j - 1] += 1;
            cout << "Leader has voted successfully!!\n";
            return 1;
        }
    }
    cout << "No such party exist!!\n";
    return 0;
}
void national_election::select_cand() {
    if (C == nullptr) {
        readparty();
    }
    int max = 0;
    for (int i = 0; i < candidate_no; i++) {
        for (int j = 0; j < candidate_no; j++) {
            if (partyseats[i] > partyseats[i]) {
                max = i;
            }
        }
    }
    pm = C[max]->getName();
    C[max]->inputPartyinfo("PM DATA.txt");
}

// For voter file reading
bool isIntVoter(const std::string& s) {
    if (s.empty()) return false;
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] < '0' || s[i] > '9') {
            return false;
        }
    }
    return true;
}
// to read mna(voters) from file
void national_election::addVoter() {
    ifstream read;
    read.open("N_VOTER DATA.txt");
    string line;
    voter_no = 0;
    while (getline(read, line)) {
        if (line == "###") {
            voter_no++;
        }
    }
    V = new voter * [voter_no];
    for (int i = 0; i < voter_no; i++) {
        V[i] = new voter();
    }
    read.clear();
    read.seekg(0, ios::beg);
    int index = 0;
    int fieldCount = 0;
    while (getline(read, line)) {
        if (index >= voter_no) break;

        switch (fieldCount) {
        case 0:
            if (isIntVoter(line)) {
                V[index]->setid(stoi(line));
            }
            else {
                cout << "Invalid voter ID at voter #" << index + 1 << ": " << line << endl;
                return;
            }
            break;
        case 1:
            V[index]->setcode(line);
            break;
        case 2:
            V[index]->setNcode(line);
            break;
        case 3:
            V[index]->setname(line);
            break;
        case 4:
            if (isIntVoter(line)) {
                V[index]->setNhasvoted(stoi(line));
            }
            else {
                cout << "Invalid voted status of voter #" << index + 1 << ": " << line << endl;
                return;
            }
            break;
        }
        fieldCount++;
        if (fieldCount == 10) {
            if (!getline(read, line) || line != "###") {
                cout << "Error: Missing or invalid separator after voter #" << index + 1 << endl;
                return;
            }
            fieldCount = 0;
            index++;
        }
    }
    read.close();
    cout << "---------Successfully loaded " << voter_no << " candidate(s).---------\n";
}

// For MNA file reading
bool isIntMNA(const std::string& s) {
    if (s.empty()) return false;
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] < '0' || s[i] > '9') {
            return false;
        }
    }
    return true;
}
// select voter
void national_election::selectVoter() {

    ifstream read;
    read.open("N_Voter DATA.txt");
    if (!read.is_open()) {
        cout << "Error opening file: MNA DATA.txt " << "\n";
        return;
    }
    string line;
    int a = 0;
    while (getline(read, line)) {
        a++;
    }
    if (a != 0) {
        if (V == nullptr) {
            addVoter();
        }
        return;
    }
    candidate** c = nullptr;
    read.open("MNA DATA");
    if (!read.is_open()) {
        cout << "Error opening file: MNA DATA.txt " << "\n";
        return;
    }
    int no = 0;
    if (c != nullptr) {
        for (int i = 0; i < no; i++) {
            delete c[i];
        }
        delete[] c;
        c = nullptr;
    }
    while (getline(read, line)) {
        if (line == "###") {
            no++;
        }
    }

    if (no == 0) {
        cout << "---------No candidates found in file.---------\n";
        return;
    }
    c = new candidate * [no];
    for (int i = 0; i < no; i++) {
        c[i] = new candidate();
    }
    read.clear();
    read.seekg(0, ios::beg);

    int index = 0;
    int fieldCount = 0;

    while (getline(read, line)) {
        if (index >= no) break;

        switch (fieldCount) {
        case 0:
            c[index]->setPosition(line);
            break;
        case 1:
            c[index]->setcode(line);
            break;
        case 2:
            c[index]->setNcode(line);
            break;
        case 3:
            c[index]->setName(line);
            break;
        case 4:
            c[index]->setParty(line);
            break;
        case 5:
            if (isIntMNA(line))
                c[index]->setc_id(stoi(line));
            else {
                cout << "Invalid candidate ID at candidate #" << index + 1 << ": " << line << endl;
                return;
            }
            break;
        case 6:
            c[index]->setArea(line);
            break;
        case 7:
            c[index]->setBio(line);
            break;
        case 8:
            c[index]->setcnic(line);
            break;
        case 9:
            if (isIntMNA(line)) {
                c[index]->setnoOfvotes(stoi(line));
            }
            else {
                cout << "Invalid vote count at candidate #" << index + 1 << ": " << line << endl;
                return;
            }
            break;
        }
        fieldCount++;
        if (fieldCount == 10) {
            if (!getline(read, line) || line != "###") {
                cout << "Error: Missing or invalid separator after candidate #" << index + 1 << endl;
                return;
            }
            fieldCount = 0;
            index++;
        }
    }

    read.close();
    cout << "---------Successfully loaded " << no << " candidate(s).---------\n";
    read.open("Winner MNA");
    if (!read.is_open()) {
        cout << "Error opening file!!\n";
        return;
    }
    int i = 0;
    string temp;
    while (getline(read, temp)) {
        i++;
    }

    read.clear();
    read.seekg(0, ios::beg);
    string* arr = new string[i];
    for (int j = 0; j < i; j++) {
        getline(read, arr[j]);
    }

    read.close();
    ofstream in;
    index = 0;
    in.open("N_VOTER DATA.txt");
    if (!in.is_open()) { cout << "Error opening file!!\n"; }
    for (int k = 0; k < no; k++) {
        for (int m = 0; m < i; m++) {
            if (arr[m] == c[k]->getcons().getNcode()) {
                V[index]->setname(c[m]->getName());
                V[index]->setcnic(c[m]->getcnic());
                V[index]->setVoterCode(c[m]->getcons());
                V[index]->setid(c[m]->getc_id());
                V[index]->setNhasvoted(0);
                in << V[index]->getid() << endl;
                in << V[index]->getcnic() << endl;
                in << V[index]->getname() << endl;
                in << V[index]->getVoterCode().getcode() << endl;
                in << V[index]->getVoterCode().getNcode() << endl;
                in << V[index]->getNhasvoted() << endl;
                in << "###" << endl;
            }
        }
    }
    delete[] arr;
    in.close();
}

national_election::~national_election() {}