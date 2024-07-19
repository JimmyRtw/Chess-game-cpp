#include "Board.h"

Board::Board()
{
    init_board();
}

void Board::init_board()
{
    board_texture();
    board_sprite();
}

void Board::draw_board(RenderWindow* window)
{
    window->draw(board_bg_spr);
    window->draw(board_spr);
}

void Board::board_texture()
{
    board_bg_tex.loadFromFile(board_bg_path);
    board_tex.loadFromFile(board_path);

    board_bg_tex.setSmooth(true);
    board_tex.setSmooth(true);
}

void Board::board_sprite()
{
    board_spr.setTexture(board_tex);
    board_spr.setOrigin(440,440);
    board_spr.setPosition(960,540);

    board_bg_spr.setTexture(board_bg_tex);
    board_bg_spr.setOrigin(460,460);
    board_bg_spr.setPosition(960,540);
}
