#pragma once
#include <string>

extern bool endGame;
extern int turns;

int evaluate();
bool isInsufficientMaterial();
bool isGameOver();
int minimax(int depth, int alpha, int beta, bool forWhite);
std::string minimaxString(int depth, int alpha, int beta);