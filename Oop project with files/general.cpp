#include<iostream>
#include<string>
#include"candidate.h"
#include"general.h"
using namespace std;
int max_candidate = 10;
general_election::general_election(string l = " ", string p = "") :level(l), province(p) {}
void general_election::set_level(string l) { level = l; }
void general_election::set_province(string p) { province = p; }
string general_election::get_level() { return level; }
string general_election::get_province() { return province; }
string general_election::getposition() { return position; }
void general_election ::addCandidate(candidate* c) {
    if (candidate_count < max_candidate) {
        C[candidate_count++] = c;
    }
    else {
        cout << "Local election candidate limit reached.\n";
    }
}
candidate general_election::getWinner() {
    int maxVotes = -1;
    int winnerIndex = -1;
    for (int i = 0; i < candidate_count; i++) {
        if (C[i]->getnoOfvotes() > maxVotes) {
            maxVotes = C[i]->getnoOfvotes();
            winnerIndex = i;
        }
    }
    return *C[winnerIndex];
}