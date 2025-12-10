
#include <iostream>
#include <vector>
using namespace std;

#include "UltimateTicTacToe.hpp"

char checkSmallBoardWinner(const vector<vector<char>>& b) {
    for (int i = 0; i < 3; i++) {
        if (b[i][0] != ' ' && b[i][0] == b[i][1] && b[i][1] == b[i][2]) return b[i][0];
        if (b[0][i] != ' ' && b[0][i] == b[1][i] && b[1][i] == b[2][i]) return b[0][i];
    }
    if (b[0][0] != ' ' && b[0][0] == b[1][1] && b[1][1] == b[2][2]) return b[0][0];
    if (b[0][2] != ' ' && b[0][2] == b[1][1] && b[1][1] == b[2][0]) return b[0][2];
    return ' ';
}

bool fullBoard(const vector<vector<char>>& b) {
    for (auto& r : b)
        for (char c : r)
            if (c == ' ') return false;
    return true;
}

void printUltimate(const vector<vector<vector<vector<char>>>>& big, const vector<vector<char>>& mainResult) {
    cout << "\n================ ULTIMATE TIC TAC TOE ================\n\n";
    for (int bigRow = 0; bigRow < 3; bigRow++) {
        for (int smallRow = 0; smallRow < 3; smallRow++) {
            for (int bigCol = 0; bigCol < 3; bigCol++) {
                for (int smallCol = 0; smallCol < 3; smallCol++) {
                    cout << big[bigRow][bigCol][smallRow][smallCol];
                    if (smallCol < 2) cout << " | ";
                }
                if (bigCol < 2) cout << "   ||   ";
            }
            cout << "\n";
        }
        if (bigRow < 2) cout << "------------------------------------------------------\n";
    }
    cout << "\n\n";
}

char checkMainWinner(const vector<vector<char>>& m) {
    for (int i = 0; i < 3; i++) {
        if (m[i][0] != ' ' && m[i][0] == m[i][1] && m[i][1] == m[i][2]) return m[i][0];
        if (m[0][i] != ' ' && m[0][i] == m[1][i] && m[1][i] == m[2][i]) return m[0][i];
    }
    if (m[0][0] != ' ' && m[0][0] == m[1][1] && m[1][1] == m[2][2]) return m[0][0];
    if (m[0][2] != ' ' && m[0][2] == m[1][1] && m[1][1] == m[2][0]) return m[0][2];
    return ' ';
}

void UltimateTicTacToeGame() {
    vector<vector<vector<vector<char>>>> board(3, vector<vector<vector<char>>>(3, vector<vector<char>>(3, vector<char>(3, ' '))));
    vector<vector<char>> bigResult(3, vector<char>(3, ' '));

    char player = 'X';
    int nextBigR = -1, nextBigC = -1;

    while (true) {
        printUltimate(board, bigResult);
        cout << "Player " << player << " turn.\n";

        int br, bc, sr, sc;

        if (nextBigR == -1) {
            cout << "Choose big board (row col from 0 to 2): ";
            cin >> br >> bc;
        } else {
            br = nextBigR; 
            bc = nextBigC;
            cout << "You MUST play inside big board: [" << br << " " << bc << "]\n";
        }

        cout << "Choose cell inside small board (row col from 0 to 2): ";
        cin >> sr >> sc;

        if (br < 0 || br > 2 || bc < 0 || bc > 2 || sr < 0 || sr > 2 || sc < 0 || sc > 2) {
            cout << "Invalid move.\n";
            continue;
        }

        if (bigResult[br][bc] != ' ' || board[br][bc][sr][sc] != ' ') {
            cout << "Cell already taken.\n";
            continue;
        }

        board[br][bc][sr][sc] = player;

        char w = checkSmallBoardWinner(board[br][bc]);
        if (w != ' ') {
            bigResult[br][bc] = w;
            cout << "Player " << w << " won small board!\n";
        } else if (fullBoard(board[br][bc])) {
            bigResult[br][bc] = '-';
        }

        char mainW = checkMainWinner(bigResult);
        if (mainW != ' ') {
            printUltimate(board, bigResult);
            cout << "PLAYER " << mainW << " WON THE GAME!\n";
            return;
        }

        if (bigResult[sr][sc] == ' ') {
            nextBigR = sr;
            nextBigC = sc;
        } else {
            nextBigR = -1;
            nextBigC = -1; 
        }

        player = (player == 'X' ? 'O' : 'X');
    }
}
