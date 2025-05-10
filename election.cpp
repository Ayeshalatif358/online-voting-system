#include<iostream>
#include<string>
#include"admin.h"
#include<fstream>
#include"election.h"
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
}

election::election()
{
    if (id == 0) {  // Only increment id the first time
        id = 1;
    }
    else {
        id = ++id;
    }
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
        C = new candidate * [candidate_no];
        while (line != a) {
            getline(read, line);
            C[j]->setcode(line);
            getline(read, line);
            C[j]->setNcode(line);
            getline(read, line);
            C[j]->setName(line);
            getline(read, line);
            C[j]->setParty(line);
            getline(read, line);
            C[j]->setArea(line);
            getline(read, line);
            C[j]->setPosition(line);
            getline(read, line);
            C[j]->setBio(line);
        }
    }
}
void election::showCand()
{
    for (int i = 0; i < candidate_no; i++)
    {
        if (C[i]->getcons() == winCode[i])
        {
            cout << C[i];
        }
    }
}
void election::winnerCand(string filename)
{
    addCandidate(filename);
    string* arr;
    ifstream read;
    read.open(filename);
    if (!read.is_open()) {
        cout << "Error opening file!!\n";
    }
    int i = 0;
    while (!read.eof()) {
        i++;
    }
    arr = new string[i];
    for (int j = 0; j < i; j++) {
        getline(read, arr[i]);
    }
    for (int k = 0; k < candidate_no; k++) {
        if (arr[i] == C[i]->getcons().getcode()) {
            cout << *C[i];
        }
    }
}

int election::checkCity(string c, int k)
{
    for (int i = 0; i < candidate_no; i++) {
        if (C[i]->getArea() == C[k]->getArea()) {
            if (C[i]->getcons().getcode() == c) {
                return 1;
            }
            else return -1;
        } 
    }
    return 2;
}

void election::regCandidate(string filename, string id) {
    int size;
    size = candidate_no + 1;
    C = new candidate * [size];
    candidate** cand = new candidate * [size];
    if (size > 1) {
        for (int i = 0; i < size; i++)
        {
            cand[i] = C[i];
        }
    }
    cand[size - 1] = new candidate();
    cin >> *cand[size - 1];
    cand[size - 1]->inputFile(filename, id);
    delete[]cand;
    C = cand;
    candidate_no = size;
}



bool election::isactive() {
    date d;
    cout << "Enter Start Date (DD-MM-YYYY): ";
    cin >> d;
    if (d >= startDate || d <= endDate && isActive)return 1;
    else
        return false;

}
void election::castVoteP(voter* v) {}
voter* election::login(const string& nic, const string& password) {
    for (int i = 0; i < voter_no; ++i) {
        if (V[i]->getcnic() == nic && V[i]->getpass() == password) {
            return V[i]; // return existing object from memory
        }
    }
    return nullptr;
}void election::listVotersWithoutCodes() {
    ifstream read("pending_voters", ios::app);
    cout << "Voters without assigned codes:\n";

    for (int i = 0; i < voter_no; ++i) {
        if (V[i]->getVoterCode().getcode() == "" || V[i]->getVoterCode().getNcode() == "") {
            cout << "ID: " << V[i]->getid()
                << ", Name: " << V[i]->getname()
                << ", CNIC: " << V[i]->getcnic() << endl;
        }
    }
}
void election::assignCodeToVoterById(int id) {
    for (int i = 0; i < voter_no; ++i) {
        if (V[i]->getid() == id) {
            string c_code, n_code;
            cout << "Enter constituency code (MPA): ";
            cin >> c_code;
            cout << "Enter national code (MNA): ";
            cin >> n_code;

            Code code;
            code.setcode(c_code);
            code.setNcode(n_code);
            V[i]->setVoterCode(code);

            cout << "Codes assigned to voter successfully.\n";

            return;
        }
    }
    cout << "Voter with ID " << id << " not found.\n";
}
void election::adminAssignCodesFlow() {
    listVotersWithoutCodes();

    int id;
    cout << "\nEnter Voter ID to assign codes: ";
    cin >> id;

    assignCodeToVoterById(id);
}

void election::saveVotersToFile(string filename) {
    ofstream fout(filename);
    if (!fout) {
        cout << "Unable to open file for writing in " << filename << endl;
        return;
    }

    for (int i = 0; i < voter_no; ++i) {
        fout << V[i]->getid() << "\n" << V[i]->getname() << "\n"
            << V[i]->getcnic() << "\n"
            << V[i]->getpass() << "\n"
            << V[i]->getage() << "\n"
            << V[i]->getVoterCode().getcode() << "\n"
            << V[i]->getVoterCode().getNcode() << "\n"
            << (V[i]->getNhasvoted() ? "1" : "0") << "\n"
            << (V[i]->getPhasvoted() ? "1" : "0") << "\n"
            ;
    }

    fout.close();
}
void election::loadVotersFromFile(const string& filename) {
    ifstream read(filename);
    if (!read) {
        cout << "Unable to open file: " << filename << endl;
        return;
    }

    // Count total lines to determine voter count
    int line_count = 0;
    string line;
    while (getline(read, line)) {
        if (!line.empty()) line_count++;
    }

    voter_no = line_count / 9; // Each voter has 9 lines

    read.clear();
    read.seekg(0, ios::beg);

    V = new voter * [voter_no];
    int index = 0;

    while (index < voter_no) {
        string id_str, name, cnic, pass, age_str, Pvoted_str, Nvoted_str, ccode, ncode;

        getline(read, id_str);
        getline(read, name);
        getline(read, cnic);
        getline(read, pass);
        getline(read, age_str);
        getline(read, Pvoted_str);
        getline(read, Nvoted_str);
        getline(read, ccode);
        getline(read, ncode);

        voter* v = new voter();
        v->setid(stoi(id_str));
        v->setname(name);
        v->setcnic(cnic);
        v->setpass(pass);
        v->setage(stoi(age_str));
        v->setPhasvoted(Pvoted_str != "0"); // voted = true if not "0"
        v->setNhasvoted(Nvoted_str != "0");
        v->setVoterCode(Code(ccode, ncode));

        V[index++] = v;
    }

    read.close();
}

void election::set_startDate(date d) { startDate = d; }
void election::set_endDate(date d) { endDate = d; }
void election::set_isActive(bool b) { isActive = b; }
bool election::get_isActive() { return isActive; }
election:: ~election() {
    // Clean up dynamically allocated memory for candidates and voters
    if (C != nullptr) {
        for (int i = 0; i < candidate_no; ++i) {
            delete C[i];  // Delete each candidate object
        }
        delete[] C;  // Delete the array of candidate pointers
    }

    if (V != nullptr) {
        for (int i = 0; i < voter_no; ++i) {
            delete V[i];  // Delete each voter object
        }
        delete[] V;  // Delete the array of voter pointers
    }

}