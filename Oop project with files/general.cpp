#include<iostream>
#include<string>
#include<fstream>
#include<windows.h>
#include"general.h"

general_election::general_election()
{
    C = nullptr;
    candidate_no = 0;
    mpa_count = 0;
}
int general_election::check(string n)
{
    int k = 0;
    for (int j = 0; j < candidate_no; j++)
    {
        if (C[j]->getcons().getNcode() == n) {
            k++;
            if (k > 2) {
                return -1;
            } 
        }
    }
    return -3;
}
int general_election::checkcandexist(string n, string filename)
{
    select_cand();
    for (int i = 0; i < candidate_no; i++) {
        for (int j = i; j < candidate_no; j++) {
            if (C[i]->getcons().getcode() == n) {
                return i;
            }
        }
    }
    return -1;
}
Code* general_election::getUniquecode() {
    if (C == nullptr) {
        addCandidate("MPA DATA.txt");
    }

    Code* allCodes = new Code[candidate_no];
    for (int i = 0; i < candidate_no; i++) {
        if (C[i] != nullptr) {
            allCodes[i] = C[i]->getcons();
        }
        else {
            allCodes[i] = Code();
        }
    }

    // Mark duplicates as "-1"
    for (int i = 0; i < candidate_no; i++) {
        if (allCodes[i].getcode() == "-1") continue;
        for (int j = i + 1; j < candidate_no; j++) {
            if (allCodes[i] == allCodes[j]) {
                allCodes[j].setcode("-1");
            }
        }
    }

    // Count unique codes
    int uniqueCount = 0;
    for (int i = 0; i < candidate_no; i++) {
        if (allCodes[i].getcode() != "-1") {
            uniqueCount++;
        }
    }

    Code* uniqueCodes = new Code[uniqueCount + 1]; // +1 for "#"
    int idx = 0;
    for (int i = 0; i < candidate_no; i++) {
        if (allCodes[i].getcode() != "-1") {
            uniqueCodes[idx++] = allCodes[i];
        }
    }

    uniqueCodes[idx].setcode("#"); // Sentinel

    delete[] allCodes;
    return uniqueCodes;
}


void general_election::select_cand() {
    Code* uniqueCons = getUniquecode();

    int len = 0;
    while (uniqueCons[len].getcode() != "#") {
        len++;
    }

    int* index = new int[len];
    for (int i = 0; i < len; i++) {
        int maxVotes = -1;
        int maxIndex = -1;

        for (int j = 0; j < candidate_no; j++) {
            if (C[j] != nullptr && C[j]->getcons().getcode() == uniqueCons[i].getcode()) {
                if (C[j]->getnoOfvotes() > maxVotes) {
                    maxVotes = C[j]->getnoOfvotes();
                    maxIndex = j;
                }
            }
        }
        index[i] = maxIndex;
    }

    // Clean previous winCode if necessary
    if (winCode != nullptr) {
        delete[] winCode;
    }

    winCode = new Code[len];
    ofstream write("Winner_MPA.txt", ios::app);
    if (!write.is_open()) {
        cout << "Error opening file!!\n";
    }
    else {
        cout << "Winners per constituency:\n";
        for (int i = 0; i < len; i++) {
            if (index[i] != -1 && C[index[i]] != nullptr) {
                winCode[i] = C[index[i]]->getcons();
                // Save full winner info to file
                write << "Constituency Code: " << winCode[i].getcode()
                    << ", Winner: " << C[index[i]]->getName()
                    << ", ID: " << C[index[i]]->getc_id()
                    << ", Votes: " << C[index[i]]->getnoOfvotes() << "\n";

                // Also print to console
                cout << "Code: " << winCode[i].getcode()
                    << ", Winner: " << C[index[i]]->getName()
                    << ", ID: " << C[index[i]]->getc_id()
                    << ", Votes: " << C[index[i]]->getnoOfvotes() << "\n";
            }
        }
        write.close();
    }

    // Call function to process winners file
    winnerCand("Winner_MPA.txt");

    delete[] uniqueCons;
    delete[] index;
}


