#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

void Obstacles_Game();
void printObstacleBoard(const vector<vector<char>>& board);
bool checkWin4(const vector<vector<char>>& board, char p);
void addRandomObstacles(vector<vector<char>>& board);
bool boardFull(const vector<vector<char>>& board);

