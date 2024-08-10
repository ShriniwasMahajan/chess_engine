#include "board.h"
#include "pieces.h"
using namespace sf;

Sprite f[32];
std::vector<std::pair<int, int>> defeated;

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

int findPieceAt(Vector2f pos)
{
    for (int i = 0; i < 32; i++)
        if (f[i].getPosition() == pos)
            return i;
    return -1;
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