//
// Created by Osman Berk An on 9.05.2023.
//

#ifndef TAKE_HOME_5_PLAYER_H
#define TAKE_HOME_5_PLAYER_H

#include <string>
#include "Board.h"
using namespace  std;



class Player {
private:
    string player_name;
    int player_balance;
    Node* position;
    Board & myBoard;


public:
    Player(Board& board, string name, int c); //constructor

    int get_balance() const;
    bool is_bankrupt() const;
    Node* where_am_I() const;
    void deposit_money(int money);
    void buy_slot(int price);
    int move(int steps);
    void pay_to_player(Player& otherPlayer,int money);
    void display() const;
};


#endif //TAKE_HOME_5_PLAYER_H
