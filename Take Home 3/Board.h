//
// Created by Osman Berk An on 4.04.2023.
//

#ifndef TAKE_HOME_3_BOARD_H
#define TAKE_HOME_3_BOARD_H


#include "CharStack.h"

struct slot
{
    slot * next = nullptr;
    slot * prev = nullptr;
    CharStack slotStack;
    slot ()
    {}
};

class Board {
private:
    slot * head;
    slot * tail;
    int xCnt;
    int oCnt;

public:
    Board();   //default constructor
    int evaluateGame() const ;  // evaluate the number of pieces (x or o) which one is more
    void createSlotBegin(char ch, int num);
    void createSlotEnd(char ch, int num);
    void createEmptySlotEnd();
    bool targetSlotFull(int index); // returns true if target slot is full
    void destroySlot(int index);  // destroy the given indexed slot
    void clearBoard();  // delete all slots
    void printBoard();
    bool noMove(char player, int steps) ; // steps is die no // It returns true, if there is no possible valid move of that player; returns false otherwise
    int validMove(char player, int startIndex, int steps, int direction );
    void movePiece(int source, int target);

};


#endif //TAKE_HOME_3_BOARD_H
