#include "Game.h"
#include "Board.h"
#include "Pieces.h"
#include "AI.h"
using namespace sf;

bool gameOver = false;
std::string position = "";

void draw(RenderWindow &window, Sprite &sBoard)
{
    window.clear();
    window.draw(sBoard);
    for (int i = 0; i < 32; i++)
        f[i].move(offset);
    for (int i = 0; i < 32; i++)
        window.draw(f[i]);
    for (int i = 0; i < 32; i++)
        f[i].move(-offset);
    window.display();
}

void move(std::string str)
{
    Vector2f oldPos = toCord(str[0], str[1]);
    Vector2f newPos = toCord(str[2], str[3]);

    int i = findPieceAt(newPos);

    if (i != -1)
    {
        defeated.push_back({turns, i});
        f[i].setPosition(-100, -100);
    }
}

void back(std::string str)
{
    Vector2f oldPos = toCord(str[0], str[1]);
    Vector2f newPos = toCord(str[2], str[3]);

    int piece = findPieceAt(newPos);
    f[piece].setPosition(oldPos);

    if (defeated.size() && defeated.back().first == turns)
    {
        f[defeated.back().second].setPosition(newPos);
        defeated.pop_back();
    }
}

void undoMoves()
{
    for (int i = 0; i < 2; i++)
    {
        turns--;
        back(position.substr(position.length() - 5, 4));
        position.erase(position.length() - 5, 5);
    }
}

bool isEndGame()
{
    bool wQueen = isValid(f[3].getPosition()), bQueen = isValid(f[27].getPosition());

    if (!wQueen && !bQueen)
        return true;

    int wMinor = 0, bMinor = 0;
    for (int i = 0; i < 8; i++)
    {
        if (i == 3 || i == 4)
            continue;
        if (!isValid(f[i].getPosition()))
            continue;

        bMinor++;
    }
    for (int i = 24; i < 32; i++)
    {
        if (i == 27 || i == 28)
            continue;
        if (!isValid(f[i].getPosition()))
            continue;

        wMinor++;
    }

    if (wQueen && wMinor > 1)
        return false;
    if (bQueen && bMinor > 1)
        return false;

    return true;
}

void checkConditions()
{
    if (!endGame && isEndGame())
        endGame = true;
    if (!gameOver && isGameOver())
        gameOver = true;
}

void compMove(RenderWindow &window, Sprite &sBoard)
{
    checkConditions();

    if (gameOver)
        return;

    std::string str = minimaxString(4, -1e9, 1e9);
    int n = findPieceAt(toCord(str[0], str[1]));

    if (str == "")
        gameOver = true;

    Vector2f oldPos = toCord(str[0], str[1]);
    Vector2f newPos = toCord(str[2], str[3]);

    move(str);
    position += str + ' ';

    Vector2f p = newPos - oldPos;
    float duration = 0.25f;
    Clock clock;

    while (true)
    {
        float elapsed = clock.getElapsedTime().asSeconds();

        if (elapsed >= duration)
            break;

        Vector2f currPos = oldPos + p * (elapsed / duration);
        f[n].setPosition(currPos);

        draw(window, sBoard);
    }

    f[n].setPosition(newPos);

    checkConditions();

    turns++;
}
