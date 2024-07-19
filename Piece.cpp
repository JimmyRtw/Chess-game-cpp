#include "Piece.h"

void Piece :: Set_Position_White(float row,float col,char piece)
{
    if(piece == 'R')
    {
        if(w_rook==0)
        {
            white_spr[rook_1].setPosition(col,row);
            w_rook++;
        }
        else
        {
            white_spr[rook_2].setPosition(col,row);
        }

    }
    else if(piece == 'K')
    {
        white_spr[king].setPosition(col,row);
    }
    else if(piece == 'B')
    {
        if(w_bishop==0)
        {
            white_spr[bishop_1].setPosition(col,row);
            w_bishop++;
        }
        else
        {
            white_spr[bishop_2].setPosition(col,row);
        }

    }
    else if(piece == 'N')
    {
        if(w_knight==0)
        {
            white_spr[knight_1].setPosition(col,row);
            w_knight++;
        }
        else
        {
            white_spr[knight_2].setPosition(col,row);
        }

    }
    else if(piece == 'Q')
    {
        white_spr[queen].setPosition(col,row);
    }
    else if(piece == 'P')
    {
        if(w_pawn == 0)
        {
            white_spr[pawn_1].setPosition(col,row);
        }
        else if(w_pawn == 1)
        {
            white_spr[pawn_2].setPosition(col,row);
        }
        else if(w_pawn == 2)
        {
            white_spr[pawn_3].setPosition(col,row);
        }
        else if(w_pawn == 3)
        {
            white_spr[pawn_4].setPosition(col,row);
        }
        else if(w_pawn == 4)
        {
            white_spr[pawn_5].setPosition(col,row);
        }
        else if(w_pawn == 5)
        {
            white_spr[pawn_6].setPosition(col,row);
        }
        else if(w_pawn == 6)
        {
            white_spr[pawn_7].setPosition(col,row);
        }
        else if(w_pawn == 7)
        {
            white_spr[pawn_8].setPosition(col,row);
        }

        w_pawn++;
    }
}

void Piece :: Set_Position_Black(float row,float col,char piece)
{
    if(piece == 'r')
    {
        if(b_rook==0)
        {
            black_spr[rook_1].setPosition(col,row);
            b_rook++;
        }
        else
        {
            black_spr[rook_2].setPosition(col,row);
        }

    }
    else if(piece == 'k')
    {
        black_spr[king].setPosition(col,row);
    }
    else if(piece == 'b')
    {
        if(b_bishop==0)
        {
            black_spr[bishop_1].setPosition(col,row);
            b_bishop++;
        }
        else
        {
            black_spr[bishop_2].setPosition(col,row);
        }

    }
    else if(piece == 'n')
    {
        if(b_knight==0)
        {
            black_spr[knight_1].setPosition(col,row);
            b_knight++;
        }
        else
        {
            black_spr[knight_2].setPosition(col,row);
        }

    }
    else if(piece == 'q')
    {
        black_spr[queen].setPosition(col,row);
    }
    else if(piece == 'p')
    {
        if(b_pawn == 0)
        {
            black_spr[pawn_1].setPosition(col,row);
        }
        else if(b_pawn == 1)
        {
            black_spr[pawn_2].setPosition(col,row);
        }
        else if(b_pawn == 2)
        {
            black_spr[pawn_3].setPosition(col,row);
        }
        else if(b_pawn == 3)
        {
            black_spr[pawn_4].setPosition(col,row);
        }
        else if(b_pawn == 4)
        {
            black_spr[pawn_5].setPosition(col,row);
        }
        else if(b_pawn == 5)
        {
            black_spr[pawn_6].setPosition(col,row);
        }
        else if(b_pawn == 6)
        {
            black_spr[pawn_7].setPosition(col,row);
        }
        else if(b_pawn == 7)
        {
            black_spr[pawn_8].setPosition(col,row);
        }

        b_pawn++;
    }
}

