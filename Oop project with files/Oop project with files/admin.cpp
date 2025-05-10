#include<iostream>
#include<fstream>
#include<string>
#include "user.h"
#include "voter.h"
#include "admin.h"
#include "election.h"
#include "general.h"
#include "national.h"
#include "local.h"
#include "candidate.h"
using namespace std;

int admin::mna_count = 0;

admin::admin() {
    // election_no = 3;
    // e = new election * [election_no];  // Allocating array of pointers to elections

    // // Initialize each election pointer
    // for (int i = 0; i < election_no; ++i) {
    //     e[i] = new election();  // Allocate new election objects
    // }
}

admin::~admin() {
    // Clean up the memory for each election
    for (int i = 0; i < election_no; ++i) {
        delete e[i];
    }
    delete[] e;  // Free the array of election pointers
}

string admin::getcnic() { return cnic; }
bool admin::login() {
    admin d;
    d.inputUserData();
    ifstream read;
    read.open("admin.txt");
    read >> name;
    read >> cnic;
    read >> password;
    if (name == d.name && cnic == d.cnic && password == d.password)
        return 1;
    else
        return 0;
}
istream& operator>>(istream& in, admin& a) {
    if (!a.status) {
        a.inputUserData();
        ofstream write;
        write.open("admin.txt");
        write << a.name << endl;
        write << a.cnic << endl;
        write << a.password << endl;
        a.status = 1;
    }
    else {
        cout << "Admin already signed up\n";
    }
    return in;
}

ostream& operator<<(ostream& out, admin& a) {
    a.outputUserData();

    cout << "Admin manages " << a.election_no << " election(s)." << endl;
    return out;
}

void admin::createElection() {
    election_no += 1;
    election** temp;
    temp = new election * [election_no];
    for (int i = 0; i < election_no - 1; ++i) {
        temp[i] = e[i];  // shallow copy (just pointer assignment)
    }

    // Step 3: Ask for election type
    int choice;
    cout << "Enter type of election you want to create.\n1. General Election\n2. Local Election\n3. National Election\n";
    cin >> choice;
    ofstream out;
    // Step 4: Create appropriate derived object
    switch (choice) {
        out.open("Election.txt", ios::app);
    case 1: {
        temp[election_no - 1] = new general_election();
        cin >> *temp[election_no - 1];
        out << temp[election_no - 1]->get_id() << endl;
        out << temp[election_no - 1]->get_title() << endl;
        out << temp[election_no - 1]->get_area() << endl;
        out << temp[election_no - 1]->get_startDate().getDay() << "/n" << temp[election_no - 1]->get_startDate().getMonth() << "/n" << temp[election_no - 1]->get_startDate().getYear() << endl;

        out << temp[election_no - 1]->get_endDate().getDay() << "/n" << temp[election_no - 1]->get_startDate().getMonth() << "/n" << temp[election_no - 1]->get_startDate().getYear() << endl;

        out << (temp[election_no - 1]->get_isActive() ? "Yes" : "No") << endl;

        break;
    }
    case 2: {
        temp[election_no - 1] = new local_election();
        cin >> *temp[election_no - 1];
        out << temp[election_no - 1]->get_id() << endl;
        out << temp[election_no - 1]->get_title() << endl;
        out << temp[election_no - 1]->get_area() << endl;

        out << temp[election_no - 1]->get_startDate().getDay() << "/n" << temp[election_no - 1]->get_startDate().getMonth() << "/n" << temp[election_no - 1]->get_startDate().getYear() << endl;

        out << temp[election_no - 1]->get_endDate().getDay() << "/n" << temp[election_no - 1]->get_startDate().getMonth() << "/n" << temp[election_no - 1]->get_startDate().getYear() << endl;

        out << (temp[election_no - 1]->get_isActive() ? "Yes" : "No") << endl;
        break;
    }
    case 3: {
        temp[election_no - 1] = new national_election();
        cin >> *temp[election_no - 1];
        out << temp[election_no - 1]->get_id() << endl;
        out << temp[election_no - 1]->get_title() << endl;
        out << temp[election_no - 1]->get_area() << endl;

        out << temp[election_no - 1]->get_startDate().getDay() << "/n" << temp[election_no - 1]->get_startDate().getMonth() << "/n" << temp[election_no - 1]->get_startDate().getYear() << endl;

        out << temp[election_no - 1]->get_endDate().getDay() << "/n" << temp[election_no - 1]->get_startDate().getMonth() << "/n" << temp[election_no - 1]->get_startDate().getYear() << endl;
        out << (temp[election_no - 1]->get_isActive() ? "Yes" : "No") << endl;
        break;
    }
    default: {
        cout << "Invalid choice. Election creation cancelled.\n";
        election_no--;
        delete[] temp;
        return;
        break;
    }
    }
    delete[]e;
    e = temp;
}
void admin::loadElectionsFromFile() {
    ifstream read("Election.txt");
    if (!read) {
        cout << "Unable to open file: Election.txt " << endl;
        return;
    }

    // Count number of non-empty lines
    int line_count = 0;
    string line;
    while (getline(read, line)) {
        if (!line.empty()) line_count++;
    }

    int lines_per_election = 6;
    int total_elections = line_count / lines_per_election;

    read.clear();
    read.seekg(0, ios::beg);

    e = new election * [total_elections];
    election_no = total_elections;

    for (int i = 0; i < total_elections; i++) {
        string title, area, isActiveStr, startStr, endStr;
        date sd, ed;
        int sday, smonth, syear;
        int eday, emonth, eyear;
        getline(read, title);
        getline(read, area);
        read >> sday;
        read >> smonth;
        read >> syear;
        read >> eday;
        read >> emonth;
        read >> eyear;
        getline(read, isActiveStr);
        getline(read, startStr);
        getline(read, endStr);


        election* ee = new election();
        ee->set_title(title);
        ee->set_area(area);
        ee->set_isActive(isActiveStr == "0");

        sd.setDate(sday, smonth, syear);
        ed.setDate(eday, emonth, eyear);

        ee->set_startDate(sd);
        ee->set_endDate(ed);


        e[i] = ee;
    }

    read.close();
}

int admin::getelectionNo() {
    return election_no;
}
election** admin::getelection() { return e; }
