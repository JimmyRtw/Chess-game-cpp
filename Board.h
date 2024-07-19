#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

using namespace std;
using namespace sf;

#ifndef BOARD_H
#define BOARD_H


class Board
{
    private:

    Texture board_tex,board_bg_tex;
    Sprite board_spr,board_bg_spr;

    string board_path = "./IMAGES/BOARD/chessboard.png";
    string board_bg_path = "./IMAGES/BOARD/chessboardbg.png";

    public:

    Board();

    void init_board();

    void board_texture();
    void board_sprite();

    void draw_board(RenderWindow* window);
};

#endif // BOARD_H
