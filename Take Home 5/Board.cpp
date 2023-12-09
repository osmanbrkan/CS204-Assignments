//
// Created by Osman Berk An on 9.05.2023.
// OSMAN BERK AN 28849 TAKE-HOME 5

#include <iostream>
#include "Board.h"


Board::Board(int numSlot){  //constructor for Board,   numSLot >= 6
    first = new Node();
    Node* prev = first;
    for (int i = 1; i < numSlot; i++) {
        Node *curr = new Node();
        prev->next = curr;
        prev = curr;
    }
    prev->next = first;
}

Board::~Board() {  //destructor
    Node* curr = first->next;
    while (curr != first) {
        Node* temp = curr;
        curr = curr->next;
        delete temp;
    }
    delete first;

}

Board::Board(const Board &copy) {  // copy const just in case
    first = copy.first;

}


const Board &Board::operator=(const Board &rhs) {  //assignment op
    int count = 0;
    if(this != &rhs){
        Node* curr = first->next;
        while (curr != first) {
            count++;
            Node* temp = curr;
            curr = curr->next;
            delete temp;

        }
        delete first;
        count = count + 1; //number of slots

    }
    first = new Node();
    Node* prev = first;
    for (int i = 0; i < count; i++) {
        Node *curr = new Node();
        prev->next = curr;
        prev = curr;
    }
    prev->next = first;
    return *this;

}

string Board:: who_owns(Node* p) const {
    return p->owner;
}

Node* Board::get_first() const{  // useful for player class implementations
    return first;
}

void Board::display() const{

    int count= 0;
    Node * cur = first;
    do {    // counting and output the elements in circular linked list
        count++;
        if(cur->owner.length() == 3 && cur->next != first){ //for Ali and Liz
            cout << cur->owner << " ->";
        }
        else if(cur->owner.length() == 4 && cur->next != first) {  //For None
            cout << cur->owner << "->";
        }
        else if(cur->owner.length() == 3 && cur->next == first){  // because after last player there is no ->
            cout << cur->owner;
        }
        else if(cur->owner.length() == 4 && cur->next == first){
            cout << cur->owner;
        }
        cur = cur->next; //advance to the next line
    } while (cur != first);

    int row1length; // f.e  (if count = 6   length = 34 ,  if count = 7     length = 40)
    row1length = ((count-1) * 6) + 4;  // f.e None->None->None
    cout << endl;

    // 2nd row of the board
    cout << "^";
    for(int i=0; i<row1length-2; i++){
        cout << " ";
    }
    cout << "|";
    cout << endl;


    // 3rd row of the board
    cout << "|----";
    for(int j=0; j<count-2; j++){
        cout << "<-----";
    }
    cout << "<---v";
    cout << endl;


}





