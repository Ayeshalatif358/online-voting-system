#include<iostream>
#include<string>
#include"user.h"
#include"admin.h"
#include"general.h"
#include"national.h"
#include"local.h"
#include<fstream>
#include<windows.h>
using namespace std;

void menu(admin& A, election** e);
void candMenu(election** e, int a);
void admin_menu(admin& a, election** e);
void voter_menu(election* e, voter* v, string ecode);
int assignmpa(election** e);
void showResult(election** e);
void seeVoteCount(admin& A) {
    date d;
    cout << "Enter date (dd mm yyyy): \n";
    cin >> d;
    system("cls");
    Sleep(500);
    election* selected = nullptr;
    A.loadElectionsFromFile();
    string title;
    cout << "\n Elections aviailable to see Vote Count:\n"; bool found = false;
    for (int i = 0; i < A.getelectionNo(); ++i) {
        election* e = A.getelection()[i];
        title = e->get_title();

        // Check if not active based on entered date 
        if (!e->isactive(d)) {
            cout << "ID: " << e->get_id() << " | Title: " << e->get_title() << "\n";
            found = true;

        }
    }
    char n;
    if (found) {
        int eid;
        cout << "Enter the ID of the election you want to see Vote Count for: ";
        cin >> eid;
        system("cls");
        Sleep(500);
        for (int i = 0; i < A.getelectionNo(); ++i) {
            if (A.getelection()[i]->get_id() == eid) {
                selected = A.getelection()[i];
                break;
            }
        }
    }
    if (!selected && !found) {
        cout << "No election to SEE Vote Count.\n";
        return;
    }
    selected->viewVoteCountIfElectionEnded(d);
    cout << "Press any key to proceed: ";
    cin >> n;
    system("cls");
    Sleep(500);
}


int main() {
    admin a;
    election** e;
    e = new election * [3];
    local_election l;
    general_election g;
    e[0] = &g;
    e[1] = &l;

    menu(a, e);
    return 0;
}
void showResult(election** e) {
    int c = 0;
    while (c != 4) {
        cout << "1. General Election\n2. Local Election\n3. National Election\n4. Exit\nEnter choice: ";
        cin >> c;
        system("cls");
        Sleep(500);
        date d; char n;
        cout << "Enter current date: \n";
        cin >> d;
        system("cls");
        Sleep(500);
        switch (c) {
        case 1:
            if (!e[0]->isactive(d)) {
                e[0]->select_cand();
            }
            else cout << "Election is in process!!\n";
            cout << "Press any key to proceed: ";
            cin >> n;
            system("cls");
            Sleep(500);
            break;
        case 2:
            if (!e[0]->isactive(d)) {
            e[1]->select_cand();
            }
            else cout << "Election is in process!!\n";
            cout << "Press any key to proceed: ";
            cin >> n;
            break;
        case 3:
            if (!e[0]->isactive(d)) {
                e[2]->select_cand();
            }
            break;
        case 4:
            cout << "Exiting....\n";
            break;
        default:
            cout << "Invalid input!!\n";
        }
    }
}

void login(string Id, string Pass) {
    ifstream fin("Voter.txt");
    if (!fin) {
        cout << "Error opening file.\n";
        return;
    }

    string id, name, cnic, age, pass, pv, nv, code1, code2;
    while (getline(fin, id)) {
        getline(fin, name);
        getline(fin, cnic);
        getline(fin, pass);
        getline(fin, age);
        getline(fin, code1);
        getline(fin, code2);
        fin >> pv;
        fin >> nv;
        fin.ignore();

        if (id == Id && pass == Pass) {
            cout << "Registered successfully!\nNow login to proceed further!\n";

            fin.close();
            return;
        }
    }

    fin.close();
    cout << "Not Registered yet.\n Please wait to be registered by admin!";
    return;
}

