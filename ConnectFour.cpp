#include "ConnectFour.h"
#include <iostream>
#include <random>

using namespace std;

ConnectFour_Board::ConnectFour_Board() : Board(6, 7) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = '.';
}

bool ConnectFour_Board::update_board(Move<char>* move) {
    int col = move->get_y();
    char mark = move->get_symbol();

    if (col < 0 || col >= columns) {
        cout << "Invalid column. Try again.\n";
        return false;
    }

    for (int row = rows - 1; row >= 0; row--) {
        if (board[row][col] == '.') {
            board[row][col] = mark;
            n_moves++;
            return true;
        }
    }

    cout << "Column is full. Try another.\n";
    return false;
}

bool ConnectFour_Board::is_win(Player<char>* player) {
    char symbol = player->get_symbol();

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < columns - 3; col++) {
            if (board[row][col] == symbol && board[row][col + 1] == symbol &&
                board[row][col + 2] == symbol && board[row][col + 3] == symbol)
                return true;
        }
    }

    for (int row = 0; row < rows - 3; row++) {
        for (int col = 0; col < columns; col++) {
            if (board[row][col] == symbol && board[row + 1][col] == symbol &&
                board[row + 2][col] == symbol && board[row + 3][col] == symbol)
                return true;
        }
    }

    for (int row = 0; row < rows - 3; row++) {
        for (int col = 0; col < columns - 3; col++) {
            if (board[row][col] == symbol && board[row + 1][col + 1] == symbol &&
                board[row + 2][col + 2] == symbol && board[row + 3][col + 3] == symbol)
                return true;
        }
    }

    for (int row = 3; row < rows; row++) {
        for (int col = 0; col < columns - 3; col++) {
            if (board[row][col] == symbol && board[row - 1][col + 1] == symbol &&
                board[row - 2][col + 2] == symbol && board[row - 3][col + 3] == symbol)
                return true;
        }
    }

    return false;
}

bool ConnectFour_Board::is_draw(Player<char>* player) {
    return n_moves >= rows * columns && !is_win(player);
}

bool ConnectFour_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

ConnectFour_UI::ConnectFour_UI() : UI<char>("Welcome to Connect Four!", 3) {}

Player<char>* ConnectFour_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Move<char>* ConnectFour_UI::get_move(Player<char>* player) {
    if (player->get_type() == PlayerType::HUMAN) {
        int col;
        cout << player->get_name() << " (" << player->get_symbol()
            << ") enter column (0-6): ";
        cin >> col;
        return new Move<char>(0, col, player->get_symbol());
    }
    else {
        Board<char>* boardPtr = player->get_board_ptr();
        vector<int> available_cols;
        auto mat = boardPtr->get_board_matrix();

        for (int col = 0; col < boardPtr->get_columns(); ++col) {
            if (mat[0][col] == '.') {
                available_cols.push_back(col);
            }
        }

        if (available_cols.empty()) {
            return new Move<char>(0, 0, player->get_symbol());
        }

        static random_device rd;
        static mt19937 gen(rd());
        uniform_int_distribution<> dist(0, (int)available_cols.size() - 1);

        int chosen_col = available_cols[dist(gen)];
        cout << player->get_name() << " (Computer) plays column: " << chosen_col << "\n";
        return new Move<char>(0, chosen_col, player->get_symbol());
    }
}

void ConnectFour_Game() {
    ConnectFour_Board* board = new ConnectFour_Board();
    ConnectFour_UI* ui = new ConnectFour_UI();

    Player<char>** players = ui->setup_players();
    GameManager<char> gm(board, players, ui);
    gm.run();

    delete board;
    for (int i = 0; i < 2; ++i) delete players[i];
    delete[] players;
    delete ui;
}