#include<iostream>
#include<string>
#include"admin.h"
#include<fstream>
#include"date.h"
using namespace std;
date::date()
{
    day = 0;
    month = 0;
    year = 0;
}
bool date::operator>=(const date& other) const {
    if (year > other.year) return true;
    if (year == other.year && month > other.month) return true;
    if (year == other.year && month == other.month && day >= other.day) return true;
    return false;
}
bool date::operator<=(const date& other) const {
    if (year < other.year) return true;
    if (year == other.year && month < other.month) return true;
    if (year == other.year && month == other.month && day <= other.day) return true;
    return false;
}
int date::getYear() const {
    return year;
}
int date::getMonth() const {
    return month;
}
int date::getDay() const {
    return day;
}
void date::setDate(int d, int m, int y) {
    day = d;
    month = m;
    year = y;
}
void date::setYear(int y) {
    year = y;
}
void date::setDay(int d) {
    day = d;
}
void date::setMonth(int m) {
    month = m;
}
istream& operator>>(istream& in, date& d)
{
    cout << "Enter day: ";
    in >> d.day;
    cout << "Enter month: ";
    in >> d.month;
    cout << "Enter year: ";
    in >> d.year;
    return in;
}
ostream& operator<<(ostream& out, const date& d)
{
    out << d.day << " - " << d.month << " - " << d.year << " - \n";
    return out;
}