#ifndef CONNECTFOUR_H
#define CONNECTFOUR_H

#include "BoardGame_Classes.h"

class ConnectFour_Board : public Board<char> {
public:
    ConnectFour_Board();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override { return false; }
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
};

class ConnectFour_UI : public UI<char> {
public:
    ConnectFour_UI();
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
};

void ConnectFour_Game();

#endif