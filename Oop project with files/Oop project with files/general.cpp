#include<iostream>
#include<string>
#include"general.h"
using namespace std;

general_election::general_election(string l = " ", string p = "") :level(l), province(p) {}
void general_election::set_level(string l) { level = l; }
void general_election::set_province(string p) { province = p; }
string general_election::get_level() { return level; }
string general_election::get_province() { return province; }
string general_election::getposition() { return position; }