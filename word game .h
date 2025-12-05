#pragma once
#ifndef _WORD_GAME_H
#define _WORD_GAME_H
#include "BoardGame_Classes.h"
#include <string>
#include <unordered_set>
class WordBoard;
class WordPlayer;
class WordUI;
class WordBoard : public Board<char> {
public:
    WordBoard(int r = 3, int c = 3, const std::string& dict_file = "dic.txt");
    void load_dict(const std::string& filename);
    virtual bool update_board(Move<char>* move) override;
    virtual bool is_win(Player<char>* p) override;
    virtual bool is_lose(Player<char>* p) override;
    virtual bool is_draw(Player<char>* p) override;
    virtual bool game_is_over(Player<char>* p) override;

private:
    std::unordered_set<std::string> dict; 
    bool collect_and_check(int x, int y, int dx, int dy, std::string& current, int depth);
};
class WordPlayer : public Player<char> {
public:
    WordPlayer(const std::string& n, char s, PlayerType t);
    virtual ~WordPlayer();
};
class WordUI : public UI<char> {
public:
    WordUI(const std::string& welcome, int cell_w = 2);
    virtual ~WordUI();

    virtual Player<char>* create_player(std::string& name, char symbol, PlayerType type) override;
    virtual Move<char>* get_move(Player<char>* p) override;
};
void Word_Game();
#endif 

