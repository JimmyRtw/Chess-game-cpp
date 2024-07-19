#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

using namespace std;
using namespace sf;

#ifndef PIECE_H
#define PIECE_H

class Piece
{
    private:

    //storing of images
    Sprite white_spr[17];
    Sprite black_spr[17];

    //storing of texture
    Texture white_tex[17];
    Texture black_tex[17];

    //image importing path
    string Start_Fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";               //"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
    string common_path = "./IMAGES/CHESS_PIECES/";

    //piece representation in numbers
    const int rook_1 = 0;
    const int rook_2 = 7;

    const int knight_1 = 1;
    const int knight_2 = 6;

    const int bishop_1 = 2;
    const int bishop_2 = 5;

    const int king = 3;
    const int queen = 4;

    const int pawn_1 = 8;
    const int pawn_2 = 9;
    const int pawn_3 = 10;
    const int pawn_4 = 11;
    const int pawn_5 = 12;
    const int pawn_6 = 13;
    const int pawn_7 = 14;
    const int pawn_8 = 15;

    //coordinates

    int row = 155;
    int col = 575;

    int O_X = 575;
    int O_y = 155;

    int X_offset = 110;
    int Y_offset = 110;

    int w_pawn = 0,w_rook = 0,w_bishop = 0,w_knight = 0;
    int b_pawn = 0,b_rook = 0,b_bishop = 0,b_knight = 0;


    public:

    Piece();

    void init_pieces();

    void piece_texture();
    void piece_sprite();

    void Set_Sprite();
    void Set_Origin();
    void Set_Defaults();
    void Set_Position(string Start_Fen);

    void Set_Position_White(float row,float col,char piece);
    void Set_Position_Black(float row,float col,char piece);

    void draw_piece(RenderWindow *window);

    string Start_Fen_string();
    Sprite* white_pieces();
    Sprite* black_pieces();

};

#endif // PIECE_H
