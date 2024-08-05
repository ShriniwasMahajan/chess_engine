#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
using namespace sf;

int size = 56;
int turns = 1;

bool endGame = false;
bool gameOver = false;

Vector2f offset(28, 28);

Sprite f[32];
std::string position = "";

std::vector<Vector2f> legalMoves;
std::vector<std::pair<int, int>> defeated;

int board[8][8] = {-1, -2, -3, -4, -5, -3, -2, -1,
                   -6, -6, -6, -6, -6, -6, -6, -6,
                   0, 0, 0, 0, 0, 0, 0, 0,
                   0, 0, 0, 0, 0, 0, 0, 0,
                   0, 0, 0, 0, 0, 0, 0, 0,
                   0, 0, 0, 0, 0, 0, 0, 0,
                   6, 6, 6, 6, 6, 6, 6, 6,
                   1, 2, 3, 4, 5, 3, 2, 1};

int pieceVals[32] = {-500, -320, -330, -900, -20000, -330, -320, -500,
                     -100, -100, -100, -100, -100, -100, -100, -100,
                     100, 100, 100, 100, 100, 100, 100, 100,
                     500, 320, 330, 900, 20000, 330, 320, 500};

int bRookPos[64] = {0, 0, 0, 10, 10, 0, 0, 0,
                    -5, 0, 0, 0, 0, 0, 0, -5,
                    -5, 0, 0, 0, 0, 0, 0, -5,
                    -5, 0, 0, 0, 0, 0, 0, -5,
                    -5, 0, 0, 0, 0, 0, 0, -5,
                    -5, 0, 0, 0, 0, 0, 0, -5,
                    5, 10, 10, 10, 10, 10, 10, 5,
                    0, 0, 0, 0, 0, 0, 0, 0};

int bKnightPos[64] = {-50, -40, -30, -30, -30, -30, -40, -50,
                      -40, -20, 0, 5, 5, 0, -20, -40,
                      -30, 5, 10, 15, 15, 10, 5, -30,
                      -30, 0, 15, 20, 20, 15, 0, -30,
                      -30, 5, 15, 20, 20, 15, 5, -30,
                      -30, 0, 10, 15, 15, 10, 0, -30,
                      -40, -20, 0, 0, 0, 0, -20, -40,
                      -50, -40, -30, -30, -30, -30, -40, -50};

int bBishopPos[64] = {-20, -10, -10, -10, -10, -10, -10, -20,
                      -10, 5, 0, 0, 0, 0, 5, -10,
                      -10, 10, 10, 10, 10, 10, 10, -10,
                      -10, 0, 10, 10, 10, 10, 0, -10,
                      -10, 5, 5, 10, 10, 5, 5, -10,
                      -10, 0, 5, 10, 10, 5, 0, -10,
                      -10, 0, 0, 0, 0, 0, 0, -10,
                      -20, -10, -10, -10, -10, -10, -10, -20};

int bQueenPos[64] = {-20, -10, -10, -5, -5, -10, -10, -20,
                     -10, 0, 5, 0, 0, 0, 0, -10,
                     -10, 5, 5, 5, 5, 5, 0, -10,
                     0, 0, 5, 5, 5, 5, 0, -5,
                     -5, 0, 5, 5, 5, 5, 0, -5,
                     -10, 0, 5, 5, 5, 5, 0, -10,
                     -10, 0, 0, 0, 0, 0, 0, -10,
                     -20, -10, -10, -5, -5, -10, -10, -20};

int bKingPos[64] = {20, 30, 10, 0, 0, 10, 30, 20,
                    20, 20, 0, 0, 0, 0, 20, 20,
                    -10, -20, -20, -20, -20, -20, -20, -10,
                    -20, -30, -30, -40, -40, -30, -30, -20,
                    -30, -40, -40, -50, -50, -40, -40, -30,
                    -30, -40, -40, -50, -50, -40, -40, -30,
                    -30, -40, -40, -50, -50, -40, -40, -30,
                    -30, -40, -40, -50, -50, -40, -40, -30};

