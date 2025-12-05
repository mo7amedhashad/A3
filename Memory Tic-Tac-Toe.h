#ifndef MEMORY_TICTACTOE_H
#define MEMORY_TICTACTOE_H

#include "BoardGame_Classes.h"
#include <vector>
using namespace std;

// ---------------- BOARD ----------------
class MemoryBoard : public Board<char> {
public:
    MemoryBoard();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>*) override { return false; }
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

    void display_board();
};

// ---------------- UI ----------------
class MemoryUI : public UI<char> {
public:
   virtual Move<char>* get_move(Player<char>* player) override;
     virtual Player<char>* create_player(string& name, char symbol, PlayerType type) override;
};

// ---------------- GAME LAUNCHER FUNCTION ----------------
void Memory_Game();

#endif
