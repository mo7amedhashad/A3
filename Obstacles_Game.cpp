#include "Obstacles_Game.h"

void printObstacleBoard(const vector<vector<char>>& board) {
    cout << "\n";
    for (int r = 0; r < 6; r++) {
        for (int c = 0; c < 6; c++) {
            cout << board[r][c] << " ";
        }
        cout << "\n";
    }
}

bool checkWin4(const vector<vector<char>>& board, char p) {
    // Horizontal
    for (int r = 0; r < 6; r++) {
        for (int c = 0; c < 3; c++) {
            if (board[r][c] == p &&
                board[r][c + 1] == p &&
                board[r][c + 2] == p &&
                board[r][c + 3] == p)
                return true;
        }
    }

    // Vertical
    for (int c = 0; c < 6; c++) {
        for (int r = 0; r < 3; r++) {
            if (board[r][c] == p &&
                board[r + 1][c] == p &&
                board[r + 2][c] == p &&
                board[r + 3][c] == p)
                return true;
        }
    }

    // Diagonal down-right
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            if (board[r][c] == p &&
                board[r + 1][c + 1] == p &&
                board[r + 2][c + 2] == p &&
                board[r + 3][c + 3] == p)
                return true;
        }
    }

    // Diagonal up-right
    for (int r = 3; r < 6; r++) {
        for (int c = 0; c < 3; c++) {
            if (board[r][c] == p &&
                board[r - 1][c + 1] == p &&
                board[r - 2][c + 2] == p &&
                board[r - 3][c + 3] == p)
                return true;
        }
    }

    return false;
}

bool boardFull(const vector<vector<char>>& board) {
    for (int r = 0; r < 6; r++)
        for (int c = 0; c < 6; c++)
            if (board[r][c] == '-')
                return false;
    return true;
}

void addRandomObstacles(vector<vector<char>>& board) {
    int count = 0;
    while (count < 2) {
        int r = rand() % 6;
        int c = rand() % 6;
        if (board[r][c] == '-') {
            board[r][c] = '#';
            count++;
        }
    }
}

void Obstacles_Game() {
    srand(time(0));
    vector<vector<char>> board(6, vector<char>(6, '-'));

    char players[2] = { 'X', 'O' };
    int turn = 0;
    int movesThisRound = 0;

    while (true) {
        printObstacleBoard(board);
        char p = players[turn];

        int r, c;
        cout << "\nPlayer " << p << " enter row & col (0–5): ";
        cin >> r >> c;

        if (r < 0 || r > 5 || c < 0 || c > 5 || board[r][c] != '-') {
            cout << "Invalid move! Try again.\n";
            continue;
        }

        board[r][c] = p;

        // Check win
        if (checkWin4(board, p)) {
            printObstacleBoard(board);
            cout << "\nPlayer " << p << " WINS!\n";
            return;
        }

        movesThisRound++;
        turn = 1 - turn;

        // After both players played → add 2 obstacles
        if (movesThisRound == 2) {
            addRandomObstacles(board);
            movesThisRound = 0;

            if (boardFull(board)) {
                printObstacleBoard(board);
                cout << "\nBoard Full — DRAW!\n";
                return;
            }
        }
    }
}
