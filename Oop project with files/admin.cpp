#include<iostream>
#include<string>
#include"admin.h"
#include"general.h"
#include"national.h"
#include"local.h"
#include<fstream>
#include<windows.h>
using namespace std;

int admin::mna_count = 0;

admin::admin() {
    e = nullptr;
    election_no = 0;
     election_no = 3;
     e = new election * [election_no]; 


     for (int i = 0; i < election_no; ++i) {
         e[i] = new election();  
     }
}

admin::~admin() {
    if (e != nullptr) {
        for (int i = 0; i < election_no; ++i) {
            delete e[i];
        }
        delete[] e;
    }
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
    ifstream check("admin.txt");

    // Check if admin.txt has any content
    if (check.peek() != ifstream::traits_type::eof()) {
        cout << "Admin already signed up.\n";
        return in;
    }
    check.close();

    // If file is empty, allow signup
    a.inputUserData();

    ofstream write("admin.txt");
    if (!write) {
        cerr << "Failed to open admin.txt for writing.\n";
        return in;
    }

    write << a.name << endl;
    write << a.cnic << endl;
    write << a.password << endl;

    cout << "Admin registered successfully.\n";

    return in;
}

ostream& operator<<(ostream& out, admin& a) {
    ifstream read("admin.txt");
    if (!read) {
        out << "No admin data found.\n";
        return out;
    }

    getline(read, a.name);
    getline(read, a.cnic);
    getline(read, a.password);

    a.outputUserData();
    out << "Admin manages " << a.election_no << " election(s)." << endl;

    return out;
}

void admin::createElection() {
    election_no += 1;
    election** temp;
    temp = new election * [election_no];
    for (int i = 0; i < election_no - 1; ++i) {
        temp[i] = e[i];  // shallow copy (just pointer assignment)
    }
    system("cls");
    Sleep(500);
    // Step 3: Ask for election type
    int choice;
    cout << "Enter type of election you want to create.\n1. General Election\n2. Local Election\n3. National Election\n";
    cin >> choice;
    system("cls");
    Sleep(500);
    ofstream out;
    ifstream read; int id;
    read.open("Election ID.txt");
    if (!read.is_open()) {
        cout << "Error opening file\n"; 
    }
    read >>id;
    read.close();

    out.open("Election.txt", ios::app);
    if (!out.is_open()) {
        system("cls");
        Sleep(500);
        cout << "Cannot open Election.txt to write\n";

    }

    // Step 4: Create appropriate derived object
    else {
        switch (choice) {
        case 1: {

            temp[election_no - 1] = new general_election();
            temp[election_no - 1]->set_id(++id);
            system("cls");
            Sleep(500);
            cin >> *temp[election_no - 1];
            out << temp[election_no - 1]->get_id() << endl;
            out << "General" << endl;
            out << temp[election_no - 1]->get_area() << endl;
            out << temp[election_no - 1]->get_startDate().getDay() << endl << temp[election_no - 1]->get_startDate().getMonth() << endl << temp[election_no - 1]->get_startDate().getYear() << endl;

            out << temp[election_no - 1]->get_endDate().getDay() << endl << temp[election_no - 1]->get_startDate().getMonth() << endl << temp[election_no - 1]->get_startDate().getYear() << endl;

            out.close();
            system("cls");
            Sleep(500);
            cout << "General Election with ID " << temp[election_no - 1]->get_id() << " Created Successfully\n";
            out.open("Election ID.txt");
            out << temp[election_no - 1]->get_id() << endl;
            out.close();
            break;
        }
        case 2: {
            temp[election_no - 1] = new local_election();
            temp[election_no - 1]->set_id(++id);
            cin >> *temp[election_no - 1];
            system("cls");
            Sleep(500);
            out << temp[election_no - 1]->get_id() << endl;
            out << "Local" << endl;
            out << temp[election_no - 1]->get_area() << endl;

            out << temp[election_no - 1]->get_startDate().getDay() << endl << temp[election_no - 1]->get_startDate().getMonth() << endl << temp[election_no - 1]->get_startDate().getYear() << endl;

            out << temp[election_no - 1]->get_endDate().getDay() << endl << temp[election_no - 1]->get_startDate().getMonth() << endl << temp[election_no - 1]->get_startDate().getYear() << endl;
            out.close();

            system("cls");
            Sleep(500);
            cout << "Local Election with ID " << temp[election_no - 1]->get_id() << " Created Successfully\n";

            break;
        }
        case 3: {
            temp[election_no - 1] = new national_election();
            temp[election_no - 1]->set_id(++id);
            cin >> *temp[election_no - 1];
            system("cls");
            Sleep(500);
            out << temp[election_no - 1]->get_id() << endl;
            out << "National" << endl;
            out << temp[election_no - 1]->get_area() << endl;

            out << temp[election_no - 1]->get_startDate().getDay() << endl << temp[election_no - 1]->get_startDate().getMonth() << endl << temp[election_no - 1]->get_startDate().getYear() << endl;

            out << temp[election_no - 1]->get_endDate().getDay() << endl << temp[election_no - 1]->get_startDate().getMonth() << endl << temp[election_no - 1]->get_startDate().getYear() << endl;
            out << endl;
            out.close();

            system("cls");
            Sleep(500);
            cout << "National Election with ID " << temp[election_no - 1]->get_id() << " Created Successfully\n";

            break;
        }
        default: {
            system("cls");
            Sleep(500);;
            cout << "Invalid choice. Election creation cancelled.\n";
            election_no--;
            delete[] temp;
            return;
            break;
        }
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

    int lines_per_election = 9;
    int total_elections = line_count / lines_per_election;

    read.clear();
    read.seekg(0, ios::beg);

    e = new election * [total_elections];
    election_no = total_elections;

    for (int i = 0; i < total_elections; i++) {
        string title, area;
        int id;
        date sd, ed;
        int sday, smonth, syear;
        int eday, emonth, eyear;

        read >> id;
        read.ignore(); // clear leftover newline

        getline(read, title);
        getline(read, area);

        read >> sday >> smonth >> syear;
        read >> eday >> emonth >> eyear;

        // clear newline before reading strings

        // Create and assign the correct election object based on title
        election* ee = nullptr;
        if (title == "General") {
            ee = new general_election();
        }
        else if (title == "Local") {
            ee = new local_election();
        }
        else if (title == "National") {
            ee = new national_election();
        }

        // Set properties for the election object
        if (ee) {
            ee->set_id(id);
            ee->set_title(title);
            ee->set_area(area);

            sd.setDate(sday, smonth, syear);
            ed.setDate(eday, emonth, eyear);
            ee->set_startDate(sd);
            ee->set_endDate(ed);

            e[i] = ee; // Assign the election to the array
        }
    }
    read.close();
}
int admin::getelectionNo() {
    return election_no;
}
election** admin::getelection() { return e; }