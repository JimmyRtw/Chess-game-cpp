#include "Play.h"

void Play::init_objects(Shapes* SHAPE,Internal_Chess_Board* ICB,Piece* PIECE,Legal_Moves* LM,Sounds* SOUND,Button* RESTART,Button* QUITE,ScreenText* LAST_MOVE,ScreenText*MOVE,ScreenText *LEGAL_MOVES,ScreenText *MOVE_COUNT)
{
    shape = SHAPE;
    icb = ICB;
    piece = PIECE;
    lm = LM;
    sound = SOUND;
    Restart = RESTART;
    Quite = QUITE;
    Last_Move = LAST_MOVE;
    Curr_Move = MOVE;
    Legal_moves = LEGAL_MOVES;
    Move_Count = MOVE_COUNT;

    static bool once = true;

    if(once)
    {
        curr_fent_string = piece->Start_Fen_string();
        lm->push_undo_move(curr_fent_string,"");
        icb->Set_Initial_Internal_chess_board(piece->Start_Fen_string());
        sm->init_special_moves(piece->Start_Fen_string(),&white_turn);
        lm->Generate_All_Legal_Moves(icb->InternalChessBoard(),white_turn,false);
        lm->check_checkmate(shape,sm,F_Pieces,E_Pieces,Move_Count,white_turn,icb->InternalChessBoard());
        once = false;
        //shape->set_aas_position(lm->return_Enemy());
    }
}

void Play::set_turn(Sprite* white,Sprite* black)
{
    if(white_turn)
    {
        F_Pieces = white;
        E_Pieces = black;
    }
    else
    {
        F_Pieces = black;
        E_Pieces = white;
    }
}

void Play::do_events(Event event,int x,int y)
{
    Restart->hower_over_button(x,y);
    Quite->hower_over_button(x,y);

    if(Restart->is_button_clicked(x,y,event))
    {
        Restart_Game();
    }

    if(Quite->is_button_clicked(x,y,event))
    {
        exit(0);
    }

    if((event.type == Event::KeyPressed)&&(event.key.code == Keyboard::Backspace))
    {
        lm->undo_move(icb,piece,sm,shape,sound,&white_turn,&curr_fent_string);
    }
    if((event.type == Event::KeyPressed)&&(event.key.code == Keyboard::Delete))
    {
        lm->redo_move(icb,piece,sm,shape,sound,&white_turn,&curr_fent_string);
    }
}

void Play::Pick_Pieces(Event event,int MX,int MY)
{
    if((event.type==Event::MouseButtonPressed)&&(event.key.code==Mouse::Left))
    {
        for(int i=0; i<17; i++)
        {
            if(F_Pieces[i].getGlobalBounds().contains(MX,MY))
            {
                do_things_1(i,MX,MY);
                return;
            }
        }
    }
}

void Play::Hower_Pieces(Event event,int MX,int MY)
{
    if(is_move)
    {
        F_Pieces[n].setPosition(MX,MY);
    }
}

void Play::Release_Pieces(Event event)
{
    if((event.type==Event::MouseButtonReleased)&&(event.key.code==Mouse::Left)&&(is_move==true))
    {
        is_move = false;

        Vector2f p = F_Pieces[n].getPosition();

        nx = 575+110*int(((p.x+55)-575)/110);
        ny = 155+110*int(((p.y+55)-155)/110);

        do_things_2(nx,ny);
    }
}

void Play::Game(Sprite* white,Sprite* black,int MX,int MY,Event event,Shapes *SHAPE,Internal_Chess_Board* ICB,Piece* PIECE,Legal_Moves* LM,Sounds* SOUND,Button* RESTART,Button* QUITE,ScreenText *LAST_MOVE,ScreenText *MOVE,ScreenText *LEGAL_MOVES,ScreenText *MOVE_COUNT)
{
    set_turn(white,black);
    init_objects(SHAPE,ICB,PIECE,LM,SOUND,RESTART,QUITE,LAST_MOVE,MOVE,LEGAL_MOVES,MOVE_COUNT);
    do_events(event,MX,MY);
    Pick_Pieces(event,MX,MY);
    Hower_Pieces(event,MX,MY);
    Release_Pieces(event);
}

