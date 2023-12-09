//
// Created by Osman Berk An on 9.05.2023.
// OSMAN BERK AN 28849 TAKE-HOME 5

#include "Player.h"

#include <iostream>

using namespace std;


Player::Player(Board &board, string name, int c): player_balance(c), player_name(name), myBoard(board),
position(board.get_first()) {}  // constructor with shared Board object


int Player::get_balance() const{
    return player_balance;
}

bool Player::is_bankrupt() const {
    if(player_balance < 0){
        return true;
    }
    else
        return false;
}

Node* Player::where_am_I() const{  // current position
    return position;
}

void Player::deposit_money(int money) {
    player_balance = player_balance + money;
}

void Player::buy_slot(int price) {
    if (player_balance >= price) {
        position->owner = player_name;
        player_balance -= price;
    }

}

int Player::move(int steps) {   // returns 1 if player passed the starting slot else 0
    bool passed_by_start = false;
    for (int i = 0; i < steps; i++) {
        position = position->next;
        if (position == myBoard.get_first()) {
            passed_by_start = true;
        }
    }

    if(passed_by_start){
        return 1;
    }
    else{
        return 0;
    }

}

void Player::pay_to_player(Player& otherPlayer, int money) {
    player_balance -= money;
    otherPlayer.player_balance += money;
}


void Player::display() const{
    int spaces = 0;
    Node* temp = myBoard.get_first();  //first node of the board
    while (temp != position) {
        temp = temp->next;
        spaces++;
    }
    for (int i = 0; i < spaces; i++) {
        cout << "      ";
    }
    cout << player_name << " " << player_balance << endl; //display the Player and its balance

}