int bKingEndGame[64] = {-50, -30, -30, -30, -30, -30, -30, -50,
                        -30, -30, 0, 0, 0, 0, -30, -30,
                        -30, -10, 20, 30, 30, 20, -10, -30,
                        -30, -10, 30, 40, 40, 30, -10, -30,
                        -30, -10, 30, 40, 40, 30, -10, -30,
                        -30, -10, 20, 30, 30, 20, -10, -30,
                        -30, -20, -10, 0, 0, -10, -20, -30,
                        -50, -40, -30, -20, -20, -30, -40, -50};

int bPawnPos[64] = {0, 0, 0, 0, 0, 0, 0, 0,
                    5, 10, 10, -20, -20, 10, 10, 5,
                    5, -5, -10, 0, 0, -10, -5, 5,
                    0, 0, 0, 20, 20, 0, 0, 0,
                    5, 5, 10, 25, 25, 10, 5, 5,
                    10, 10, 20, 30, 30, 20, 10, 10,
                    50, 50, 50, 50, 50, 50, 50, 50,
                    0, 0, 0, 0, 0, 0, 0, 0};

int idxToPiece(int idx)
{
    if (idx == 0 || idx == 7 || idx == 24 || idx == 31)
        return 1;
    else if (idx == 1 || idx == 6 || idx == 25 || idx == 30)
        return 2;
    else if (idx == 2 || idx == 5 || idx == 26 || idx == 29)
        return 3;
    else if (idx == 3 || idx == 27)
        return 4;
    else if (idx == 4 || idx == 28)
        return 5;
    else
        return 6;
}

std::string toChessNote(Vector2f p)
{
    std::string s = "";
    s += p.x / size + 97;
    s += 7 - p.y / size + 49;
    return s;
}

Vector2f toCord(char a, char b)
{
    int x = (int)a - 97;
    int y = 7 - (int)b + 49;
    return Vector2f(x * size, y * size);
}

bool isValid(Vector2f pos)
{
    return std::min(pos.x, pos.y) >= 0.0f && std::max(pos.x, pos.y) < 8.0f * size;
}

