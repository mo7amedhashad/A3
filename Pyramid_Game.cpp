#include "Pyramid_Game.h"

void printPyramidBoard(const vector<vector<char>>& board) {
    cout << "\n";
    cout << "   " << board[0][0] << "\n";
    cout << "  " << board[1][0] << " " << board[1][1] << " " << board[1][2] << "\n";
    cout << " " << board[2][0] << " " << board[2][1] << " " << board[2][2] << " "
        << board[2][3] << " " << board[2][4] << "\n";
}

bool checkPyramidWin(const vector<vector<char>>& board, char s) {
    // Check row 0 and row 1
    if (board[0][0] == s && board[1][1] == s && board[2][2] == s) return true; // diagonal middle
    if (board[1][0] == s && board[1][1] == s && board[1][2] == s) return true; // row of 3
    if (board[2][0] == s && board[2][1] == s && board[2][2] == s) return true; // bottom left
    if (board[2][1] == s && board[2][2] == s && board[2][3] == s) return true;
    if (board[2][2] == s && board[2][3] == s && board[2][4] == s) return true;

    // vertical middle
    if (board[0][0] == s && board[1][1] == s && board[2][2] == s) return true;

    // diagonal left
    if (board[2][0] == s && board[1][0] == s && board[0][0] == s) return true;

    // diagonal right
    if (board[2][4] == s && board[1][2] == s && board[0][0] == s) return true;

    return false;
}

bool isValidPyramidMove(const vector<vector<char>>& board, int r, int c) {
    if (r < 0 || r > 2) return false;
    if (r == 0 && c != 0) return false;
    if (r == 1 && (c < 0 || c > 2)) return false;
    if (r == 2 && (c < 0 || c > 4)) return false;
    if (board[r][c] != '-') return false;
    return true;
}

void Pyramid_Game() {
    vector<vector<char>> board = {
        {'-'},        // row 0 → 1 cell
        {'-', '-', '-'}, // row 1 → 3 cells
        {'-', '-', '-', '-', '-'} // row 2 → 5 cells
    };

    char players[2] = { 'X', 'O' };
    int turn = 0;

    while (true) {
        printPyramidBoard(board);

        char current = players[turn];
        cout << "\nPlayer " << current << " enter row and column: ";

        int r, c;
        cin >> r >> c;

        if (!isValidPyramidMove(board, r, c)) {
            cout << "Invalid move! Try again.\n";
            continue;
        }

        board[r][c] = current;

        if (checkPyramidWin(board, current)) {
            printPyramidBoard(board);
            cout << "\nPlayer " << current << " WINS!\n";
            return;
        }

        turn = 1 - turn;
    }
}
