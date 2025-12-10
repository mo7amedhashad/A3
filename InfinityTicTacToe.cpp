#include "InfinityTicTacToe.h"
#include <iostream>
#include <random>

using namespace std;

Infinity_Board::Infinity_Board() : Board(3, 3), moveCounter(0) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = '.';
}

bool Infinity_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    if (x < 0 || x >= rows || y < 0 || y >= columns) {
        cout << "Invalid position. Try again.\n";
        return false;
    }

    if (board[x][y] != '.') {
        cout << "Cell not empty. Try another.\n";
        return false;
    }

    board[x][y] = mark;
    moveHistory.push({ x, y });
    moveCounter++;
    n_moves++;

    if (moveCounter % 3 == 0 && moveCounter > 0) {
        removeOldestMove();
    }

    return true;
}

void Infinity_Board::removeOldestMove() {
    if (!moveHistory.empty()) {
        auto oldest = moveHistory.front();
        board[oldest.first][oldest.second] = '.';
        moveHistory.pop();
        n_moves--;
    }
}

bool Infinity_Board::is_win(Player<char>* player) {
    char symbol = player->get_symbol();

    for (int i = 0; i < 3; i++) {
        if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol)
            return true;
    }

    for (int i = 0; i < 3; i++) {
        if (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol)
            return true;
    }

    if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol)
        return true;
    if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol)
        return true;

    return false;
}

bool Infinity_Board::is_draw(Player<char>* player) {
    return false;
}

bool Infinity_Board::game_is_over(Player<char>* player) {
    return is_win(player);
}

Infinity_UI::Infinity_UI() : UI<char>("Welcome to Infinity Tic-Tac-Toe (Oldest moves disappear every 3 moves!)", 3) {}

Player<char>* Infinity_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Move<char>* Infinity_UI::get_move(Player<char>* player) {
    if (player->get_type() == PlayerType::HUMAN) {
        int x, y;
        cout << player->get_name() << " (" << player->get_symbol()
            << ") enter your move (row and column 0-2): ";
        cin >> x >> y;
        return new Move<char>(x, y, player->get_symbol());
    }
    else {
        Board<char>* boardPtr = player->get_board_ptr();
        vector<pair<int, int>> empties;
        auto mat = boardPtr->get_board_matrix();
        for (int i = 0; i < boardPtr->get_rows(); ++i)
            for (int j = 0; j < boardPtr->get_columns(); ++j)
                if (mat[i][j] == '.') empties.emplace_back(i, j);

        if (empties.empty()) {
            return new Move<char>(0, 0, player->get_symbol());
        }

        static random_device rd;
        static mt19937 gen(rd());
        uniform_int_distribution<> dist(0, (int)empties.size() - 1);

        auto chosen = empties[dist(gen)];
        cout << player->get_name() << " (Computer) plays: "
            << chosen.first << " " << chosen.second << "\n";
        return new Move<char>(chosen.first, chosen.second, player->get_symbol());
    }
}

void Infinity_TicTacToe() {
    Infinity_Board* board = new Infinity_Board();
    Infinity_UI* ui = new Infinity_UI();

    cout << "Set players for Infinity Tic-Tac-Toe:\n";
    string name1, name2;
    cout << "Enter Player X name: ";
    getline(cin >> ws, name1);
    cout << "Human or Computer? (h/c): ";
    char t1; cin >> t1;
    PlayerType pt1 = (t1 == 'c' || t1 == 'C') ? PlayerType::COMPUTER : PlayerType::HUMAN;

    cout << "Enter Player O name: ";
    getline(cin >> ws, name2);
    cout << "Human or Computer? (h/c): ";
    char t2; cin >> t2;
    PlayerType pt2 = (t2 == 'c' || t2 == 'C') ? PlayerType::COMPUTER : PlayerType::HUMAN;

    Player<char>* players[2];
    players[0] = new Player<char>(name1, 'X', pt1);
    players[1] = new Player<char>(name2, 'O', pt2);

    GameManager<char> gm(board, players, ui);
    gm.run();

    delete board;
    delete ui;
    delete players[0];
    delete players[1];
}