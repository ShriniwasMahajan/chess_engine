#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

extern bool endGame;
extern int turns;

int evaluate();
bool isInsufficientMaterial();
bool isGameOver();
int backtrack(std::string &str, int i, int j, std::vector<sf::Vector2f> &moves, int depth, int alpha, int beta, bool forWhite);
void minmaxUtil(int depth, int &alpha, int &beta, bool forWhite, int &i, int &someEval);
int minimax(int depth, int alpha, int beta, bool forWhite);
std::string minimaxString(int depth, int alpha, int beta);