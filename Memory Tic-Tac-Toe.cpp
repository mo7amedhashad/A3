#include "Memory Tic-Tac-Toe.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// ---------------- BOARD IMPLEMENTATION ----------------

MemoryBoard::MemoryBoard() :Board<char>(3, 3)
{
    rows = columns = 3;
    board = vector<vector<char>>(3, vector<char>(3, ' '));
}



bool MemoryBoard::update_board(Move<char>* move) {
    int r = move->get_x();
    int c = move->get_y();
    char symbol = move->get_symbol();

    if (r < 0 || r >= 3 || c < 0 || c >= 3) return false;
    if (board[r][c] != ' ') return false;

    // Place mark but hide it
    board[r][c] = symbol;   // real
    board[r][c] = '*';      // hidden

    return true;
}

bool MemoryBoard::is_win(Player<char>* player) {
    char hidden = '*';

    // Check rows
    for (int r = 0; r < 3; r++)
        if (board[r][0] == hidden &&
            board[r][1] == hidden &&
            board[r][2] == hidden)
            return true;

    // Check columns
    for (int c = 0; c < 3; c++)
        if (board[0][c] == hidden &&
            board[1][c] == hidden &&
            board[2][c] == hidden)
            return true;

    // Diagonals
    if (board[0][0] == hidden && board[1][1] == hidden && board[2][2] == hidden)
        return true;
    if (board[0][2] == hidden && board[1][1] == hidden && board[2][0] == hidden)
        return true;

    return false;
}

bool MemoryBoard::is_draw(Player<char>* player) {
    for (auto& row : board)
        for (auto c : row)
            if (c == ' ') return false;
    return !is_win(player);
}

bool MemoryBoard::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

void MemoryBoard::display_board() {
    cout << "  0 1 2\n";
    for (int r = 0; r < 3; r++) {
        cout << r << " ";
        for (int c = 0; c < 3; c++)
            cout << "* ";
        cout << "\n";
    }
}

// ---------------- UI IMPLEMENTATION ----------------

Player<char>* MemoryUI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Move<char>* MemoryUI::get_move(Player<char>* player) {
    if (player->get_type() == PlayerType::COMPUTER) {
        int r, c;
        do {
            r = rand() % 3;
            c = rand() % 3;
        } while (player->get_board_ptr()->get_board_matrix()[r][c] != ' ');

        cout << "Computer plays: " << r << " " << c << "\n";
        return new Move<char>(r, c, player->get_symbol());
    }

    int r, c;
    cout << player->get_name() << " (" << player->get_symbol() << ") enter row & col: ";
    cin >> r >> c;
    return new Move<char>(r, c, player->get_symbol());
}

// ---------------- GAME LAUNCHER ----------------

void Memory_Game() {
    srand(static_cast<unsigned int>(time(nullptr)));

    // Create board & UI
    MemoryBoard board;
    MemoryUI ui;

    cout << "=== Memory Tic-Tac-Toe (3x3 Hidden Marks) ===\n";

    // -------- Player 1 --------
    string n1, n2;
    cout << "Enter Player 1 name (X): ";
    getline(cin >> ws, n1);

    cout << "Human or Computer? (h/c): ";
    char t1;
    cin >> t1;
    PlayerType pt1 = (t1 == 'c' || t1 == 'C') ? PlayerType::COMPUTER : PlayerType::HUMAN;

    // -------- Player 2 --------
    cout << "Enter Player 2 name (O): ";
    getline(cin >> ws, n2);

    cout << "Human or Computer? (h/c): ";
    char t2;
    cin >> t2;
    PlayerType pt2 = (t2 == 'c' || t2 == 'C') ? PlayerType::COMPUTER : PlayerType::HUMAN;

    // Create players
    Player<char>* players[2];
    players[0] = new Player<char>(n1, 'X', pt1);
    players[1] = new Player<char>(n2, 'O', pt2);

    // Set board pointer
    players[0]->set_board_ptr(&board);
    players[1]->set_board_ptr(&board);

    // Run Game
    GameManager<char> gm(&board, players, &ui);
    gm.run();

    // Free memory
    delete players[0];
    delete players[1];
}
