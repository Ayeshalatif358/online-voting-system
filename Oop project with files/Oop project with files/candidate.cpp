#include<iostream>
#include<string>
#include"candidate.h"
using namespace std;
int candidate::id = 0;
candidate::candidate()
{
	id = ++id;
	c_ID = id;
	name = "";
	party = "";
	area = "";
	position = "";
	noOfvotes = 0;
	bio = "";
}
void candidate::set_ID()
{
	c_ID = id;
}
istream& operator>>(istream& in, candidate& c) {
	cout << "Enter Candidate Name: ";
	getline(in >> ws, c.name);

	cout << "Enter Party: ";
	getline(in, c.party);

	cout << "Enter Area: ";
	getline(in, c.area);

	cout << "Enter Position: ";
	getline(in, c.position);

	cout << "Enter Bio: ";
	getline(in, c.bio);

	c.noOfvotes = 0;  // Reset votes when candidate is entered
	return in;
}
ostream& operator<<(ostream& out, const candidate& c) {
	out << "Candidate ID: " << c.id << endl;
	out << "Name: " << c.name << endl;
	out << "Party: " << c.party << endl;
	out << "Area: " << c.area << endl;
	out << "Position: " << c.position << endl;
	out << "Votes: " << c.noOfvotes << endl;
	out << "Bio: " << c.bio << endl;
	return out;
}


candidate::candidate(string n, string p, string a, string pos, int n_votes, string b)
{
	id = ++id;
	name = n;
	party = p;
	area = a;
	position = pos;
	noOfvotes = n_votes;
	bio = b;
}
void candidate::setName(string n) {
	name = n;
}
void candidate::setParty(string p) { party = p; }
void candidate::setArea(string a) { area = a; }
void candidate::setPosition(string p) { position = p; }
void candidate::setnoOfvotes(int n) { noOfvotes = n; }
void candidate::setBio(string b) { bio = b; }
string candidate::getName() const { return name; }
string candidate::getParty() const { return party; }
string candidate::getArea() const { return area; }
string candidate::getPosition() const { return position; }
int candidate::getnoOfvotes() const { return noOfvotes; }
string candidate::getBio() const { return bio; }
void candidate::setcandidate(string n, string p, string a, string P, string b, int no) {
	party = p; name = n;
	area = a; position = P;  noOfvotes = no;
	bio = b;
}
void candidate::addVote()
{
	noOfvotes++;
}