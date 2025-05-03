#include<iostream>
#include<fstream>
#include<string>
#include "user.h"
#include "voter.h"
#include "admin.h"
#include "election.h"
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

int admin::getcnic() { return cnic; }
bool admin::login(){
    admin d;
    d.inputUserData(); 
    ifstream read;
    read.open("admin.txt");
    read>>name;
    read>>cnic;
    read>>password;
    if(name==d.name&&cnic==d.cnic&&password==d.password)
    return 1;
else
return 0;
}
istream& operator>>(istream& in, admin& a) {
    if(!a.status){
    a.inputUserData();
    ofstream write;
    write.open("admin.txt");
    write<<a.name<<endl;
    write<<a.cnic<<endl;
    write<<a.password<<endl;
a.status=1;
}else{
    cout<<"Admin already signed up\n";
}
    return in;
}

ostream& operator<<(ostream& out, admin& a) {
    a.outputUserData();

    cout << "Admin manages " << a.election_no << " election(s)." << endl;
    return out;
}

void admin::createElection() {
    election_no+=1;
    election **temp;
    temp=new election*[election_no];
    for (int i = 0; i < election_no - 1; ++i) {
        temp[i] = e[i];  // shallow copy (just pointer assignment)
    }

    // Step 3: Ask for election type
    int choice;
    cout << "Enter type of election you want to create.\n1. General Election\n2. Local Election\n3. National Election\n";
    cin >> choice;

    // Step 4: Create appropriate derived object
    switch (choice) {
        case 1:
            temp[election_no - 1] = new general_election();
            break;
        case 2:
            temp[election_no - 1] = new local_election();
            break;
        case 3:
            temp[election_no - 1] = new national_election();
            break;
        default:
            cout << "Invalid choice. Creating general election by default.\n";
            temp[election_no - 1] = new general_election();
            break;
    }
    delete[]e;
    e=temp;
}

void admin::CMelection() {
    cin >> *e[1];  // Read election data for e[1]
}

void admin::PMelection() {
    cin >> *e[2];  // Read election data for e[2]
}

void admin::addCandidateMNA() {
    candidate** ca = e[0]->get_candidate();
    int a = e[0]->get_candidate_no();
    for (int i = 0; i < a; i++) {
        if (ca[i]->getPosition() == "MNA" || ca[i]->getPosition() == "mna") {
            string c, n;
            cout << "Enter constituency code: ";
            cin >> c;
            cout << "Enter national code: ";
            cin >> n;
            while (e[0]->MNcheck(i, n) == -1) {
                cout << "National Code of MNA must be unique!!\nEnter National Code again: ";
                cin >> n;
            }
            ca[i]->inputCand(c, n);
            mna_count++;
        }
    }
}

void admin::addCandidateMPA() {
    cout << "Inside addCandidateMPA function." << endl;

    if (e[0] == nullptr) {
        cout << "e[0] is null, cannot proceed with adding MPA candidates." << endl;
        return;  // Exit if the election object is invalid
    }

    string c;
    candidate** ca = e[0]->get_candidate();
    int a = e[0]->get_candidate_no();
    cout << "Number of candidates: " << a << endl;

    for (int i = 0; i < a+1; i++) {
        if (ca[i] != nullptr) {
            cout << "Candidate " << i + 1 << " Position: " << ca[i]->getPosition() << endl;
            if (ca[i]->getPosition() == "MPA" || ca[i]->getPosition() == "mpa") {
                cout << "Position matches MPA." << endl;
                cout << *ca[i] << endl;
                cout << "Enter constituency code of MPA: ";
                cin >> c;
                ca[i]->setcode(c);
                cout << "Updated Candidate Info: " << endl;
                cout << *ca[i] << endl;
            }
        }
        else {
            cout << "Candidate " << i + 1 << " is null." << endl;
        }
    }
}





int admin::check(candidate** ca, string m) {
    int a = e[0]->get_candidate_no();
    for (int i = 0; i < a; i++) {
        if (ca[i]->getcons().getcode() == m) {
            return i;
        }
    }
    return -1;
}

void admin::assignMpa() {
    string c;
    candidate** ca = e[0]->get_candidate();
    Code* mcode = e[0]->selectedMna();
    e[0]->showMPA();
    int k = 0;
    int z = e[0]->getmnaCount();
    for (int i = 0; i < z; i++) {
        cout << "Enter constituency code for MNA having code: " << mcode[i] << endl;
        for (int j = 0; j < 2; j++) {
            cout << "For MPA" << j + 1 << ": ";
            cin >> c;
            k = check(ca, c);
            while (k == -1) {
                cout << "No such MPA exist!!\n";
                cout << "Enter constituency code for MPA again: ";
                cin >> c;
                k = check(ca, c);
            }
            if (k != -1) {
                ca[k]->setNcode(mcode[i].getNcode());
            }
        }
    }
}
