#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

void Pyramid_Game();
void printPyramidBoard(const vector<vector<char>>& board);
bool checkPyramidWin(const vector<vector<char>>& board, char symbol);
bool isValidPyramidMove(const vector<vector<char>>& board, int r, int c);
