#include "word game .h"
#include <fstream>
#include <algorithm>
#include <cctype>
#include <random>
#include <limits>
#include <iostream>
using namespace std;
WordBoard::WordBoard(int r, int c, const string& dict_file)
    : Board<char>(r, c)
{
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < columns; ++j)
            board[i][j] = '.';

    load_dict(dict_file);
}

void WordBoard::load_dict(const std::string& filename) {
    ifstream ifs(filename);
    if (!ifs.is_open()) {
        cerr << "Warning: could not open " << filename << ". No words loaded.\n";
        return;
    }
    std::string w;
    while (ifs >> w) {
        if (w.size() != 3) continue;
        std::string up;
        for (char ch : w) up.push_back(toupper((unsigned char)ch));
        dict.insert(up);
    }
}

bool WordBoard::update_board(Move<char>* move) {
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
    board[x][y] = toupper((unsigned char)sym);
    n_moves++;
    return true;
}

bool WordBoard::collect_and_check(int x, int y, int dx, int dy,string& current, int depth) {
    if (x < 0 || x >= rows || y < 0 || y >= columns) return false;
    if (board[x][y] == '.') return false;

    current.push_back(board[x][y]);
    if (depth == 2) {
        bool found = (dict.find(current) != dict.end());
        current.pop_back();
        return found;
    }
    else {
        bool found = collect_and_check(x + dx, y + dy, dx, dy, current, depth + 1);
        current.pop_back();
        return found;
    }
}

bool WordBoard::is_win(Player<char>*) {
    const int dirs[8][2] = {
        {0,1}, {1,0}, {0,-1}, {-1,0},
        {1,1}, {1,-1}, {-1,1}, {-1,-1}
    };

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (board[i][j] == '.') continue;
            for (auto& d : dirs) {
               string current;
                if (collect_and_check(i, j, d[0], d[1], current, 0))
                    return true;
            }
        }
    }
    return false;
}

bool WordBoard::is_lose(Player<char>*) {
    return false;
}

bool WordBoard::is_draw(Player<char>*) {
    if (n_moves < rows * columns) return false;
    return !is_win(nullptr);
}

bool WordBoard::game_is_over(Player<char>* p) {
    return is_win(p) || is_draw(p);
}

WordPlayer::WordPlayer(const string& n, char s, PlayerType t)
    : Player<char>(n, s, t) {}

WordPlayer::~WordPlayer() {}

WordUI::WordUI(const string& welcome, int cell_w)
    : UI<char>(welcome, cell_w) {}

WordUI::~WordUI() {}

Player<char>* WordUI::create_player(string& name, char symbol, PlayerType type) {
    return new WordPlayer(name, symbol, type);
}

Move<char>* WordUI::get_move(Player<char>* p) {
    if (p->get_type() == PlayerType::HUMAN) {
        int x, y;
        char ch;
        while (true) {
            cout << p->get_name() << " enter row ,col, and letter (example: 0 1 a) ";
            if (!(cin >> x >> y >> ch)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>:: max(), '\n');
                cout << "Invalid input. Try again.\n";
                continue;
            }
            ch =toupper((unsigned char)ch);
            if (!isalpha((unsigned char)ch)) {
                cout << "Letter must be A-Z. Try again.\n";
                continue;
            }
            break;
        }
        return new Move<char>(x, y, ch);
    }
    else {
        Board<char>* bptr = p->get_board_ptr();
        vector<pair<int, int>> empties;
        auto mat = bptr->get_board_matrix();
        for (int i = 0; i < bptr->get_rows(); ++i)
            for (int j = 0; j < bptr->get_columns(); ++j)
                if (mat[i][j] == '.') empties.emplace_back(i, j);

        if (empties.empty()) {
            return new Move<char>(0, 0, 'A');
        }

        static std::random_device rd;
        static std::mt19937 gen(rd());
        uniform_int_distribution<> distPos(0, (int)empties.size() - 1);
        uniform_int_distribution<> distLetter(0, 25);

        auto chosen = empties[distPos(gen)];
        char ch = 'A' + distLetter(gen);
        cout << p->get_name() << " (Computer) plays: " << chosen.first << " " << chosen.second << " " << ch << "\n";
        return new Move<char>(chosen.first, chosen.second, ch);
    }
}
void Word_Game() {
    WordBoard board(3, 3, "dic.txt");
    WordUI ui("=== 3-letter-word Game ===", 2);

    cout << "Set players:\n";
    string name1, name2;
    cout << "Enter Player 1 name: "; getline(cin >> ws, name1);
    cout << "Human or Computer? (h/c): ";
    char t1; cin >> t1;
    PlayerType pt1 = (t1 == 'c' || t1 == 'C') ? PlayerType::COMPUTER : PlayerType::HUMAN;

    cout << "Enter Player 2 name: "; getline(cin >> ws, name2);
    cout << "Human or Computer? (h/c): ";
    char t2; cin >> t2;
    PlayerType pt2 = (t2 == 'c' || t2 == 'C') ? PlayerType::COMPUTER : PlayerType::HUMAN;

    Player<char>* players[2];
    players[0] = new WordPlayer(name1, '1', pt1);
    players[1] = new WordPlayer(name2, '2', pt2);

    GameManager<char> gm(&board, players, &ui);
    gm.run();

    delete players[0];
    delete players[1];
}