void general_election::assignCode() {
    if (C == nullptr) {
        addCandidate("MPA DATA.txt");
    }
    outputCand();

    string c;
    for (int i = 0; i < candidate_no; i++) {
        // Safe: check if candidate is initialized
        if (C[i] == nullptr) {
            cout << "Error: Candidate at index " << i << " is not initialized!\n";
            continue; // skip this candidate
        }

        if (C[i]->getcons().getcode() == "null") {
            cout << "For MPA having ID: " << C[i]->getc_id() << endl;
            cout << "Enter constituency code: ";
            cin >> c;
            system("cls");
            Sleep(500);
            // Safe check using fixed checkCity
            while (checkCity(c, i) == -1) {
                cout << "Candidates of same party and area cannot have same constituency code!!\n";
                cout << "Enter constituency code again: ";
                cin >> c;
                system("cls");
                Sleep(500);
            }
            while (checkCity(c, i) == -2) {
                cout << "Candidates of different parties and same area should have same constituency code!!\n";
                cout << "Enter constituency code again: ";
                cin >> c;
                system("cls");
                Sleep(500);
            }
            C[i]->setcode(c);
        }
    }

    inputalldata("MPA DATA.txt");
}

void general_election::assignMpa(string n, int i) {
    C[i]->setNcode(n);
    inputalldata("MPA DATA.txt");
}


void general_election::showCandidates(string code) {
    char n;
    if (C == nullptr || candidate_no <= 0) {
        addCandidate("MPA DATA.txt");


    }


    if (C == nullptr || candidate_no <= 0) {
        cout << "No candidates loaded.\n";
        cout << "Press any key to proceed: ";
        cin >> n;
        system("cls");
        Sleep(500);
        return;
    }

    cout << "Looking for candidates with code: " << code << "\n";

    bool found = false;
    for (int i = 0; i < candidate_no; i++) {
        if (C[i] && C[i]->getcons().getcode() == code) {
            cout << "-------Candidate No. " << i + 1 << "------- : \n" <<"CID: " << C[i]->getc_id() << endl
                << "Name: " << C[i]->getName() << endl
                << "Bio: " << C[i]->getBio() << endl
                << "Area: " << C[i]->getArea() << endl
                << "Cnic: " << C[i]->getcnic() << endl
                << "Party: " << C[i]->getParty() << endl
                << "Position: " << C[i]->getPosition() << endl
                << "-----------------------------------\n";

            found = true;
        }
    }

    if (!found) {
        cout << "No candidates found with code: " << code << "\n";
        cout << "Press any key to proceed: ";
        cin >> n;
        system("cls");
        Sleep(500);
    }
}


void general_election::castVote(voter* v) {
    char n;
    if (v->getPhasvoted()) {
        cout << "You have already voted for MPA.\n";
        cout << "Press any key to proceed: ";
        cin >> n;
        system("cls");
        Sleep(500);
        return;
    }
    cout << "Showing candidates for MPA : \n";
    cout << "\n\n";
    general_election::showCandidates(v->getVoterCode().getcode());
    int choice;
    // Example vote casting:

    for (int i = 0; i < candidate_no; i++) {
        cout << "Enter candidate id to vote for: ";
        cin >> choice;
        system("cls");
        Sleep(500);
        if (choice == C[i]->getc_id() && v->getVoterCode().getcode() == C[i]->getcons().getcode()) {
            cout << "You want to vote for candidate with id: " << C[i]->getc_id() << endl;
            bool confirm;
            cout << "press 1 to confirm. press 0 to discard\n Enter choice: "; cin >> confirm;
            system("cls");
            Sleep(500);
            if (confirm) {
                C[choice - 1]->addVote();
                v->setPhasvoted(1);
                cout << "Vote cast successfully!\n";
                cout << "Press any key to proceed: ";
                cin >> n;
                system("cls");
                Sleep(500);
                break;
            }
        }
        else {
            cout << "Invalid choice\n";
            cout << "Press any key to proceed: ";
            cin >> n;
            system("cls");
            Sleep(500);
        }
    }
    this->inputalldata("MPA DATA.txt");
}

void general_election::viewVoteCountIfElectionEnded(const date& today) {
    char n;
    if (today <= endDate) {
        cout << "Election is still ongoing or hasn't ended yet. Vote counts will be visible after "
            << get_endDate() << ".\n";
        cout << "Press any key to proceed: ";
        cin >> n;
        system("cls");
        Sleep(500);
        return;
    }
    this->addCandidate("MPA DATA.txt");
    if (C == nullptr || candidate_no == 0) {
        cout << "No candidates to display.\n";
        cout << "Press any key to proceed: ";
        cin >> n;
        system("cls");
        Sleep(500);
        return;
    }

    cout << "\n--- Vote Count for All Candidates ---\n";
    for (int i = 0; i < candidate_no; i++) {
        if (C[i]) {
            cout << i + 1 << ". " << C[i]->getName()
                << " (" << C[i]->getParty() << ") - "
                << C[i]->getnoOfvotes() << " votes\n";
        }
    }
    cout << "--------------------------------------\n";
}