void candMenu(election** e, int a) {
    int choice = 0;
    while (choice != 3) {
        system("cls");
        Sleep(500);
        cout << "1. Sign Up\n2. Login\n3. Exit\nEnter Choice: ";
        cin >> choice;
        system("cls");
        Sleep(500); char n;
        switch (choice) {
        case 1:
            if (a == 1) {
                e[0]->regCandidate("MPA DATA.txt", "MPA ID.txt", "MPA");
                cout << "Signed Up Successfully\n";
            }
            else if (a == 2) { // FIXED: You had `a == 1` twice
                e[1]->regCandidate("MNA DATA.txt", "MNA ID.txt", "MNA"); // Also corrected e[0] to e[1] for MNA
                cout << "Signed Up Successfully\n";
            }
            else {
                cout << "Invalid Input!!\n";
            }
            break;

        case 2: {
            int id;
            string cnic;
            cout << "Enter your ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter CNIC: ";
            getline(cin, cnic);
            system("cls");
            Sleep(500);
            if (a == 1) {
                if (e[0]->login(id, cnic, "MPA DATA.txt")) {
                    cout << "Login Successfully!!\n";
                    cout << "Press any key to proceed: ";
                    cin >> n;
                    system("cls");
                    Sleep(500);
                }
                else {
                    cout << "Wrong Password!!\n";
                    cout << "Press any key to proceed: ";
                    cin >> n;
                    system("cls");
                    Sleep(500);
                }
            }
            else if (a == 2) {
                if (e[1]->login(id, cnic, "MNA DATA.txt")) {
                    cout << "Login Successfully!!\n";
                    cout << "Press any key to proceed: ";
                    cin >> n;
                    system("cls");
                    Sleep(500);
                }
                else {
                    cout << "Wrong Password!!\n";
                    cout << "Press any key to proceed: ";
                    cin >> n;
                    system("cls");
                    Sleep(500);
                }
            }
            else {
                cout << "Invalid Input!!\n";
                cout << "Press any key to proceed: ";
                cin >> n;
                system("cls");
                Sleep(500);
            }
            break;
        }

        case 3:
            cout << "Exiting....\n";
            cout << "Press any key to proceed: ";
            cin >> n;
            system("cls");
            Sleep(500);
            break;

        default:
            cout << "Invalid Input!!\n";
            cout << "Press any key to proceed: ";
            cin >> n;
            system("cls");
            Sleep(500);
            break;
        }
    }
}