void Play::do_things_1(int i,int MX,int MY)
{
    n = i;

    if(i==16)
    {
        char promoted = sm->promote(F_Pieces,icb->InternalChessBoard(),MX,MY,n,&white_turn);
        lm->clear_Enemy();
        lm->Generate_All_Legal_Moves(icb->InternalChessBoard(),white_turn,false);
        lm->check_checkmate(shape,sm,E_Pieces,F_Pieces,Move_Count,white_turn,icb->InternalChessBoard());

        curr_fent_string = lm->updated_fen_string(curr_fent_string,lm->Generate_Move_notation(ox,oy,nx,ny)+promoted,3);

        lm->push_undo_move(curr_fent_string,lm->Generate_Move_notation(ox,oy,nx,ny));
        Curr_Move->screen_text_change_text(lm->Generate_Move_notation(ox,oy,nx,ny)+promoted);

        //shape->set_aas_position(lm->return_Enemy());
        return;
    }

    is_move = true;

    ox = F_Pieces[i].getPosition().x;
    oy = F_Pieces[i].getPosition().y;
                                                                                                            //looking for all enemy captures
    lm->Generate_Pseudo_Legal_Moves(ox,oy,icb->InternalChessBoard(),true);                                //looking for all pseudo legal moves
    lm->Update_Pseudo_to_Legal(ox,oy,&F_Pieces[3],icb->InternalChessBoard());

    shape->set_rds_position(lm->return_Legal_Move());
    shape->set_gls_position(ox,oy);
}

void Play::do_things_2(float nx,float ny)
{
    int Move = lm->is_legal_move(nx,ny,ox,oy,icb->InternalChessBoard(),E_Pieces);

    if(Move)
    {
        F_Pieces[n].setPosition(nx,ny);

        shape->set_rds_position(vector<int>());

        lm->clear_Vector();

        if(ox!=nx||oy!=ny)
        {
            shape->set_yls_position(ox,oy);
            shape->set_yds_position(nx,ny);

            icb->Update_Internal_chess_board(nx,ny,ox,oy);

            if(sm->set_passent(ox,oy,nx,ny,icb->InternalChessBoard(),E_Pieces)==2){Move=2;psm=2;}

            if(sm->set_promotion(F_Pieces,nx,ny,icb->InternalChessBoard(),n,Move,sound)){return;}

            if(sm->Castle(ox,oy,nx,ny,icb->InternalChessBoard(),F_Pieces)){psm = sm->Castle(ox,oy,nx,ny,icb->InternalChessBoard(),F_Pieces);}

            sm->false_castle(white_turn,n);

            lm->clear_Enemy();
            lm->Generate_All_Legal_Moves(icb->InternalChessBoard(),!white_turn,false);

            string s = lm->Generate_Move_notation(ox,oy,nx,ny);

            curr_fent_string = lm->updated_fen_string(curr_fent_string,s,psm);

            //shape->set_aas_position(lm->return_Enemy());
            lm->push_undo_move(curr_fent_string,s);
            Curr_Move->screen_text_change_text(s);

            Move==1?sound->play_move_Sound():sound->play_capture_Sound();
            white_turn=!white_turn;

            lm->check_checkmate(shape,sm,E_Pieces,F_Pieces,Move_Count,white_turn,icb->InternalChessBoard());
            psm = -1;
        }
    }
    else
    {
        shape->set_rds_position(vector<int>());
        lm->clear_Vector();

        F_Pieces[n].setPosition(ox,oy);
    }
}

void Play::Restart_Game()
{
    white_turn = true;
    shape->set_chs_position(-55,-55);shape->set_gls_position(-55,-55);shape->set_yds_position(-55,-55);shape->set_yls_position(-55,-55);

    curr_fent_string = piece->Start_Fen_string();

    sm->init_special_moves(piece->Start_Fen_string(),&white_turn);
    icb->Set_Initial_Internal_chess_board(piece->Start_Fen_string());
    lm->do_empty();
    lm->clear_Enemy();
    lm->Generate_All_Legal_Moves(icb->InternalChessBoard(),white_turn,false);
    //lm->check_checkmate(shape,sm,E_Pieces,F_Pieces,Move_Count,white_turn,icb->InternalChessBoard());
    shape->set_chs_position(-500,-500);
    Curr_Move->screen_text_change_text("-");
    //shape->set_aas_position(lm->return_Enemy());
    piece->Set_Position(piece->Start_Fen_string());
}
