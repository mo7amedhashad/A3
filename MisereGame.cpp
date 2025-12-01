#include "MisereGame.h"
#include <iostream>
using namespace std;

MisereGame::MisereGame() {
    currentPlayer = 'X';
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';
}

void MisereGame::printBoard() {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        cout << " ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j];
            if (j < 2) cout << " | ";
        }
        if (i < 2) cout << "\n-----------\n";
    }
    cout << "\n\n";
}

bool MisereGame::isFull() {
    for (auto &row : board)
        for (char c : row)
            if (c == ' ') return false;
    return true;
}

bool MisereGame::checkWin() {
    for (int i = 0; i < 3; i++)
        if (board[i][0] == currentPlayer &&
            board[i][1] == currentPlayer &&
            board[i][2] == currentPlayer)
            return true;

    for (int i = 0; i < 3; i++)
        if (board[0][i] == currentPlayer &&
            board[1][i] == currentPlayer &&
            board[2][i] == currentPlayer)
            return true;

    if (board[0][0] == currentPlayer &&
        board[1][1] == currentPlayer &&
        board[2][2] == currentPlayer)
        return true;

    if (board[0][2] == currentPlayer &&
        board[1][1] == currentPlayer &&
        board[2][0] == currentPlayer)
        return true;

    return false;
}

void MisereGame::switchPlayer() {
    currentPlayer = (currentPlayer == 'X' ? 'O' : 'X');
}

void MisereGame::play() {
    int r, c;

    while (true) {
        printBoard();
        cout << "Player " << currentPlayer << " enter row and column (1-3): ";
        cin >> r >> c;
        r--; c--;

        if (r < 0 || r > 2 || c < 0 || c > 2 || board[r][c] != ' ') {
            cout << "Invalid move.\n";
            continue;
        }

        board[r][c] = currentPlayer;

        if (checkWin()) {
            printBoard();
            cout << "Player " << currentPlayer << " loses! (Misère rule)\n";
            return;
        }

        if (isFull()) {
            printBoard();
            cout << "Draw!\n";
            return;
        }

        switchPlayer();
    }
}

void Misere_TicTacToe() {
    MisereGame game;
    game.play();
}