void menu(admin& A, election** e) {
    int choice;
    do {

        char n;
        cout << "1. Admin\n2. Candidate\n3. Voter\n4. Leader\n5. Exit\nEnter choice: ";
        cin >> choice;
        system("cls");
        Sleep(500);
        switch (choice) {
        case 1: {

            int c;
            do {
                cout << "1.sign up\n2.log in\n3.exit\n Enter choice: ";
                cin >> c;
                system("cls");
                Sleep(500);
                switch (c) {
                case 1: {
                    cin >> A;
                    cout << "Now please Log in to proceed further\n";
                    cout << "Press any key to proceed: ";
                    cin >> n;
                    system("cls");
                    Sleep(500);
                    break;
                }
                case 2: {
                    system("cls");
                    Sleep(500);
                    if (A.login()) {
                        system("cls");
                        Sleep(500);
                        cout << "login successful\n";
                        cout << "Press any key to proceed: ";
                        cin >> n;
                        system("cls");
                        Sleep(500);
                        admin_menu(A, e);
                    }
                    else {
                        system("cls");
                        Sleep(500);
                        cout << "You may have entered wrong Name , NIC or Password\n";
                    }
                    break;
                }
                case 3:
                {
                    national_election n;
                }
                break;
                case 4: {
                    system("cls");
                    Sleep(500);
                    cout << "Exiting...............\n";
                    break;
                }
                default: {
                    system("cls");
                    Sleep(500);
                    cout << "Invalid input\n";
                    break;
                }
                }
            } while (c != 4);
            break;
        }
        case 2: {

            int choice = 0;
            while (choice != 4) {
                cout << "Enter your position:\n1. MPA\n2. MNA\n3. Voter\n4. Exit\nEnter choice: ";
                cin >> choice;
                switch (choice) {
                case 1:
                    candMenu(e, choice);
                    break;
                case 2:
                    candMenu(e, choice);
                    break;
                case 3:
                {
                    e[2]->selectVoter();
                    int c = 0;
                    while (c != 2) {
                        cout << "1. Login\n2. Exit\nEnter choice: ";
                        cin >> c;
                        switch (c) {
                        case 1:
                        {
                            string c;
                            cout << "Enter cnic: ";
                            if (e[2]->loginMNA(c)) {
                                char ch = 'y';
                                cout << "Login Successfully!!\nIf you want to cast press 'Y' or 'y'";
                                cin >> ch;
                                if (ch == 'Y' || ch == 'y') {
                                    e[2]->cast_Voteforpm();
                                }
                            }
                            else cout << "Wrong CNIC!!\n";
                        }break;
                        case 2:cout << "Exiting....\n"; break;
                        default:cout << "Invalid Input!!\n"; break;
                        }
                    }
                }
                break;
                case 4:
                    cout << "Exiting...............\n";
                    break;
                default:
                    cout << "Invalid choice\n";
                    break;
                }
            }
            break;
        }
        case 3: {
            system("cls");
            Sleep(500);
            election* selected = nullptr;
            int c;
            do {
                cout << "1.Sign Up\n2.Check Registration\n3.Log In\n4.See Vote Count\n5. See Result\n6.Exit\n Enter choice: ";
                cin >> c;
                system("cls");
                Sleep(500);
                switch (c) {
                case 1: {
                    voter* v = new voter();
                    if (v->signupToPendingFile()) {
                        cout << "Now please wait to be registered and assigned code by admin\n";
                        cout << "Press any key to proceed: ";
                        cin >> n;
                        system("cls");
                        Sleep(500);
                    }
                    else {
                        cout << "Press any key to proceed: ";
                        cin >> n;
                        system("cls");
                        Sleep(500);
                    }
                    break;
                }
                case 2: {
                    string nic, password;
                    cout << "Enter NIC: ";
                    cin >> nic;
                    cout << "Enter password: ";
                    cin >> password;
                    login(nic, password);
                    cout << "Press any key to proceed: ";
                    cin >> n;
                    system("cls");
                    Sleep(500);
                    break;
                }
                case 3: {
                    date d;
                    cout << "Enter date (dd mm yyyy): \n";
                    cin >> d;
                    system("cls");
                    Sleep(500);

                    A.loadElectionsFromFile();
                    string title;
                    cout << "\nActive Elections:\n";
                    bool found = false;
                    for (int i = 0; i < A.getelectionNo(); ++i) {
                        election* e1 = A.getelection()[i];
                        title = e1->get_title();
                        if (e1->isactive(d)) {
                            if (title != "National") {
                                cout << "ID: " << e1->get_id() << " | Title: " << e1->get_title() << "\n";
                                found = true;
                            }
                        }
                    }
                    if (found) {
                        int eid;
                        cout << "Enter the ID of the election you want to login for: ";
                        cin.ignore();
                        cin >> eid;
                        system("cls");
                        Sleep(500);
                        for (int i = 0; i < A.getelectionNo(); ++i) {
                            if (A.getelection()[i]->get_id() == eid) {
                                selected = A.getelection()[i];
                                title = A.getelection()[i]->get_title();
                                A.getelection()[i]->loadVotersFromFile("Voters.txt");
                                break;
                            }
                        }
                    }
                    if (!selected && !found) {
                        cout << "No election active on this date.\n";
                        break;
                    }
                    system("cls");
                    Sleep(500);
                    string nic, password;
                    cout << "Enter NIC: ";
                    cin >> nic;
                    cout << "Enter password: ";
                    cin >> password;
                    system("cls");
                    Sleep(500);
                    voter* v = selected->login(nic, password);
                    if (v != nullptr) {
                        cout << "Login successful\n";

                        cout << "Press any key to proceed: ";
                        cin >> n;
                        system("cls");
                        Sleep(500);
                        voter_menu(selected, v, title);
                    }
                    else {
                        cout << "Login failed\n";
                        cout << "Press any key to proceed: ";
                        cin >> n;
                        system("cls");
                        Sleep(500);
                    }
                    break;
                }
                case 4: {
                    A.loadElectionsFromFile();
                    seeVoteCount(A);
                    break;
                }
                case 5: {
                    showResult(e);
                    cout << "Press any key to proceed: ";
                    cin >> n;
                    break;
                }
                case 6: {
                    cout << "Exiting...............\n";
                    break;
                }
                default: {
                    cout << "Invalid input\n";
                    cout << "Press any key to proceed: ";
                    cin >> n;
                    system("cls");
                    Sleep(500);
                    break;
                }
                }
            } while (c != 6);
            break;
        }
        case 4: {
            national_election n;
            n.regCandidate("Leader DATA.txt", "N_ID", "pm");
            break;
        }

        default:
            cout << "Invalid choice.\n";
            break;
        }
    } while (choice != 5);
}

void voter_menu(election* e, voter* v, string ecode) {
    int choice;
    do {
        cout << "1. See Candidates\n2. Cast Vote\n3. Check Vote status\n4. Exit\nEnter Choice: ";
        cin >> choice;                    system("cls");
        Sleep(500);
        switch (choice) {
        case 1: {

            if (ecode == "General") {
                e->showCandidates(v->getVoterCode().getcode());
            }
            else if (ecode == "Local") {
                e->showCandidates(v->getVoterCode().getNcode());
            }
            break;
        }
        case 2: {
            e->castVote(v);
            e->saveVotersToFile("Voters.txt");
            break;
        }
        case 3: {
            char n;
            cout << "Vote Status for General Election: ";
            cout << v->getPhasvoted() << endl;
            cout << "Vote Status for Local Election: ";
            cout << v->getNhasvoted() << endl;
            cout << "Press any key to proceed: ";
            cin >> n;
            system("cls");
            Sleep(500);
            break;
        }
        case 4: {
            cout << "Exiting.............\n";
            break;
        }
        default:
            cout << "Invalid choice.\n";
            break;
        }
    } while (choice!= 4);
}


