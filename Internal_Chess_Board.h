#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

#include "Piece.h"

using namespace std;
using namespace sf;

#ifndef INTERNAL_CHESS_BOARD_H
#define INTERNAL_CHESS_BOARD_H


class Internal_Chess_Board
{
private:

    char Icb[64] = {'O','O','O','O','O','O','O','O',
                    'O','O','O','O','O','O','O','O',
                    'O','O','O','O','O','O','O','O',
                    'O','O','O','O','O','O','O','O',
                    'O','O','O','O','O','O','O','O',
                    'O','O','O','O','O','O','O','O',
                    'O','O','O','O','O','O','O','O',
                    'O','O','O','O','O','O','O','O'};

    Piece piece;

    public:

    Internal_Chess_Board();

    char* InternalChessBoard();

    void Set_Initial_Internal_chess_board(string Start_Fen);
    void Update_Internal_chess_board(int nx,int ny,int ox,int oy);
    void Print_Internal_chess_board();
};

#endif // INTERNAL_CHESS_BOARD_H
