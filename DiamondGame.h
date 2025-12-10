#ifndef DIAMOND_GAME_H
#define DIAMOND_GAME_H

class DiamondGame {
private:
    char board[5][5];
    char currentPlayer;

    void printBoard();
    bool checkWin();
    bool isFull();
    void switchPlayer();

public:
    DiamondGame();
    void play();
};

void Diamond_TicTacToe();

#endif