void Piece::piece_texture()
{
    for(int i=0; i<17; i++)
    {
        if(i==0||i==7)
        {
            white_tex[i].loadFromFile(common_path+"WHITE\\w_rook.png");
            black_tex[i].loadFromFile(common_path+"BLACK\\b_rook.png");
        }
        else if(i==1||i==6)
        {

            white_tex[i].loadFromFile(common_path+"WHITE\\w_knight.png");
            black_tex[i].loadFromFile(common_path+"BLACK\\b_knight.png");
        }
        else if(i==2||i==5)
        {
            white_tex[i].loadFromFile(common_path+"WHITE\\w_bishop.png");
            black_tex[i].loadFromFile(common_path+"BLACK\\b_bishop.png");

        }
        else if(i==3)
        {
            white_tex[i].loadFromFile(common_path+"WHITE\\w_king.png");
            black_tex[i].loadFromFile(common_path+"BLACK\\b_king.png");

        }
        else if(i==4)
        {
            white_tex[i].loadFromFile(common_path+"WHITE\\w_queen.png");
            black_tex[i].loadFromFile(common_path+"BLACK\\b_queen.png");

        }
        else if(i>7&&i<=15)
        {
            white_tex[i].loadFromFile(common_path+"WHITE\\w_pawn.png");
            black_tex[i].loadFromFile(common_path+"BLACK\\b_pawn.png");
        }
        else if(i==16)
        {
            white_tex[i].loadFromFile(common_path+"WHITE\\w_promotion.png");
            black_tex[i].loadFromFile(common_path+"BLACK\\b_promotion.png");
        }

        white_tex[i].setSmooth(true);
        black_tex[i].setSmooth(true);
    }
}

Piece::Piece()
{
    init_pieces();
}

void Piece::Set_Defaults()
{
    row = 155;
    col = 575;

    w_pawn = 0;w_rook = 0;w_bishop = 0;w_knight = 0;
    b_pawn = 0;b_rook = 0;b_bishop = 0;b_knight = 0;
}

void Piece::Set_Position(string Start_Fen)
{
    Set_Defaults();
    Set_Sprite();
    //setting initial position
    for(int i=0;i<16;i++)
    {
        white_spr[i].setPosition(-55,-55);
        black_spr[i].setPosition(-55,-55);
    }

    white_spr[16].setPosition(-880,-880);
    black_spr[16].setPosition(-880,-880);

    //setting further position
    for(int i=0; i<Start_Fen.size(); i++)
    {
        if(Start_Fen[i] == '/')
        {
            row += Y_offset;
            col = O_X;
        }
        else if((Start_Fen[i]>='A' && Start_Fen[i]<='Z')||((Start_Fen[i]>='a' && Start_Fen[i]<='z')))
        {
            if((Start_Fen[i]>='A' && Start_Fen[i]<='Z'))
            {
                Set_Position_White(row,col,Start_Fen[i]);
            }
            else
            {
                Set_Position_Black(row,col,Start_Fen[i]);
            }

            col += X_offset;
        }
        else if(Start_Fen[i]==' ')
        {
            break;
        }
        else
        {
            col += X_offset*(((Start_Fen[i])-'0'));
        }
    }
}

void Piece::Set_Origin()
{
    for(int i=0; i<17; i++)
    {
        white_spr[i].setOrigin(55,55);
        black_spr[i].setOrigin(55,55);
    }
}

void Piece::Set_Sprite()
{
    for(int i=0; i<17; i++)
    {
        white_spr[i].setTexture(white_tex[i]);
        black_spr[i].setTexture(black_tex[i]);
    }
}

void Piece::init_pieces()
{
    piece_texture();
    piece_sprite();
}

void Piece::piece_sprite()
{
    Set_Sprite();
    Set_Origin();
    Set_Position(Start_Fen);
}

void Piece::draw_piece(RenderWindow *window)
{
    for(int i=0; i<17; i++)
    {
        window->draw(white_spr[i]);
        window->draw(black_spr[i]);
    }
}

string Piece::Start_Fen_string()
{
    return Start_Fen;
}

Sprite* Piece :: white_pieces()
{
    return white_spr;
}
Sprite* Piece :: black_pieces()
{
    return black_spr;
}
