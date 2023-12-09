//
// Created by Osman Berk An on 4.04.2023.
// Take Home 3  Osman Berk An 28849

#include <iostream>
#include "Board.h"
#include <string>
#include <vector>

using namespace std;


Board::Board(){
    head = nullptr;
    tail = nullptr;
    xCnt = 0;
    oCnt = 0;
}

int Board::evaluateGame() const {
    if (xCnt < oCnt) {
        return 1;
    } else if (oCnt < xCnt) {
        return 2;
    } else {
        return 3;
    }
}

void Board::createSlotBegin(char ch, int num) {

    slot* newStack = new slot();

    for (int i = 0; i < num; i++) {
        newStack->slotStack.push(ch);
    }

    // update piece counts
    if(ch == 'x'){
        xCnt += num;

    }
    else if(ch == 'o'){
        oCnt += num;
    }

    // update head of the linked list  // head will be newStack
    if(head == nullptr){
        head = newStack;
        tail = newStack;
    }
    else{
        head->prev = newStack;
        newStack->next = head;
        head = newStack;
    }

}

void Board::createSlotEnd(char ch, int num){ //must be new tail
    slot* newStack = new slot();

    for(int i=0; i<num; i++){
        newStack->slotStack.push(ch);

    }
    if(ch == 'x'){  // piece counts
        xCnt += num;
    }
    else if(ch == 'o'){
        oCnt += num;
    }

    if(head == nullptr){  // if there is no slot before
        head = newStack;
        tail = newStack;
    }
    else{
        tail->next = newStack;
        newStack->prev = tail;
        tail = newStack;
    }

}

void Board::createEmptySlotEnd() {
    slot* newSlot = new slot();


    if (head == nullptr) {  // if there is no stack before
        head = newSlot;
        tail = newSlot;
    }
    else {
        tail->next = newSlot;
        newSlot->prev = tail;
        tail = newSlot;
    }

}

bool Board::targetSlotFull(int index) {
    slot* curr = head;
    for (int i = 0; i < index; i++) {
        curr = curr->next;
    }
    if(curr->slotStack.isFull()){
        return true;
    }
    else
        return false;

}

void Board::destroySlot(int index) {  //destroy all slot not just elements
    slot* current = head;
    for(int i=0; i<index; i++){
        current = current->next;
    }

    char ch;
    while (!current->slotStack.isEmpty())  // loop goes all elements of stack and pop them out to check pop out x or o
    {
        current->slotStack.pop(ch);
        if(ch == 'x'){
            xCnt--;
        }
        else
            oCnt--;
    }

    if (current == head && current == tail) {  // If the slot is the only one in the list
        delete current;
        head = nullptr;
        tail = nullptr;
    }
    else if (current == head && current != tail) {  // If the slot is the head of the list
        head = current->next;
        delete current;
        head->prev = nullptr;
    }
    else if (current == tail && current != head) {  // If the slot is the tail of the list
        tail = current->prev;
        delete current;
        tail->next = nullptr;
    }
    else if(current != tail && current != head) {  // If the slot is in the middle of the list
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
    }

}

void Board::clearBoard() {
    slot * current = head;

    while(current->next != nullptr){
        current = current->next;
        delete current->prev;
    }
    delete current;

    head = nullptr;
    tail = nullptr;
    xCnt = 0;
    oCnt = 0;
}

void Board::printBoard() {

    slot* curr= head;
    string row[4];
    int slotNumb= 0;
    while (curr!= nullptr){
        int count = 0;
        slotNumb++;
        char ch;
        while (!curr->slotStack.isEmpty()){
            curr->slotStack.pop(ch);
            count++;
        }
        for (int c = 0; c < count ; c ++){
            curr->slotStack.push(ch);
        }

        for (int i = 0; i < count ; i ++){
            row[i] += ch;
        }
        for (int i = count; i < 3 ; i ++){
            row[i] += " ";
        }
        curr = curr->next;

    }
    cout << endl;
    cout << row[2] <<endl;
    cout << row[1] <<endl;
    cout << row[0] <<endl;

    for(int l=0; l<slotNumb; l++){
        row[3] += '^';
    }
    cout << row[3] <<endl;

}

