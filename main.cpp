#include<iostream>
#include<string>
#include"user.h"
#include"admin.h"
#include"general.h"
#include"local.h"
#include<fstream>
using namespace std;
void createFile(){
	ofstream in;
	in.open("Voter ID.txt");
	in << 0;
	in.close();
	in.open("MPA ID");
	in << 0;
	in.close();
	in.open("MNA ID");
	in << 0;
	in.close();
	in.open("Election ID.txt");
	in << 0;
	in.close();
}
int main()
{
	election e;
	cin >> e;
	voter v;
	cin >> v;
	//admin a;
	//cin >> a;
	//cout << a;
	return 0;
}