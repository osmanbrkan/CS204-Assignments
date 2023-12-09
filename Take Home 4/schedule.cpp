//
// Created by Osman Berk An on 18.04.2023.
// OSMAN BERK AN 28849 TAKE_HOME 4

#include "schedule.h"

using namespace std;

Schedule::Schedule() {
     time_slots = 0;
     data = new string*[7];
     for (int i = 0; i < 7; i++) {
        data[i] = nullptr;  //NULL
     }
}

Schedule::Schedule(int c) {
    time_slots = c;
    data = new string*[7];

    for(int i=0; i<7; i++){
        data[i] = new string[c];
        for(int j=0; j<c; j++){
            data[i][j] = "free";
        }
    }
}

Schedule::Schedule(const Schedule &oth) {
    time_slots = oth.time_slots;  // copy the column number
    data = new string*[7];
    for(int i=0; i<7; i++){
        data[i] = new string[time_slots];
        for(int j=0; j<time_slots; j++) {
            data[i][j] = oth.data[i][j];
        }

    }

}

Schedule::~Schedule() {
    for (int i = 0; i < 7; i++) {
        delete[] data[i];
    }
    delete[] data;
}


const Schedule & Schedule :: operator = (const Schedule & rhs) {

    if(this != &rhs){
        for(int i=0; i<7; i++){
            delete [] data[i];
        }
        delete [] data;
        time_slots = rhs.time_slots;
        data = new string*[7];
        for (int i = 0; i < 7; i++) {
            data[i] = new string[time_slots];
        }
        for (int i = 0; i < 7; ++i) {
            for (int j = 0; j < time_slots; j++) {
                data[i][j] = rhs.data[i][j];
            }
        }

    }
    return *this;
}

Schedule  Schedule::operator+(const Days &day)  { //day is rhs

    // enum Days{Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday};

    Schedule result(*this); //lhs
    for(int i=0; i<result.time_slots; i++) {
        result.data[day][i] = "busy";
    }
    return result;
}


Schedule  Schedule::operator+(int time_slot) {
    Schedule new_schedule(*this);
    for(int i=0; i<7; i++){
        new_schedule.data[i][time_slot] = "busy";
    }
    return new_schedule;  // not a reference because we return local variable
}


Schedule Schedule::operator+(const Schedule &rhs) {

    Schedule lhs(*this);
    Schedule result(rhs.time_slots);
    for(int i=0; i<7;i++){
        for(int j=0; j<rhs.time_slots; j++) {
            if(lhs.data[i][j] == "free" && rhs.data[i][j] == "free"){
                result.data[i][j] = "free";
            }
            else
                result.data[i][j] = "busy";
        }
    }
    return result;

}

Schedule Schedule ::operator*(const Schedule &rhs) {  //opposite of upside +
    Schedule lhs(*this);
    Schedule result(rhs.time_slots);
    for(int i=0; i<7;i++){
        for(int j=0; j<rhs.time_slots; j++) {
            if(lhs.data[i][j] == "busy" && rhs.data[i][j] == "busy"){
                result.data[i][j] = "busy";
            }
            else
                result.data[i][j] = "free";
        }
    }
    return result;

}

string* Schedule::operator[](const Days &day) const {
    //Schedule lhs(*this);
    //return lhs.data[day];
    return data[day];

}


bool Schedule ::operator<(const Schedule &rhs) {
    Schedule lhs(*this);
    int busy_lhs = 0;
    int busy_rhs = 0;
    for(int i=0; i<7; i++){
        for(int j=0; j< time_slots; j++){
            if(data[i][j] == "busy"){
                busy_lhs++;
            }
        }
    }
    for(int k=0; k<7; k++){
        for(int l=0; l<rhs.time_slots; l++){
            if(rhs.data[k][l] == "busy"){
                busy_rhs++;
            }
        }
    }
    if(busy_lhs < busy_rhs){
        return true;
    }
    else
        return false;
}


int Schedule::get_time_slot() const {
    return time_slots;
}

string Schedule::get_data(int i, int j) const {
    return data[i][j];
}

ostream & operator << (ostream & output, const Schedule & rhs){ // free function
    for(int i=0; i<7; i++){
        if(Days(i) == Monday){
            output << "Mo: ";
        }
        else if(Days(i) == Tuesday){
            output << "Tu: ";
        }
        else if(Days(i) == Wednesday){
            output << "We: ";
        }
        else if(Days(i) == Thursday){
            output << "Th: ";
        }
        else if(Days(i) == Friday){
            output << "Fr: ";
        }
        else if(Days(i) == Saturday){
            output << "Sa: ";
        }
        else if(Days(i) == Sunday){
            output << "Su: ";
        }
        for(int j=0; j<rhs.get_time_slot(); j++) {
            output << rhs.get_data(i,j) << " ";
        }
        output << endl;
    }
    return output;
}

ostream & operator << (ostream & output, const Days& day){ //Free
   if(day == Monday){
       output << "Monday";
   }
   else if(day ==Tuesday){
       output << "Tuesday";
   }
   else if(day ==Wednesday){
       output << "Wednesday";
   }
   else if(day ==Thursday) {
       output << "Thursday";
   }
   else if(day ==Friday){
       output << "Friday";
   }
   else if(day ==Saturday){
       output << "Saturday";
   }
   else if(day ==Sunday){
       output << "Sunday";
   }
   return output;

}




