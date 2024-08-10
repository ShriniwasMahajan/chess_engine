#include "ai.h"
#include "board.h"
#include "pieces.h"
#include "game.h"
using namespace sf;

bool endGame = false;
int turns = 1;

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