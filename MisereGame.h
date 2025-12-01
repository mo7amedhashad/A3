#ifndef MISERE_GAME_H
#define MISERE_GAME_H

class MisereGame {
private:
    char board[3][3];
    char currentPlayer;

    void printBoard();
    bool isFull();
    bool checkWin();
    void switchPlayer();

public:
    MisereGame();
    void play();
};

void Misere_TicTacToe();

#endif
