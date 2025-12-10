#include "SUSGame.h"
#include <iostream>
#include <random>
#include "SUSGame.h"

using namespace std;

SUS_Board::SUS_Board() : Board(3, 3), scoreS(0), scoreU(0), currentPlayer('S') {
    for (auto& row : board)
        for (auto& cell : row)
            cell = ' ';
}

bool SUS_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    if (x < 0 || x >= rows || y < 0 || y >= columns) {
        cout << "Invalid position. Try again.\n";
        return false;
    }

    if (board[x][y] != ' ') {
        cout << "Cell not empty. Try another.\n";
        return false;
    }

    board[x][y] = mark;
    n_moves++;
    checkSequences();

    currentPlayer = (currentPlayer == 'S') ? 'U' : 'S';
    return true;
}

void SUS_Board::checkSequences() {
    vector<vector<pair<int, int>>> directions = {
        {{0,0}, {0,1}, {0,2}},
        {{1,0}, {1,1}, {1,2}},
        {{2,0}, {2,1}, {2,2}},
        {{0,0}, {1,0}, {2,0}},
        {{0,1}, {1,1}, {2,1}},
        {{0,2}, {1,2}, {2,2}},
        {{0,0}, {1,1}, {2,2}},
        {{0,2}, {1,1}, {2,0}}
    };

    for (auto& direction : directions) {
        vector<char> cells;
        for (auto& pos : direction) {
            cells.push_back(board[pos.first][pos.second]);
        }
        if (cells[0] == 'S' && cells[1] == 'U' && cells[2] == 'S') {
            if (currentPlayer == 'S') scoreS++;
            else scoreU++;
        }
    }
}

bool SUS_Board::is_win(Player<char>* player) {
    if (n_moves < 9) return false;

    char playerSymbol = player->get_symbol();
    if (playerSymbol == 'S' && scoreS > scoreU) return true;
    if (playerSymbol == 'U' && scoreU > scoreS) return true;
    return false;
}

bool SUS_Board::is_draw(Player<char>* player) {
    if (n_moves < 9) return false;

    char playerSymbol = player->get_symbol();
    if ((playerSymbol == 'S' && scoreS == scoreU) ||
        (playerSymbol == 'U' && scoreS == scoreU)) {
        return true;
    }
    return false;
}

bool SUS_Board::game_is_over(Player<char>* player) {
    return n_moves >= 9;
}

SUS_UI::SUS_UI() : UI<char>("Welcome to SUS Game", 3) {}

Player<char>* SUS_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Move<char>* SUS_UI::get_move(Player<char>* player) {
    SUS_Board* boardPtr = dynamic_cast<SUS_Board*>(player->get_board_ptr());

    if (player->get_type() == PlayerType::HUMAN) {
        int x, y;
        cout << player->get_name() << " (" << boardPtr->getCurrentPlayer()
            << ") enter your move (row and column 0-2): ";
        cin >> x >> y;
        return new Move<char>(x, y, boardPtr->getCurrentPlayer());
    }
    else {
        vector<pair<int, int>> empties;
        auto mat = boardPtr->get_board_matrix();
        for (int i = 0; i < boardPtr->get_rows(); ++i)
            for (int j = 0; j < boardPtr->get_columns(); ++j)
                if (mat[i][j] == ' ') empties.emplace_back(i, j);

        if (empties.empty()) {
            return new Move<char>(0, 0, boardPtr->getCurrentPlayer());
        }

        static random_device rd;
        static mt19937 gen(rd());
        uniform_int_distribution<> dist(0, (int)empties.size() - 1);

        auto chosen = empties[dist(gen)];
        cout << player->get_name() << " (Computer) plays: "
            << chosen.first << " " << chosen.second << "\n";
        return new Move<char>(chosen.first, chosen.second, boardPtr->getCurrentPlayer());
    }
}

void SUS_Game() {
    SUS_Board* board = new SUS_Board();
    SUS_UI* ui = new SUS_UI();

    cout << "Set players for SUS Game:\n";
    string name1, name2;
    cout << "Enter Player S name: ";
    getline(cin >> ws, name1);
    cout << "Human or Computer? (h/c): ";
    char t1; cin >> t1;
    PlayerType pt1 = (t1 == 'c' || t1 == 'C') ? PlayerType::COMPUTER : PlayerType::HUMAN;

    cout << "Enter Player U name: ";
    getline(cin >> ws, name2);
    cout << "Human or Computer? (h/c): ";
    char t2; cin >> t2;
    PlayerType pt2 = (t2 == 'c' || t2 == 'C') ? PlayerType::COMPUTER : PlayerType::HUMAN;

    Player<char>* players[2];
    players[0] = new Player<char>(name1, 'S', pt1);
    players[1] = new Player<char>(name2, 'U', pt2);

    GameManager<char> gm(board, players, ui);
    gm.run();

    SUS_Board* susBoard = dynamic_cast<SUS_Board*>(board);
    cout << "\nFinal Scores - S: " << susBoard->getScoreS()
        << ", U: " << susBoard->getScoreU() << endl;

    delete board;
    delete ui;
    delete players[0];
    delete players[1];
}  