#include "DiamondGame.h"
#include <iostream>
using namespace std;

DiamondGame::DiamondGame() {
    currentPlayer = 'X';

    char temp[5][5] = {
        {' ', ' ', 'X', ' ', ' '},
        {' ', 'X', 'X', 'X', ' '},
        {'X', 'X', 'X', 'X', 'X'},
        {' ', 'X', 'X', 'X', ' '},
        {' ', ' ', 'X', ' ', ' '}
    };

    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            board[i][j] = (temp[i][j] == 'X' ? ' ' : '#');
}

void DiamondGame::printBoard() {
    cout << "\nDiamond Board:\n";
    for (int i = 0; i < 5; i++) {
        cout << " ";
        for (int j = 0; j < 5; j++) {
            if (board[i][j] == '#') cout << "  ";
            else cout << board[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

bool DiamondGame::checkWin() {
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == currentPlayer &&
                board[i][j + 1] == currentPlayer &&
                board[i][j + 2] == currentPlayer)
                return true;

    for (int j = 0; j < 5; j++)
        for (int i = 0; i < 3; i++)
            if (board[i][j] == currentPlayer &&
                board[i + 1][j] == currentPlayer &&
                board[i + 2][j] == currentPlayer)
                return true;

    return false;
}

bool DiamondGame::isFull() {
    for (auto &row : board)
        for (char c : row)
            if (c == ' ') return false;
    return true;
}

void DiamondGame::switchPlayer() {
    currentPlayer = (currentPlayer == 'X' ? 'O' : 'X');
}

void DiamondGame::play() {
    int r, c;

    while (true) {
        printBoard();
        cout << "Player " << currentPlayer << " enter row and column (1-5): ";
        cin >> r >> c;
        r--; c--;

        if (r < 0 || r > 4 || c < 0 || c > 4 || board[r][c] != ' ') {
            cout << "Invalid move.\n";
            continue;
        }

        board[r][c] = currentPlayer;

        if (checkWin()) {
            printBoard();
            cout << "Player " << currentPlayer << " wins!\n";
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

void Diamond_TicTacToe() {
    DiamondGame game;
    game.play();
}
