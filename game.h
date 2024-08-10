#pragma once
#include <SFML/Graphics.hpp>
#include <string>

extern bool gameOver;
extern std::string position;

void draw(sf::RenderWindow &window, sf::Sprite &sBoard);
void move(std::string str);
void back(std::string str);
void undoMoves();
bool isEndGame();
void compMove(sf::RenderWindow &window, sf::Sprite &sBoard);