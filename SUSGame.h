#ifndef SUS_GAME_H
#define SUS_GAME_H

#include "BoardGame_Classes.h"
#include <vector>
#include <utility>

class SUS_Board : public Board<char> {
private:
    int scoreS;
    int scoreU;
    char currentPlayer;

public:
    SUS_Board();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override { return false; }
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
    void checkSequences();
    int getScoreS() const { return scoreS; }
    int getScoreU() const { return scoreU; }
    char getCurrentPlayer() const { return currentPlayer; }
};

class SUS_UI : public UI<char> {
public:
    SUS_UI();
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
};

void SUS_Game();

#endif