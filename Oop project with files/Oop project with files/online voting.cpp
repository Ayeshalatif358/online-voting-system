#include<iostream>
#include<string>
#include"user.h"
#include"voter.h"
#include"candidate.h"
#include"admin.h"
#include"local.h"
#include"constituency.h"
#include"election.h"
#include"general.h"
#include"national.h"
using namespace std;
void menu(admin& A);
void elections();
void admin_menu();
int main()
{
    admin a;
    a.createElection();
    election E;
    char ch='Y';
    while (ch == 'Y' || ch == 'y')
    {
        E.addCandidate();
        cout << "Enter 'Y' or 'y' to add candidate: ";
        cin >> ch;
    }
    E.showCand();
    a.addCandidateMPA();
    //general_election E1;

    return 0;
}
void menu(admin& A)
{
    int choice;
    cout << "1. Admin\n2. Candidate\n3. Voter\nEner choice";
    cin >> choice;
    switch (choice)
    {
    case 1:
    {
        cin >> A;
        admin_menu();
        break;
    }
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
void admin_menu()
{
    int choice;
    cout << "1. Create Election\n2. Add Candidate\nEnter Choice: ";
    cin >> choice;
    switch (choice)
    {
    case 1:

        break;
    }
}