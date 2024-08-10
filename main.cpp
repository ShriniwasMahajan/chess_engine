#include <SFML/Graphics.hpp>
#include "board.h"
#include "pieces.h"
#include "ai.h"
#include "game.h"
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(504, 504), "Chess Engine");

    Texture t1, t2;
    t1.loadFromFile("Resources/figures.png");
    t2.loadFromFile("Resources/board.png");

    Image icon;
    icon.loadFromFile("Resources/icon.png");

    for (int i = 0; i < 32; i++)
        f[i].setTexture(t1);
    Sprite sBoard(t2);
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    loadPosition();

    bool isMove = false;
    float dx = 0, dy = 0;
    int n;

    Vector2f oldPos, newPos;
    std::vector<Vector2f> legalMoves;

    while (window.isOpen())
    {
        Vector2i pos = Mouse::getPosition(window) - (Vector2i)offset;

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();

            if (e.type == Event::KeyPressed)
                if (e.key.code == Keyboard::Key::BackSpace)
                {
                    if (position.length())
                        undoMoves();
                }
                else if (e.key.code == Keyboard::Key::R)
                    restart();

            if (e.type == Event::MouseButtonPressed)
                if (e.mouseButton.button == Mouse::Button::Left)
                    for (int i = 16; i < 32; i++)
                        if (f[i].getGlobalBounds().contains(pos.x, pos.y))
                        {
                            if (gameOver)
                                continue;

                            isMove = true;

                            legalMoves.clear();
                            possibleMoves(i, legalMoves);

                            n = i;
                            dx = pos.x - f[i].getPosition().x;
                            dy = pos.y - f[i].getPosition().y;

                            oldPos = f[i].getPosition();
                        }

            if (e.type == Event::MouseButtonReleased)
                if (e.mouseButton.button == Mouse::Button::Left)
                {
                    if (!isMove)
                        continue;

                    isMove = false;
                    Vector2f p = f[n].getPosition() + Vector2f(size / 2, size / 2);

                    newPos = Vector2f((int)p.x / size * size, (int)p.y / size * size);
                    if (std::find(legalMoves.begin(), legalMoves.end(), newPos) == legalMoves.end())
                        newPos = oldPos;

                    if (oldPos != newPos)
                    {
                        std::string str = toChessNote(oldPos) + toChessNote(newPos);
                        move(str);
                        turns++;
                        position += str + " ";
                    }
                    f[n].setPosition(newPos);

                    if (oldPos != newPos)
                        compMove(window, sBoard);
                }
        }

        if (isMove)
            f[n].setPosition(pos.x - dx, pos.y - dy);

        draw(window, sBoard);
    }

    return 0;
}