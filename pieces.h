#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>

extern sf::Sprite f[32];
extern std::vector<std::pair<int, int>> defeated;

int idxToPiece(int idx);
int findPieceAt(sf::Vector2f pos);

void findRBQMoves(int idx, std::vector<sf::Vector2f> &moves, sf::Vector2f dir[], int n);
void findKKMoves(int idx, std::vector<sf::Vector2f> &moves, sf::Vector2f dir[]);
void rookMoves(int idx, std::vector<sf::Vector2f> &moves);
void knightMoves(int idx, std::vector<sf::Vector2f> &moves);
void bishopMoves(int idx, std::vector<sf::Vector2f> &moves);
void queenMoves(int idx, std::vector<sf::Vector2f> &moves);
void kingMoves(int idx, std::vector<sf::Vector2f> &moves);
void pawnMoves(int idx, std::vector<sf::Vector2f> &moves);
void possibleMoves(int idx, std::vector<sf::Vector2f> &moves);