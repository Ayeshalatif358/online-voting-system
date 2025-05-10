#include<iostream>
#include<fstream>
#include<string>
#include"user.h"
#include"voter.h"
#include"candidate.h"
#include"admin.h"
#include"local.h"
#include"code.h"
#include"election.h"
#include"general.h"
#include"national.h"
using namespace std;
void menu(admin& A);
void elections();
void admin_menu(admin &a);
void voter_menu(election* e, voter* v);
int main()
{
    //voter::loadLastVoterId();
    admin a;
    // a.createElection();
    // election E;
    // char ch='Y';
    // while (ch == 'Y' || ch == 'y')
    // {
    //     E.addCandidate();
    //     cout << "Enter 'Y' or 'y' to add candidate: ";
    //     cin >> ch;
    // }
    // E.showCand();
    // a.addCandidateMPA();
    //general_election E1;
    menu(a);
    return 0;
}
void login(string Id, string Pass) {
    ifstream fin("Voter.txt");
    if (!fin) {
        cout << "Error opening file.\n";
        return;
    }

    string id, name, cnic, age, pass, gender, address, code;
    while (getline(fin, id)) {
        getline(fin, name);
        getline(fin, cnic);
        getline(fin, age);
        getline(fin, pass);
        getline(fin, gender);
        getline(fin, address);
        getline(fin, code);

        if (id == Id && pass == Pass) {
            cout << "Registered successfully!\nNow please login to proceed further!\n";
            fin.close();
            return;
        }
    }

    fin.close();
    cout << "Not Registered yet.\n Please wait to be registered by admin!";
    return ;
}
void menu(admin& A)
{
    int choice;
    cout << "1. Admin\n2. Candidate\n3. Voter\nEnter choice: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
    {
        int c;
        do {
            cout << "1.sign up\n2.log in\n3.exit\n Enter choice: ";
            cin >> c;
            switch (c)
            {
            case 1:
            {
                cin >> A;
                cout << "Now please Log in to proceed further\n";
                break;
            }
            case 2: {

                if (A.login()) {
                    cout << "login sucessfull\n";
                    admin_menu(A);
                    break;
                }
                else {
                    cout << "You may have entered wrong Name , NIC or Password\n";
                    break;
                }
            }
            case 3: {
                cout << "Exiting...............\n";
            }
            default: {
                cout << "Invalid input\n";
            }
            }
        } while (c != 3);
    }
    case 2:
    {
        int c;
        do {
            cout << "1.sign up\n2.Check Registration\n3.log in\n4.exit\n Enter choice: ";
            cin >> c;
            switch (c)
            {
            case 1:
            {
                voter* v = new voter();
                v->signupToPendingFile();
                cout << "Now please wait to be registered and assigned code by admin\n";
                break;
            }
            case 2: {

                string nic, password;
                cout << "Enter NIC: ";
                cin >> nic;
                cout << "Enter password: ";
                cin >> password;
                login(nic, password);
                break;
                
            }
            case 3: {
                date d;
                cout << "Please Enter date to see active election to login for: ";
                cin >> d;
                election* selected = nullptr;
                A.loadElectionsFromFile();
                for (int i = 0; i < A.getelectionNo(); ++i) {
                    if (A.getelection()[i]->isactive()) {
                        if (A.getelection()[i]->get_title() != "National" || A.getelection()[i]->get_title() != "national") {
                            cout << "Active Elections: \n";
                            cout << A.getelection()[i]->get_id() << "\n";
                            cout << A.getelection()[i]->get_title() << "\n";
                        }
                    }
                }


                if (!selected) {
                    cout << "No election active on this date.\n";
                    break;
                }
                string nic, password;
                cout << "Enter NIC: ";
                cin >> nic;
                cout << "Enter password: ";
                cin >> password;

                voter* v = selected->login(nic, password);
                if (v != nullptr) {
                    cout << "Login successful\n";
                    voter_menu(selected, v);  // pass voter* to the menu
                }
                else {
                    cout << "Login failed\n";
                }
            }
            case 4: {
                cout << "Exiting...............\n";
            }
            default: {
                cout << "Invalid input\n";
            }
            }
        } while (c != 3);
    }
    }
}
void voter_menu(election* e, voter* v) {
    int choice;
    cout << "1. See Candidates\n2. Cast Vote For MPA \n3. See No. of votes\n4. See Results\nEnter Choice: ";
    cin >> choice;

    switch (choice) {
    case 1: {
        e->showCand();
        break;
    }
    case 2: {
        e->castVoteP(v); // Pass the logged-in voter to castVote
        break;
    }
          // Add other cases if needed
    default:
        cout << "Invalid choice.\n";
    }
}
void elections()
{
    int choice;
    cout << "1. National Election\n2. General Election\nEnter Choice: ";
    cin >> choice;
    switch (choice)
    {
    case 1:

        break;
    case 2:
        break;
    defaul:
        cout << "Invalid Input!!\n";
    }
}
void admin_menu(admin &a)
{
    int choice;
    cout << "1. Create Election\n2. Add Candidate\n3. Register voter\nEnter Choice: ";
    cin >> choice;
    switch (choice)
    {
    case 1: {
        a.createElection();
        break;
    }
    case 3: {
        election temp;
        char n = 'y';
        while (n == 'y' || n == 'Y') {
            temp.adminAssignCodesFlow(); // assign codes to registered voters
            temp.saveVotersToFile("Voter.txt");
            cout << "Assign more codes? (y/n): ";
            cin >> n;
        }
        break;
    }

    default: {
        cout << "Invalid choice. Try again.\n";
        break;
    }
    }
}