bool Board::noMove(char player, int steps) {  // player x or o
    // returns true if there is no move

    slot * curr = head;

    int forwardTrue = 0;
    int backwardTrue = 0;

    while(curr != nullptr){
        slot * forSlot = curr;
        slot * backSlot = curr;
        char ch;
        if(!curr->slotStack.isEmpty()){
            curr->slotStack.pop(ch);
            curr->slotStack.push(ch);
            if(ch == player){
                //forward
                char xo;
                for(int i=0; i<steps;i++) {
                    forSlot = forSlot->next;
                    if (forSlot == nullptr) {
                        break;
                    }
                }
                if( forSlot != nullptr ){
                    if(!forSlot->slotStack.isEmpty()){
                        forSlot->slotStack.pop(xo);
                        forSlot->slotStack.push(xo);
                        if(xo == player){

                            forwardTrue++;
                        }
                    }
                    else{

                        forwardTrue++;
                    }
                }

                // backward
                for(int j=0; j<steps;j++){
                    backSlot = backSlot->prev;
                    if(backSlot == nullptr){
                        break;
                    }
                }
                if(backSlot != nullptr){
                    if(!backSlot->slotStack.isEmpty()){
                        backSlot->slotStack.pop(xo);
                        backSlot->slotStack.push(xo);
                        if(xo == player){

                            backwardTrue++;
                        }
                    }
                    else{

                        backwardTrue++;
                    }
                }
            }
        }
        curr = curr->next;
    }
    if(forwardTrue == 0 && backwardTrue == 0){  // there is no move
        return true;
    }
    else
        return false;

}

int Board::validMove(char player, int startIndex, int steps, int direction) {
    /* check four things:
        1. Entered slot index is not within bounds.  // return 1
2. Target slot index not within bounds. // return 2
3. Target slot index is not empty or does not belong to the player. // return 3
4. Entered slot index does not belong to the player.*/  // return 4
    // if move is valid return 0

    //error 1
    slot * curr = head;
    int count = 0;
    while(curr != nullptr){
        count++;

        curr = curr->next;
    }
    if(startIndex >= count){
        return 1;
    }

    // error 4
    slot * startSlot = head;
    for(int i=0; i<startIndex; i++){
        startSlot = startSlot->next;
    }
    if(startSlot->slotStack.isEmpty()){
        return 4;
    }
    char ch;
    startSlot->slotStack.pop(ch);  // pop to check the element is x or o
    startSlot->slotStack.push(ch);
    if(ch != player){
        return 4;
    }

    // error 2
    slot * current = head;
    slot * targetSlot = current;
    for(int k=0; k<startIndex;k++){
        current= current->next;
    }
    targetSlot = current;
    for(int j =0; j<steps; j++){
        if(direction == 0){

            targetSlot = targetSlot->prev;
            if(targetSlot == nullptr){
                return 2;
            }
        }
        else if(direction == 1){
            targetSlot = targetSlot->next;
            if(targetSlot == nullptr){
                return 2;
            }
        }

    }



    // error 3
    slot * start = head;
    slot * target = start;
    for(int k=0; k<startIndex;k++){
        start = start->next;
    }
    target = start;

    for(int i=0; i<steps; i++){
        if(direction == 0){
            target = target->prev;
        }
        else if(direction == 1){
            target = target->next;
        }
    }
    if(!targetSlot->slotStack.isEmpty()){
        char xo;
        targetSlot->slotStack.pop(xo);
        targetSlot->slotStack.push(xo);
        if(xo != player){
            return 3;
        }
    }



    return 0;

}

void Board::movePiece(int source, int target) {
    slot * sourceSlot = head;
    slot * targetSlot = head;
    for(int i=0; i<source; i++){
        sourceSlot = sourceSlot->next;
    }
    for(int j=0; j<target; j++) {
        targetSlot = targetSlot->next;
    }
    char ch;
    sourceSlot->slotStack.pop(ch);
    targetSlot->slotStack.push(ch);

}







