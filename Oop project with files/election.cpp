#include<iostream>
#include<string>
#include"admin.h"
#include<fstream>
#include"election.h"
#include<windows.h>


election::election(int c, int v, string t, string a, bool active)
{
        id = 0;

    candidate_no = c;
    title = t;
    area = a;
    voter_no = v;
    C = nullptr;
    V = nullptr;
    winCode = nullptr;
}

election::election()
{
    winCode = nullptr;
    id = 0;
    candidate_no = 0;
    title = "";
    voter_no = 0;
    area = "";
    C = nullptr;
}
void election::outputCand()
{
    for (int i = 0; i < candidate_no; i++) {
        cout << "ID: " << C[i]->getc_id() << endl;
        cout << "Name: " << C[i]->getName()<<endl;
        cout << "Area: " << C[i]->getArea() << endl;
        cout << "Party: " << C[i]->getParty() << endl;
        cout << "------------------------\n";
    }
}
bool election::cast_Voteforpm() { return true; }
void election::selectVoter() {}
bool election::loginMNA(string c) { return true; }
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

    cout << "Enter Area: ";
    getline(in >> ws, e.area);

    cout << "Enter Start Date (DD-MM-YYYY): \n";
    in >> e.startDate;

    cout << "Enter End Date (DD-MM-YYYY): \n";
    in >> e.endDate;

    in.ignore(); // important: ignore leftover newline
    return in;
}

ostream& operator<<(ostream& out, const election& e) {
    out << "ID: " << e.id;
    out << "Title: " << e.title << endl;
    out << "Area: " << e.area << endl;
    out << "Start Date: " << e.startDate << endl;
    out << "End Date: " << e.endDate << endl;
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

bool isInteger(const std::string& s) {
    if (s.empty()) return false;
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] < '0' || s[i] > '9') {
            return false;
        }
    }
    return true;
}

