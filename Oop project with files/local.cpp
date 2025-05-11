#include<iostream>
#include<string>

#include<windows.h>
#include<fstream>
#include"local.h"
int local_election::getmnaCount()
{
    return mna_count;
}

Code* local_election::getUniquecode() {
    if (C == nullptr) {
        addCandidate("MNA DATA.txt");
    }

    Code* s = new Code[candidate_no];
    for (int i = 0; i < candidate_no; i++) {
        s[i] = C[i]->getcons();
    }

    // Mark duplicates with "-1"
    for (int i = 0; i < candidate_no; i++) {
        for (int j = i + 1; j < candidate_no; j++) {
            if (s[i] == s[j] && s[j].getcode() != "-1") {
                s[j].setcode("-1");
            }
        }
    }

    // Count unique codes
    int uniqueCount = 0;
    for (int i = 0; i < candidate_no; i++) {
        if (s[i].getcode() != "-1") {
            uniqueCount++;
        }
    }

    Code* S = new Code[uniqueCount + 1]; // +1 for sentinel
    int idx = 0;
    for (int i = 0; i < candidate_no; i++) {
        if (s[i].getcode() != "-1") {
            S[idx++] = s[i];
        }
    }

    S[uniqueCount].setcode("#"); // Sentinel
    delete[] s;
    return S;
}

void local_election::select_cand() {
    Code* uniqueCons = getUniquecode();
    int len = 0;
    while (uniqueCons[len].getcode() != "#") {
        len++;
    }

    mna_count = len;
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

    // Clean existing winCode memory
    if (winCode != nullptr) {
        delete[] winCode;
    }
    winCode = new Code[len];

    ofstream write("Winner MNA.txt", ios::app);
    if (!write.is_open()) {
        cout << "Error opening file!!\n";
        delete[] uniqueCons;
        delete[] index;
        return;
    }

    for (int i = 0; i < len; i++) {
        if (index[i] != -1 && C[index[i]] != nullptr) {
            winCode[i] = C[index[i]]->getcons();

            write << "Code: " << winCode[i].getcode() << endl;
            write << "NCode: " << winCode[i].getNcode() << endl;
            write << "Winner: " << C[index[i]]->getName() << endl;
            write << "ID: " << C[index[i]]->getc_id() << endl;
            write << "Votes: " << C[index[i]]->getnoOfvotes() << endl;
            write << "----------------------------\n";
        }
    }

    write.close();
    delete[] uniqueCons;
    delete[] index;
}

int local_election::checkcandexist(string n,string filename)
{
    select_cand();
    for (int i = 0; i < candidate_no; i++) {
        for (int j = i; j < candidate_no; j++) {
            if (C[i]->getcons().getNcode() == n) {
                return i;
            }
        }
    }
    return -1;
}

int local_election::MNcheck(int i, string n)
{
    int k = 0;
    for (int j = 0; j < i; j++)
    {
        if (C[j]->getcons().getNcode() == n) {
            k++;
            if (k > 1) {
                return -1;
            }
        }
        return -3;
    }
    return -2;
}
int local_election::MNcheckCons(int i, string c)
{
    int k = 0;
    for (int j = 0; j < i; j++)
    {
        if (C[j]->getcons().getcode() == c) {
            k++;
            if (k > 1) {
                return -2;
            }
        }
    }
    return -3;
}
void local_election::assignCode() {
    if (C == nullptr) {
        addCandidate("MNA DATA.txt");
    }
    outputCand();

    string line, pos;

    for (int i = 0; i < candidate_no; i++) {
        if (C[i]->getcons().getcode() == "null") {
            string c, n;
            cout << "For MNA having ID: " << C[i]->getc_id() << endl;

            cout << "Enter constituency code: ";
            cin >> c;

            cout << "Enter national code: ";
            cin >> n;
            system("cls");
            Sleep(500);
            while (MNcheck(i, n) == -1) {
                cout << "National Code of MNA must be unique!!\nEnter National Code again: ";
                cin >> n;
            }

            C[i]->setcode(c);
            C[i]->setNcode(n);
        }
        else continue;
    }
    inputalldata("MNA DATA.txt");
}
void local_election::showCandidates(string code) {
    char n;
    if (C == nullptr || candidate_no <= 0) {
        addCandidate("MNA DATA.txt");


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
            cout << "-------Candidate No. " << i + 1 << "------- : \n" << "CID: " << C[i]->getc_id() << endl
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



void local_election::castVote(voter* v) {
    if (v->getNhasvoted()) {
        cout << "You have already voted.\n";
        return;
    }

    cout << "Showing candidates for MNA Code: \n";

    local_election::showCandidates(v->getVoterCode().getNcode());
    int choice;
    // Example vote casting:

    for (int i = 0; i < candidate_no; i++) {
        cout << "Enter candidate id to vote for: ";
        cin >> choice;
        if (choice == C[i]->getc_id() && v->getVoterCode().getNcode() == C[i]->getcons().getcode()) {
            cout << "you want to vote for candidate with id: " << C[i]->getc_id();
            bool confirm;
            cout << "press 1 to confirm. press 0 to discard\n Enter choice: "; cin >> confirm;
            if (confirm) {
                C[choice - 1]->addVote();
                v->setNhasvoted(true);
                cout << "Vote cast successfully!\n";
                break;
            }
        }
        else {
            cout << "Invalid choice\n";
        }
    }
    inputalldata("MNA DATA.txt");
}