int findPieceAt(Vector2f pos)
{
    for (int i = 0; i < 32; i++)
        if (f[i].getPosition() == pos)
            return i;
    return -1;
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

void loadPosition()
{
    int k = 0;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
        {
            if (!board[i][j])
                continue;
            int place = abs(board[i][j]) - 1;
            int sign = board[i][j] > 0;
            f[k].setTextureRect(IntRect(size * place, size * sign, size, size));
            f[k].setPosition(size * j, size * i);
            k++;
        }
}

void restart()
{
    position = "";
    turns = 1;
    defeated.clear();

    for (int i = 0; i < 16; i++)
        f[i].setPosition(size * (i % 8), size * (i / 8));
    for (int i = 16; i < 32; i++)
        f[i].setPosition(size * (i % 8), size * (4 + (i / 8)));
}

void findRBQMoves(int idx, std::vector<Vector2f> &moves, Vector2f dir[], int n)
{
    Vector2f pos = f[idx].getPosition();

    for (int d = 0; d < n; d++)
    {
        dir[d].x *= size;
        dir[d].y *= size;

        Vector2f temp = pos;

        while (true)
        {
            temp += dir[d];
            if (!isValid(temp))
                break;

            int piece = findPieceAt(temp);
            if (piece == -1)
                moves.push_back(temp);
            else
            {
                if (piece / 16 != idx / 16)
                    moves.push_back(temp);
                break;
            }
        }
    }
}

void findKKMoves(int idx, std::vector<Vector2f> &moves, Vector2f dir[])
{
    Vector2f pos = f[idx].getPosition();

    for (int d = 0; d < 8; d++)
    {
        dir[d].x *= size;
        dir[d].y *= size;

        Vector2f temp = pos + dir[d];

        if (!isValid(temp))
            continue;

        int piece = findPieceAt(temp);
        if (piece == -1 || piece / 16 != idx / 16)
            moves.push_back(temp);
    }
}

void rookMoves(int idx, std::vector<Vector2f> &moves)
{
    Vector2f dir[4] = {Vector2f(1.0f, 0), Vector2f(-1.0f, 0), Vector2f(0, 1.0f), Vector2f(0, -1.0f)};

    findRBQMoves(idx, moves, dir, 4);
}

void knightMoves(int idx, std::vector<Vector2f> &moves)
{
    Vector2f dir[8] = {Vector2f(2.0f, -1.0f),
                       Vector2f(2.0f, 1.0f),
                       Vector2f(-2.0f, -1.0f),
                       Vector2f(-2.0f, 1.0f),
                       Vector2f(1.0f, -2.0f),
                       Vector2f(-1.0f, -2.0f),
                       Vector2f(1.0f, 2.0f),
                       Vector2f(-1.0f, 2.0f)};

    findKKMoves(idx, moves, dir);
}

void bishopMoves(int idx, std::vector<Vector2f> &moves)
{
    Vector2f dir[4] = {Vector2f(1.0f, 1.0f), Vector2f(-1.0f, -1.0f), Vector2f(1.0f, -1.0f), Vector2f(-1.0f, 1.0f)};

    findRBQMoves(idx, moves, dir, 4);
}

void queenMoves(int idx, std::vector<Vector2f> &moves)
{
    Vector2f dir[8] = {Vector2f(1.0f, 0), Vector2f(-1.0f, 0), Vector2f(0, 1.0f), Vector2f(0, -1.0f), Vector2f(1.0f, 1.0f), Vector2f(-1.0f, -1.0f), Vector2f(1.0f, -1.0f), Vector2f(-1.0f, 1.0f)};

    findRBQMoves(idx, moves, dir, 8);
}

void kingMoves(int idx, std::vector<Vector2f> &moves)
{
    Vector2f dir[8] = {Vector2f(1.0f, -1.0f),
                       Vector2f(1.0f, 1.0f),
                       Vector2f(-1.0f, -1.0f),
                       Vector2f(-1.0f, 1.0f),
                       Vector2f(0, -1.0f),
                       Vector2f(-1.0f, 0),
                       Vector2f(0, 1.0f),
                       Vector2f(1.0f, 0)};

    findKKMoves(idx, moves, dir);
}

void pawnMoves(int idx, std::vector<Vector2f> &moves)
{
    Vector2f pos = f[idx].getPosition();

    Vector2f dir[2] = {Vector2f(0, 1.0f * size), Vector2f(0, -1.0f * size)};
    Vector2f atk[2][2] = {Vector2f(-1.0f * size, 1.0f * size),
                          Vector2f(1.0f * size, 1.0f * size),
                          Vector2f(-1.0f * size, -1.0f * size),
                          Vector2f(1.0f * size, -1.0f * size)};

    bool twoSq = idx / 16 ? (pos.y == 6.0f * size) : (pos.y == 1.0f * size);

    Vector2f temp = pos + dir[idx / 16];
    if (findPieceAt(temp) == -1)
        moves.push_back(temp);

    temp += dir[idx / 16];
    if (twoSq && moves.size() && findPieceAt(temp) == -1)
        moves.push_back(temp);

    for (int i = 0; i < 2; i++)
    {
        temp = pos + atk[idx / 16][i];
        if (isValid(temp) && idx / 16 != findPieceAt(temp) / 16)
            moves.push_back(temp);
    }
}

void possibleMoves(int idx, std::vector<Vector2f> &moves)
{
    std::function<void(int, std::vector<Vector2f> &)> funcs[] = {rookMoves, knightMoves, bishopMoves, queenMoves, kingMoves, pawnMoves};

    int piece = idxToPiece(idx);
    funcs[piece - 1](idx, moves);
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

int evaluate()
{
    int *bMap[] = {bRookPos, bKnightPos, bBishopPos, bQueenPos, bKingPos, bPawnPos, bKingEndGame};

    int value = 0;
    for (int k = 0; k < 32; k++)
    {
        Vector2f pos = f[k].getPosition();
        if (!isValid(pos))
            continue;

        pos.x /= size;
        pos.y /= size;

        int i = pos.y, j = pos.x;
        int piece = idxToPiece(k);

        if (piece == 5 && endGame)
            piece = 7;

        value += pieceVals[k];
        value += bMap[piece - 1][k / 16 ? ((7 - i) * 8 + j) : (i * 8 + j)];
    }

    return value;
}

bool isInsufficientMaterial()
{
    int knights = 0, bishops = 0;

    for (int i = 0; i < 32; i++)
    {
        if (!isValid(f[i].getPosition()))
            continue;
        if (i == 1 || i == 6 || i == 25 || i == 30)
            knights++;
        else if (i == 2 || i == 5 || i == 26 || i == 29)
            bishops++;
        else if (i != 4 && i != 28)
            return false;
    }

    if (!knights && !bishops)
        return true;
    else if (!knights && bishops == 1)
        return true;
    else if (!bishops && knights)
        return true;
    return false;
}

bool isGameOver()
{
    if (!isValid(f[4].getPosition()) || !isValid(f[28].getPosition()))
        return true;

    if (isInsufficientMaterial())
        return true;

    return false;
}

int minimax(int depth, int alpha, int beta, bool forWhite)
{
    if (!depth || isGameOver())
        return evaluate();

    if (forWhite)
    {
        int maxEval = -1e9;
        for (int i = 16; i < 32; i++)
        {
            std::vector<Vector2f> moves;
            Vector2f pos = f[i].getPosition();

            if (!isValid(pos))
                continue;

            possibleMoves(i, moves);

            for (int j = 0; j < moves.size(); j++)
            {
                std::string str = toChessNote(pos) + toChessNote(moves[j]);

                move(str);
                turns++;
                f[i].setPosition(moves[j]);
                int eval = minimax(depth - 1, alpha, beta, false);
                turns--;
                back(str);

                maxEval = std::max(maxEval, eval);
                alpha = std::max(alpha, eval);

                if (beta <= alpha)
                {
                    i = 32;
                    break;
                }
            }
        }
        return maxEval;
    }
    else
    {
        int minEval = 1e9;
        for (int i = 0; i < 16; i++)
        {
            std::vector<Vector2f> moves;
            Vector2f pos = f[i].getPosition();

            if (!isValid(pos))
                continue;

            possibleMoves(i, moves);

            for (int j = 0; j < moves.size(); j++)
            {
                std::string str = toChessNote(pos) + toChessNote(moves[j]);

                move(str);
                turns++;
                f[i].setPosition(moves[j]);
                int eval = minimax(depth - 1, alpha, beta, true);
                turns--;
                back(str);

                minEval = std::min(minEval, eval);
                beta = std::min(beta, eval);

                if (beta <= alpha)
                {
                    i = 32;
                    break;
                }
            }
        }
        return minEval;
    }
}

std::string minimaxString(int depth, int alpha, int beta)
{
    int minEval = 1e9;
    std::string toReturn = "";

    for (int i = 0; i < 16; i++)
    {
        std::vector<Vector2f> moves;
        Vector2f pos = f[i].getPosition();

        if (!isValid(pos))
            continue;

        possibleMoves(i, moves);

        for (int j = 0; j < moves.size(); j++)
        {
            std::string str = toChessNote(pos) + toChessNote(moves[j]);

            move(str);
            turns++;
            f[i].setPosition(moves[j]);
            int eval = minimax(depth - 1, alpha, beta, true);
            turns--;
            back(str);

            if (minEval > eval)
            {
                minEval = eval;
                toReturn = str;
            }

            if (beta <= alpha)
            {
                i = 32;
                break;
            }
        }
    }
    return toReturn;
}

void compMove(RenderWindow &window, Sprite &sBoard)
{
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

    if (!endGame && isEndGame())
        endGame = true;
    if (!gameOver && isGameOver())
        gameOver = true;

    turns++;
}

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