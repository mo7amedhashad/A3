#pragma once
#ifndef NUMERICAL_GAME_H
#define NUMERICAL_GAME_H

#include "BoardGame_Classes.h"
#include <string>
#include <vector>

class NumericalBoard : public Board<int> {
public:
    NumericalBoard();

    bool update_board(Move<int>* move) override;
    bool is_win(Player<int>* player) override;
    bool is_lose(Player<int>* player) override;
    bool is_draw(Player<int>* player) override;
    bool game_is_over(Player<int>* player) override;
};

class NumericalPlayer : public Player<int> {
public:
    // symbol: 0 => odd-player, 1 => even-player
    NumericalPlayer(const std::string& name, int symbol, PlayerType type);

    std::vector<int>& getAvailableNumbers();
    bool hasAvailableNumbers() const;
    bool useNumber(int num);

private:
    std::vector<int> availableNumbers;
};

class NumericalUI : public UI<int> {
public:
    NumericalUI();
    virtual Move<int>* get_move(Player<int>* player) override;
    virtual Player<int>* create_player(std::string& name, int symbol, PlayerType type) override;

private:
    int get_valid_input(const std::string& prompt, int min, int max);
};

// launcher to be used by the menu
void numerical_game();

#endif // NUMERICAL_GAME_H
