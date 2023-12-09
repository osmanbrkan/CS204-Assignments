//
// Created by Osman Berk An on 18.04.2023.
// TAKE HOME 4


#ifndef TAKE_HOME_4_LAST_SCHEDULE_H
#define TAKE_HOME_4_LAST_SCHEDULE_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum Days{Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday};

class Schedule {
private:
    int time_slots;   //num of col
    string** data;


public:
    Schedule();
    Schedule(int c);
    ~Schedule();
    Schedule(const Schedule& copy); // deep copy

    //operator overloading
    const Schedule & operator = (const Schedule &rhs);
    Schedule  operator + (const Days &day);
    Schedule  operator + (int time_slot);
    Schedule  operator + (const Schedule &rhs);
    Schedule  operator * (const Schedule &rhs);
    string* operator [] (const Days &day) const;
    bool operator < (const Schedule & rhs);
    int get_time_slot() const;   //getter
    string get_data(int i, int j) const; //getter





};
ostream & operator << (ostream &output, const Schedule & rhs);  //free
ostream & operator << (ostream &output, const Days &day);   // free



#endif //TAKE_HOME_4_LAST_SCHEDULE_H
