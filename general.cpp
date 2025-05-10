#include<iostream>
#include<string>
#include<fstream>
#include"general.h"
general_election::general_election()
{
    C = nullptr;
    candidate_no = 0;
}
int general_election::check(string n)
{
    int k = 0;
    string temp;
    for (int j = 0; j < candidate_no; j++)
    {
        if (C[j]->getPosition() == "MPA" || C[j]->getPosition() == "mpa")
        {
            if (C[j]->getcons().getNcode() == n) {
                k++;
                if (k > 2) {
                    return -1;
                }
                else if (k < 2) {
                    return -2;
                }
            }
        }
    }
    return -3;
}
Code* general_election::getUniquecode()
{
    int k = 0;
    Code* s = new Code[candidate_no];
    Code* S;
    for (int i = 0; i < candidate_no; i++)
    {
        s[i] = C[i]->getcons();
    }
    for (int i = 0; i < candidate_no; i++)
    {
        for (int j = i + 1; j < candidate_no; j++)
        {
            if (C[i]->getcons() == C[j]->getcons() && s[i].getcode() != "-1" && s[j].getcode() != "-1")
            {
                s[j].setcode("-1");
                k++;
            }
        }
    }
    S = new Code[k + 1];
    for (int i = 0; i < k; i++)
    {
        if (s[i].getcode() != "-1")
        {
            S[i] = s[i];
        }
    }
    S[k].setcode("#");
    return S;
}

void general_election::select_mpa()
{
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
            if (C[j]->getcons().getcode() == uniqueCons[i].getcode()) {
                if (C[j]->getnoOfvotes() > maxVotes) {
                    maxVotes = C[j]->getnoOfvotes();
                    maxIndex = j;
                }
            }
        }
        index[i] = maxIndex;
    }
    winCode = new Code[len];
    for (int i = 0; i < len; i++) {
        winCode[i] = C[index[i]]->getcons();
    }
    delete[] uniqueCons;
    delete[] index;
    ofstream write;
    write.open("Winner MPA", ios::app);
    if (!write.is_open()) {
        cout << "Error opening file!!\n";
    }
    for (int i = 0; i < len; i++) {
        write << winCode[i] << endl;
    }
}


void general_election::assignCodeToMPA() {
    if (C == nullptr) {
        addCandidate("MPA DATA");
    }
    string line, pos;
    ofstream write("Candidate", ios::app);
    if (!write.is_open()) {
        cout << "Error opening file!!\n";
    }
    ifstream read("Candidate");
    string c, n;
    for (int i = 0; i < candidate_no; i++) {
        if (C[i]->getcons().getcode() == "") {
            cout << "For MPA having CNIC: " << C[i]->getc_id() << endl;
            cout << "Enter constituency code: ";
            cin >> c;
            while (checkCity(c, i) == -1) {
                cout << "Candidates having same area should have same constituency code!!\n";
                cout << "Enter constituency code again: ";
                cin >> c;
            }
            C[i]->setcode(c);
            C[i]->inputWholeData("MPA DATA");
        }
    }
}
string general_election::nationalCode() {
    string n;
    cout << "Enter national code: ";
    cin >> n;
    return n;
}
void general_election::assignMpa(string n, int i) {
    C[i]->setNcode(n);
}


void general_election::showCandidatesMPA(string code) {
    addCandidate("MPA DATA");
    for (int i = 0; i < candidate_no; i++) {
        if (C[i]->getcons().getcode() == code) {
            cout << i + 1 << " : " << C[i];
        }
    }
}
void general_election::castVoteP(voter* v) {
    if (v->getPhasvoted()) {
        cout << "You have already voted.\n";
        return;
    }

    cout << "Showing candidates for MPA Code: \n";

    showCandidatesMPA(v->getVoterCode().getcode());
    int choice;
    // Example vote casting:

    for (int i = 0; i < candidate_no; i++) {
        cout << "Enter candidate id to vote for: ";
        cin >> choice;
        if (choice == C[i]->getc_id() && v->getVoterCode().getcode() == C[i]->getcons().getcode()) {
            cout << "you want to vote for candidate with id: " << C[i]->getc_id();
            bool confirm;
            cout << "press 1 to confirm. press 0 to discard\n Enter choice: "; cin >> confirm;
            if (confirm) {
                C[choice - 1]->addVote();
                v->setPhasvoted(true);
                cout << "Vote cast successfully!\n";
                break;
            }
        }
        else {
            cout << "Invalid choice\n";
        }
    }

}