void election::addCandidate(string filename) {
    ifstream read(filename);
    if (!read.is_open()) {
        cout << "Error opening file: " << filename << "\n";
        return;
    }

    // Free previously allocated memory if any
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
            C[index]->setPosition(line);
            break;
        case 1:
            C[index]->setcode(line);
            break;
        case 2:
            C[index]->setNcode(line);
            break;
        case 3:
            C[index]->setName(line);
            break;
        case 4:
            C[index]->setParty(line);
            break;
        case 5:
            if (isInteger(line))
                C[index]->setc_id(stoi(line));
            else {
                cout << "Invalid candidate ID at candidate #" << index + 1 << ": " << line << endl;
                return;
            }
            break;
        case 6:
            C[index]->setArea(line);
            break;
        case 7:
            C[index]->setBio(line);
            break;
        case 8:
            C[index]->setcnic(line);
            break;
        case 9:
            if (isInteger(line)) {
                C[index]->setnoOfvotes(stoi(line));
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
    cout << "---------Successfully loaded " << candidate_no << " candidate(s).---------\n";
    system("cls");
}

string election::checkNcode(int i) {
    if (C == nullptr) {
        addCandidate("MPA DATA.txt");
    }
    if (i < 0 || i >= candidate_no) {
        cout << "Error: Invalid candidate index i = " << i << endl;
        return ""; 
    }
    if (C[i] == nullptr) {
        cout << "Error: Candidate at index " << i << " is not initialized!" << endl;
        return ""; 
    }
    return C[i]->getcons().getNcode();
}

void election::assignMpa(string n, int i){}
void election::inputalldata(string filename) {
    if (C == nullptr) {
        addCandidate(filename);
    }

    // Open the file with truncation mode to overwrite
    ofstream write(filename, ios::out | ios::trunc);  // <-- This forces overwrite
    if (!write.is_open()) {
        cout << "Error opening file!!\n";
        return;
    }

    for (int i = 0; i < candidate_no; i++) {
        if (C[i] == nullptr) {
            cout << "Error: Candidate at index " << i << " is not initialized!\n";
            continue;
        }

        // Write candidate data
        write << C[i]->getPosition() << endl;
        write << C[i]->getcons().getcode() << endl;
        write << C[i]->getcons().getNcode() << endl;
        write << C[i]->getName() << endl;
        write << C[i]->getParty() << endl;
        write << C[i]->getc_id() << endl;
        write << C[i]->getArea() << endl;
        write << C[i]->getBio() << endl;
        write << C[i]->getcnic() << endl;
        write << C[i]->getnoOfvotes() << endl;
        write << "###" << endl;
    }

    write.close(); // Close file
}


int election::check(string n) { return 1; }
bool election::login(int i, string c, string filename) {
    if (C == nullptr) { addCandidate(filename); }
    for (int j = 0; j < candidate_no; j++) {
        if (C[j] != nullptr) { // null check
            int a = C[j]->getc_id();
            if (a == i) {
                if (C[j]->getcnic() == c)
                    return true;
                else
                    return false;
            }
        }
    }
    return false;
}
void election::showCandidates(string code){}
int election::checkcandexist(string n, string filename) { return 1; }
void election::showCand(string filename)
{
    if (C == nullptr) {
        addCandidate(filename);
    }
    for (int i = 0; i < candidate_no; i++)
    {
        if (C[i]->getcons() == winCode[i])
        {
            cout << *C[i];
        }
    }
}
void election::assignCode(){}
void election::select_cand() {}
void election::winnerCand(string filename)
{
    ifstream read;
    read.open(filename);
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

    for (int k = 0; k < candidate_no; k++) {
        for (int m = 0; m < i; m++) {
            if (arr[m] == C[k]->getcons().getcode()) {
                cout << *C[k];  
                cout << "-------------------\n";
            }
        }
    }

    delete[] arr;
}

int election::checkCity(string c, int k)
{
    // Step 1: Check if k is within valid range
    if (k < 0 || k >= candidate_no) {
        cout << "Error: Invalid candidate index k = " << k << endl;
        return -99; // error code
    }

    for (int i = 0; i < candidate_no; i++) {
        // Step 2: Null pointer checks
        if (C[i] == nullptr || C[k] == nullptr) {
            cout << "Error: Null pointer at i = " << i << " or k = " << k << endl;
            return -98; // error code
        }

        // Step 3: Compare area, party, and constituency code safely
        if (C[i]->getArea() == C[k]->getArea()) {
            if (C[i]->getParty() == C[k]->getParty()) {
                // Assuming getcons() returns **by reference**. If it returns a pointer, tell me.
                if (C[i]->getcons().getcode() == c) {
                    return -1;
                }
            }
            else if (C[i]->getParty() != C[k]->getParty()) {
                if (C[i]->getcons().getcode() != c) {
                    return -2;
                }
            }
        }
    }
    return 2;
}

bool election::checkParty(string filename,string area,string party) {
    if (C == nullptr){
        addCandidate(filename);
}
    for (int i = 0; i < candidate_no; i++) {
        if (C[i]->getArea() == area) {
            if (C[i]->getParty() == party) {
                return false;
            }
        }
    }
    return true;
}
void election::regCandidate(string filename, string id, string pos) {
    int size = candidate_no + 1;
    string area, party;
    candidate** cand = new candidate * [size];

    // Copy old candidates
    for (int i = 0; i < candidate_no; i++) {
        cand[i] = C[i];
    }

    // Add new candidate
    cand[size - 1] = new candidate();
    cin >> *cand[size - 1];
    cout << "Enter Party: ";
    getline(cin, party);

    cout << "Enter Area: ";
    getline(cin, area);
    while (!checkParty(filename, area, party)) {
        cout << "There can't be more than 1 candidate of same party in an area!!\n";
        cout << "Enter Party again: ";
        getline(cin, party);
        cout << "Enter Area again: ";
        getline(cin, area);
    }
    cand[size - 1]->setPosition(pos);
    cand[size - 1]->inputFile(filename, id);

    // Free old array only (not the candidates)
    delete[] C;

    C = cand;
    candidate_no = size;
}
void election::deleteCandidateById(int targetId, string filename) {
    bool found = false;
    int indexToDelete = -1;

    // Search candidate in array
    for (int i = 0; i < candidate_no; i++) {
        if (C[i]->getc_id() == targetId) {
            found = true;
            indexToDelete = i;
            break;
        }
    }

    if (!found) {
        cout << "Candidate with ID " << targetId << " not found.\n";
        return;
    }

    // Delete candidate object
    delete C[indexToDelete];

    // Shift array left
    for (int i = indexToDelete; i < candidate_no - 1; i++) {
        C[i] = C[i + 1];
    }

    candidate_no--; // Reduce count

    // Call your existing function to write all candidates back
    inputalldata(filename);

    cout << "Candidate with ID " << targetId << " deleted successfully.\n";
}

void election::set_id(int i) { id = i; }

bool election::isactive(date d) {

    if (d >= startDate && d <= endDate )return 1;
    else
        return false;

}
void election::castVote(voter* v) {}
voter* election::login(const string& nic, const string& password) {
    for (int i = 0; i < voter_no; ++i) {
        if (V[i]->getcnic() == nic && V[i]->getpass() == password && V[i]->getVoterCode().getcode() != "0" && V[i]->getVoterCode().getNcode() != "0" && V[i]->getVoterCode().getcode() != "null" && V[i]->getVoterCode().getNcode() != "null") {
            return V[i]; // return existing object from memory
        }
    }
    return nullptr;
}

void election::assignCodeToVoterById(int id) {
    bool found = false;
    for (int i = 0; i < voter_no; ++i) {
        if (V[i]->getid() == id && (V[i]->getVoterCode().getcode() == "null" && V[i]->getVoterCode().getNcode() == "null") || (V[i]->getVoterCode().getcode() == "0" && V[i]->getVoterCode().getNcode() == "0")) {
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
            found = true;
            break;  // Stop loop once voter is found
        }
    }

    if (!found) {

        cout << "No Voter with ID " << id << "found Available for Assigning code.\n";
    }

}

void election::adminAssignCodesFlow() {
    if (listVotersWithoutCodes()) {
        char n;
        int id;
        cout << "\nEnter Voter ID to assign codes: ";
        cin >> id;
        system("cls");
        Sleep(500);
        assignCodeToVoterById(id);
        cout << "The code Assigned: \n";
        for (int i = 0; i < voter_no; ++i) {
            if (V[i]->getid() == id) {
                cout << "Code: " << V[i]->getVoterCode().getcode() << endl;
                cout << "Ncode: " << V[i]->getVoterCode().getNcode() << endl;
                cout << "Press any key to proceed: ";
                cin >> n;
                system("cls");
                Sleep(500);
            }
        }

    }
    /*   deleteVoterByID(id);*/
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
bool election::loadVotersFromFile(const string& filename) {
    ifstream read(filename);
    if (!read) {
        system("cls");
        Sleep(500);
        cout << " Unable to open file: " << filename << endl;
        return false;
    }

    int line_count = 0;
    string line;
    while (getline(read, line)) {
        if (!line.empty()) ++line_count;
    }

    if (line_count % 9 != 0) {
        system("cls");
        Sleep(500);
        cout << " Invalid file format. Expected multiple of 9 lines, got " << line_count << " lines.\n";
        read.close();
        return false;
    }

    voter_no = line_count / 9;
    //cout << " Found " << voter_no << " voters in the file.\n"; // Debug message

    read.clear();
    read.seekg(0, ios::beg);

    V = new voter * [voter_no];
    int index = 0;

    while (index < voter_no) {
        string id_str, name, cnic, pass, age_str, pvoted_line, nvoted_line, ccode, ncode; bool Pvoted_str, Nvoted_str;

        getline(read, id_str);
        getline(read, name);
        getline(read, cnic);
        getline(read, pass);
        getline(read, age_str);
        getline(read, ccode);
        getline(read, ncode);
        getline(read, pvoted_line);
        getline(read, nvoted_line);
        Pvoted_str = (pvoted_line == "1" || pvoted_line == "true");
        Nvoted_str = (nvoted_line == "1" || nvoted_line == "true");


        if (read.fail()) {
            system("cls");
            Sleep(500);;
            cout << " Error reading data for voter #" << index + 1 << endl;
            break;
        }

        voter* v = new voter();
        v->setid(stoi(id_str));
        v->setname(name);
        v->setcnic(cnic);
        v->setpass(pass);
        v->setage(stoi(age_str));
        v->setVoterCode(Code(ccode, ncode));
        v->setPhasvoted(Pvoted_str);
        v->setNhasvoted(Nvoted_str);

        V[index++] = v;
    }

    read.close();
    //cout << "voters Loaded from file.\n";
    return true;
}

bool election::listVotersWithoutCodes() {
    if (loadVotersFromFile("Voters.txt")) {
        cout << "Listing Voters without assigned codes:\n";
        system("cls");
        Sleep(500);
        bool found = false;  // Flag to check if any voter is found without code

        for (int i = 0; i < voter_no; ++i) {
            // Check if either code is "null"
            if (V[i]->getVoterCode().getcode() == "null" || V[i]->getVoterCode().getNcode() == "null" || V[i]->getVoterCode().getcode() == "0" || V[i]->getVoterCode().getNcode() == "0") {
                cout << "ID: " << V[i]->getid()
                    << ", Name: " << V[i]->getname()
                    << ", CNIC: " << V[i]->getcnic() << endl;
                cout << "_________________________________\n";
                found = true;
            }
        }

        if (!found) {
            cout << "No voters found without codes." << endl;
            return false;
        }

        return true;  // Only after checking all voters
    }
    return false;  // If file couldn't be loaded
}
void election::set_startDate(date d) { startDate = d; }
void election::set_endDate(date d) { endDate = d; }
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
void election::viewVoteCountIfElectionEnded(const date& today){}