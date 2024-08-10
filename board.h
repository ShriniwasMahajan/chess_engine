#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

extern int board[8][8];
extern int pieceVals[32];
extern int bRookPos[64];
extern int bKnightPos[64];
extern int bBishopPos[64];
extern int bQueenPos[64];
extern int bKingPos[64];
extern int bKingEndGame[64];
extern int bPawnPos[64];

extern int size;
extern sf::Vector2f offset;

std::string toChessNote(sf::Vector2f p);
sf::Vector2f toCord(char a, char b);
bool isValid(sf::Vector2f pos);
void loadPosition();
void restart();
