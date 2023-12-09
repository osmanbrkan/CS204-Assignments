//
// Created by Osman Berk An on 9.05.2023.
//

#ifndef TAKE_HOME_5_BOARD_H
#define TAKE_HOME_5_BOARD_H

#include <string>
#include <iostream>
using namespace std;


struct Node {
    string owner;
    Node* next;
    Node () {
        owner = "None";
        next = nullptr;
    }
    Node(string &o, Node* p) {  // not necessary because I made its implementation in default and I used it in other functions
        owner = o;
        next = p;
    }

};

class Board {
private:
    Node* first;

public:
     Board(int  numSlot); //constructor
    ~Board(); //destructor
    string who_owns(Node*p) const;  // who owns current slot
    Node* get_first() const ;  // get the first node
    void display() const; // display the board
    Board(const Board& copy); // deep copy
    const Board & operator = (const Board &rhs);  // assignment op
};


#endif //TAKE_HOME_5_BOARD_H

