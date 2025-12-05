#ifndef TICTACTOE5_H
#define TICTACTOE5_H

#include "BoardGame_Classes.h"
#include <string>

class TicTacToe5Board : public Board<char> {
public:
    TicTacToe5Board();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

   
    int count_sequences(char sym) const;

private:
    bool check_line3(int x, int y, int dx, int dy, char sym) const;
};

class TicTacToe5UI : public UI<char> {
public:
    TicTacToe5UI();
    virtual ~TicTacToe5UI() {}

    virtual Player<char>* create_player(std::string& name, char symbol, PlayerType type) override;
    virtual Move<char>* get_move(Player<char>* player) override;
};
void xo_Game();

#endif 
