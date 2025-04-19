#include"user.h"
#include<iostream>
#include<string>
using namespace std;
user::user(int c, string n, string p) :cnic(c), name(n), password(p) {}
void user::inputUserData() {
    cout << "Enter CNIC: ";
    cin >> cnic;
    cout << "Enter Name: ";
    getline(cin >> ws, name); // ws to skip leading whitespace
    cout << "Enter Password: ";
    getline(cin, password);
}
void user::outputUserData() const {
    cout << "CNIC: " << cnic << endl;
    cout << "Name: " << name << endl;
    cout << "Password: " << password << endl;
}
int user::getcnic() { return cnic; };
string user::getname()const { return name; }
string user::getpass()const { return password; }
void user::setcnic(int c) { cnic = c; }
void user::setname(string n) { name = n; }
void user::setpass(string n) { password = n; }