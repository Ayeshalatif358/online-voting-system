#pragma once
#ifndef Date_H
#define Date_H
#include<iostream>
#include<string>
#include "user.h"
using namespace std;
class date
{
private:
    int day, month, year;
public:
    date();
    // Operator >=
    bool operator>=(const date& other) const;

    // Operator <=
    bool operator<=(const date& other) const;
    friend istream& operator>>(istream& in, date& d);
    friend ostream& operator<<(ostream& out, const date& d);
    void setMonth(int m);
    void setDay(int d);
    void setYear(int y);
    void setDate(int d, int m, int y);
    // Getters
    int getDay() const;
    int getMonth() const;
    int getYear() const;
};
#endif