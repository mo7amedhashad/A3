#include "xo_game.h"
#include <iostream>
#include <iomanip>
#include <cctype>
#include <limits>

using namespace std;
TicTacToe5Board::TicTacToe5Board() : Board<char>(5, 5) {
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < columns; ++j)
            board[i][j] = '.';
    n_moves = 0;
}

bool TicTacToe5Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char sym = move->get_symbol();

    if (x < 0 || x >= rows || y < 0 || y >= columns) {
        cout << "Invalid position. Try again.\n";
        return false;
    }
    if (board[x][y] != '.') {
        cout << "Cell not empty. Try another.\n";
        return false;
    }
    board[x][y] = std::toupper((unsigned char)sym);
    n_moves++;
    return true;
}
bool TicTacToe5Board::check_line3(int x, int y, int dx, int dy, char sym) const {
    for (int k = 0; k < 3; ++k) {
        int nx = x + k * dx;
        int ny = y + k * dy;
        if (nx < 0 || nx >= rows || ny < 0 || ny >= columns) return false;
        if (board[nx][ny] != sym) return false;
    }
    return true;
}

int TicTacToe5Board::count_sequences(char sym) const {
    const int dirs[4][2] = { {0,1}, {1,0}, {1,1}, {1,-1} };
    int count = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            for (auto& d : dirs) {
                if (check_line3(i, j, d[0], d[1], sym)) ++count;
            }
        }
    }
    return count;
}
bool TicTacToe5Board::is_win(Player<char>* player) {
    if (n_moves < rows* columns - 1) return false; 
    char sym = player->get_symbol();
    char opp = (sym == 'X' ? 'O' : 'X');

    int s1 = count_sequences(sym);
    int s2 = count_sequences(opp);
    return s1 > s2;
}

bool TicTacToe5Board::is_lose(Player<char>* player) {
    if (n_moves < rows * columns - 1) return false;
    char sym = player->get_symbol();
    char opp = (sym == 'X' ? 'O' : 'X');
    int s1 = count_sequences(sym);
    int s2 = count_sequences(opp);
    return s1 < s2;
}

bool TicTacToe5Board::is_draw(Player<char>* player) {
    if (n_moves < rows * columns - 1) return false;
    char sym = player->get_symbol();
    char opp = (sym == 'X' ? 'O' : 'X');
    int s1 = count_sequences(sym);
    int s2 = count_sequences(opp);
    return s1 == s2;
}

bool TicTacToe5Board::game_is_over(Player<char>*) {
    
    return (n_moves >= rows * columns - 1);
}


TicTacToe5UI::TicTacToe5UI() : UI<char>("=== 5x5 Tic-Tac-Toe (count 3-in-row) ===", 3) {}

Player<char>* TicTacToe5UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Move<char>* TicTacToe5UI::get_move(Player<char>* player) {
    if (player->get_type() == PlayerType::HUMAN) {
        int x, y;
        while (true) {
            cout << player->get_name() << " (" << player->get_symbol() << ") enter row col (0-4): ";
            if (!(cin >> x >> y)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Try again.\n";
                continue;
            }
            return new Move<char>(x, y, player->get_symbol());
        }
    }
    else { 
        Board<char>* bptr = player->get_board_ptr();
        auto mat = bptr->get_board_matrix();
        vector<pair<int, int>> empties;
        for (int i = 0; i < bptr->get_rows(); ++i)
            for (int j = 0; j < bptr->get_columns(); ++j)
                if (mat[i][j] == '.') empties.emplace_back(i, j);

        if (empties.empty()) return new Move<char>(0, 0, player->get_symbol());
        int idx = rand() % (int)empties.size();
        auto chosen = empties[idx];
        cout << player->get_name() << " (Computer) plays: " << chosen.first << " " << chosen.second << "\n";
        return new Move<char>(chosen.first, chosen.second, player->get_symbol());
    }
}
void xo_Game() {
    srand(static_cast<unsigned int>(time(nullptr)));
    TicTacToe5Board board;
    TicTacToe5UI ui;

    cout << "Set players for 5x5 Tic-Tac-Toe:\n";
    string n1, n2;
    cout << "Enter Player 1 name (X): "; getline(cin >> ws, n1);
    cout << "Human or Computer? (h/c): ";
    char t1; cin >> t1;
    PlayerType pt1 = (t1 == 'c' || t1 == 'C') ? PlayerType::COMPUTER : PlayerType::HUMAN;

    cout << "Enter Player 2 name (O): "; getline(cin >> ws, n2);
    cout << "Human or Computer? (h/c): ";
    char t2; cin >> t2;
    PlayerType pt2 = (t2 == 'c' || t2 == 'C') ? PlayerType::COMPUTER : PlayerType::HUMAN;

    Player<char>* players[2];
    players[0] = new Player<char>(n1, 'X', pt1);
    players[1] = new Player<char>(n2, 'O', pt2);
    players[0]->set_board_ptr(&board);
    players[1]->set_board_ptr(&board);

    GameManager<char> gm(&board, players, &ui);
    gm.run();
    delete players[0];
    delete players[1];
}