void admin_menu(admin& a, election** e) {
    int choice;
    election temp;
    char n;
    do {
        cout << "1. Create Election\n2. Register Candidate\n3. Register voter\n4. Assign MPA to MNA\n5. Delete MPA Candidate\n6.Delete MNA candidate\n6.Exit \nEnter choice";        cin >> choice;
        switch (choice) {
        case 1: {
            char n = 'y';
            while (n == 'y' || n == 'Y') {
                a.createElection();
                cout << "Create more Elections? (y/n): ";
                cin >> n;                    system("cls");
                Sleep(500);
            }
            break;
        }
        case 2: {
            int C = 0;
            while (C != 3) {
                cout << "1. Register MPA\n2. Register MNA\n3. Exit\nEnter choice: ";
                cin >> C;
                switch (C) {
                case 1:
                    e[0]->assignCode();
                    break;
                case 2:
                    e[1]->assignCode();
                    break;
                case 3:
                    cout << "Exiting..\n";
                    break;
                default:
                    cout << "Invalid choice!!\n";
                    break;
                }
            }
            break;
        }
        case 3: {

            char n = 'y';
            while (n == 'y' || n == 'Y') {
                temp.adminAssignCodesFlow();
                temp.saveVotersToFile("Voters.txt");
                cout << "Assign more codes? (y/n): ";
                cin >> n;
            }
            break;
        }
        case 4: {
            if (assignmpa(e) == 1)
                cout << "Assigned successfully!!\n";
            else if (assignmpa(e) == 3)
                cout << "Not assigned\n";
            else if (assignmpa(e) == 1)
                break;
        }
        case 5: {
            int id;
            cout << "Enter Candidate ID to Delete: \n";
            cin >> id;
            system("cls");
            Sleep(500);
            temp.deleteCandidateById(id, "MPA DATA.txt");
            break;
        }
        case 6: {
            int id;
            cout << "Enter Candidate ID to Delete: \n";
            cin >> id;
            system("cls");
            Sleep(500);
            temp.deleteCandidateById(id, "MNA DATA.txt");
            break;
        }
        case 7: {
            cout << "Exiting.............\n";
            cout << "Press any key to proceed: ";
            cin >> n;
            system("cls");
            Sleep(500);

            break;
        }
        default: {
            cout << "Invalid choice. Try again.\n";
            break;
        }
        }
    } while (choice != 7);
}

int assignmpa(election** e) {
    int a;
    date d;
    string c, n;
    cout << "Enter current date:\n";
    cin >> d;
    if (e[0]->isactive(d) && !e[1]->isactive(d)) {
        e[0]->select_cand();
        e[1]->select_cand();
    }
    else {
        cout << "Election is in process!!\n";
        return -1;
    }
    char ch = 'y';
    cin.ignore();
    while (ch == 'y' || ch == 'Y') {
        cout << "Enter constituency code of MPA: ";
        getline(cin, c);

        a = e[0]->checkcandexist(c, "MPA DATA.txt");
        if (a == -1) {
            cout << "You have entered wrong code!!\nIf you want to enter code again, press 'Y' or 'y': ";
            cin >> ch;
            cin.ignore();
        }
        else if (e[0]->checkNcode(a) != "") {
            cout << "This MPA is already assigned to a MNA!!\n";
            return -1;
        }
        else {
            break;
        }
    }

    ch = 'y';
    while (ch == 'y' || ch == 'Y') {
        cout << "Enter national code for this MPA: ";
        getline(cin, n);

        if (e[1]->checkcandexist(n, "MNA DATA.txt") == -1) {
            cout << "You have entered wrong code!!\nIf you want to enter code again, press 'Y' or 'y': ";
            cin >> ch;
            cin.ignore();
        }
        else {
            if (e[0]->check(n) == -1) {
                cout << "A national cannot be assigned to more than two MPAs!!\nIf you want to enter code again, press 'Y' or 'y': ";
                cin >> ch;
                cin.ignore();
            }
            else {
                break;
            }
        }
    }
    if (a != -1 && e[0]->check(n) != -1) {
        e[0]->assignMpa(n, a);
        cout << "MPA assigned successfully!\n";
        return 1;
    }

    return 3;
}
