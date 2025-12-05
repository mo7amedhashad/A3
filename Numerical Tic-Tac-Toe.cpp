#include "Numerical Tic-Tac-Toe.h"
#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
using namespace std;
NumericalBoard::NumericalBoard() : Board<int>(3, 3) {
    board = vector<vector<int>>(3, vector<int>(3, -1));
    n_moves = 0;
}

bool NumericalBoard::update_board(Move<int>* move) {
    int row = move->get_x();
    int col = move->get_y();
    int value = move->get_symbol();

    if (row < 0 || row > 2 || col < 0 || col > 2)
        return false;
    if (board[row][col] != -1)
        return false;

    board[row][col] = value;
    n_moves++;
    return true;
}

bool NumericalBoard::is_win(Player<int>* /*player*/) {
    // Check rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] != -1 && board[i][1] != -1 && board[i][2] != -1 &&
            board[i][0] + board[i][1] + board[i][2] == 15) {
            return true;
        }
    }
    for (int j = 0; j < 3; j++) {
        if (board[0][j] != -1 && board[1][j] != -1 && board[2][j] != -1 &&
            board[0][j] + board[1][j] + board[2][j] == 15) {
            return true;
        }
    }
    if (board[0][0] != -1 && board[1][1] != -1 && board[2][2] != -1 &&
        board[0][0] + board[1][1] + board[2][2] == 15) {
        return true;
    }
    if (board[0][2] != -1 && board[1][1] != -1 && board[2][0] != -1 &&
        board[0][2] + board[1][1] + board[2][0] == 15) {
        return true;
    }
    return false;
}

bool NumericalBoard::is_draw(Player<int>* player) {
    return (n_moves == 9 && !is_win(player));
}

bool NumericalBoard::is_lose(Player<int>* /*player*/) {
    return false;
}

bool NumericalBoard::game_is_over(Player<int>* player) {
    return is_win(player) || is_draw(player);
}

/* ---------------- NumericalPlayer ---------------- */

NumericalPlayer::NumericalPlayer(const std::string& name, int symbol, PlayerType type)
    : Player<int>(name, symbol, type)
{
    // symbol == 0 => odd player, symbol == 1 => even player
    if (symbol == 0) { // odds
        availableNumbers = { 1, 3, 5, 7, 9 };
    }
    else { // evens
        availableNumbers = { 2, 4, 6, 8 };
    }
}

vector<int>& NumericalPlayer::getAvailableNumbers() {
    return availableNumbers;
}

bool NumericalPlayer::hasAvailableNumbers() const {
    return !availableNumbers.empty();
}

bool NumericalPlayer::useNumber(int num) {
    auto it = find(availableNumbers.begin(), availableNumbers.end(), num);
    if (it != availableNumbers.end()) {
        availableNumbers.erase(it);
        return true;
    }
    return false;
}

/* ---------------- NumericalUI ---------------- */

NumericalUI::NumericalUI() : UI<int>("Welcome to Numerical Tic-Tac-Toe!", 3) {
    srand(static_cast<unsigned int>(time(nullptr)));
    display_message("Player O (odd): numbers {1,3,5,7,9}");
    display_message("Player E (even): numbers {2,4,6,8}");
    display_message("Goal: Make a line (row/col/diag) that sums to 15.");
}

int NumericalUI::get_valid_input(const string& prompt, int min, int max) {
    int value;
    while (true) {
        cout << prompt;
        if (!(cin >> value)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Try again.\n";
            continue;
        }
        if (value < min || value > max) {
            cout << "Out of range. Try again.\n";
            continue;
        }
        return value;
    }
}

Move<int>* NumericalUI::get_move(Player<int>* player) {
    NumericalPlayer* np = dynamic_cast<NumericalPlayer*>(player);
    NumericalBoard* nb = dynamic_cast<NumericalBoard*>(player->get_board_ptr());
    if (!np || !nb) return nullptr;

    int row, col, num;
    bool validMove = false;

    while (!validMove) {
        cout << "\n" << player->get_name() << "'s turn.\n";
        row = get_valid_input("Enter row (0-2): ", 0, 2);
        col = get_valid_input("Enter column (0-2): ", 0, 2);

        if (nb->get_board_matrix()[row][col] != -1) {
            cout << "Cell already occupied. Choose another.\n";
            continue;
        }

        cout << "Available numbers: ";
        for (int n : np->getAvailableNumbers()) cout << n << " ";
        cout << "\n";

        num = get_valid_input("Enter number to place: ", 1, 9);

        if (find(np->getAvailableNumbers().begin(), np->getAvailableNumbers().end(), num) == np->getAvailableNumbers().end()) {
            cout << "Number not available for you. Choose again.\n";
            continue;
        }

        np->useNumber(num);
        validMove = true;
    }

    return new Move<int>(row, col, num);
}

Player<int>* NumericalUI::create_player(string& name, int symbol, PlayerType type) {
    return new NumericalPlayer(name, symbol, type);
}

void numerical_game() {
    NumericalBoard board;
    NumericalUI ui;

    cout << "Set players for Numerical Tic-Tac-Toe:\n";
    string name1, name2;
    cout << "Enter Player 1 name (Odd player): ";
    getline(cin >> ws, name1);
    cout << "Is Player 1 a Computer? (y/n): ";
    char c1; cin >> c1;
    PlayerType pt1 = (c1 == 'y' || c1 == 'Y') ? PlayerType::COMPUTER : PlayerType::HUMAN;

    cout << "Enter Player 2 name (Even player): ";
    getline(cin >> ws, name2);
    cout << "Is Player 2 a Computer? (y/n): ";
    char c2; cin >> c2;
    PlayerType pt2 = (c2 == 'y' || c2 == 'Y') ? PlayerType::COMPUTER : PlayerType::HUMAN;

    // create players: symbol 0 => odd set, symbol 1 => even set
    Player<int>* players[2];
    players[0] = new NumericalPlayer(name1, 0, pt1);
    players[1] = new NumericalPlayer(name2, 1, pt2);

    // attach board pointer to players (GameManager will also set them in constructor)
    players[0]->set_board_ptr(&board);
    players[1]->set_board_ptr(&board);

    GameManager<int> gm(&board, players, &ui);
    gm.run();

    delete players[0];
    delete players[1];
}
