#include "Legal_Moves.h"

int total_moves = 0;

Legal_Moves::Legal_Moves()
{
    init_Nums_Square();
}

void Legal_Moves::count_Nums_Square()
{
    for(int row=0; row<8; row++)
    {
        for(int col=0; col<8; col++)
        {
            int num_up = row;
            int num_down = 7 - row;
            int num_left = col;
            int num_right = 7 - col;


            Nums_Square.push_back({num_up,
                                   num_right,
                                   num_down,
                                   num_left,
                                   min(num_up,num_left),
                                   min(num_up,num_right),
                                   min(num_down,num_right),
                                   min(num_down,num_left)});

        }
    }
}

void Legal_Moves:: print_Nums_Square()
{
    for(int i=0; i<64; i++)
    {
        if(i%8==0)
        {
            cout<<endl;
        }

        cout<<Nums_Square[i][5]<<" ";
    }
}

void Legal_Moves:: init_Nums_Square()
{
    count_Nums_Square();
    //print_Nums_Square();
}

void Legal_Moves:: Generate_Pseudo_Legal_Moves(float x,float y,char *InternalChessBoard,bool Switch)
{
    int row = (y-155)/110;
    int col = (x-575)/110;

    int curr_pos = row*8+col;
    char curr_char = InternalChessBoard[curr_pos];

    if(curr_char=='R'||curr_char=='r')
    {
        Generate_Sliding_Moves(curr_pos,curr_char,InternalChessBoard,0,3,Switch);
    }
    else if(curr_char=='B'||curr_char=='b')
    {
        Generate_Sliding_Moves(curr_pos,curr_char,InternalChessBoard,4,7,Switch);
    }
    else if(curr_char=='Q'||curr_char=='q')
    {
        Generate_Sliding_Moves(curr_pos,curr_char,InternalChessBoard,0,7,Switch);
    }
    else if(curr_char=='P'||curr_char=='p')
    {
        Generate_Pawn_Moves(curr_pos,curr_char,InternalChessBoard,Switch);
    }
    else if(curr_char=='N'||curr_char=='n')
    {
        Generate_Knight_Moves(curr_pos,curr_char,InternalChessBoard,Switch);
    }
    else if(curr_char=='K'||curr_char=='k')
    {
        Generate_King_Moves(curr_pos,curr_char,InternalChessBoard,Switch);
    }
}

void Legal_Moves::Generate_All_Legal_Moves(char*InternalChessBoard,bool white_turn,bool Switch)
{
    vector<int>temp = temp_legal_moves;

    for(int i=0; i<64; i++)
    {
        char curr_char = InternalChessBoard[i];

        if(curr_char=='O'||(white_turn&&(isupper(curr_char)))||(!white_turn&&(islower(curr_char))))
        {
            continue;
        }

        float x = (i%8)*110 + 575;
        float y = (i/8)*110 + 155;

        clear_Vector();

        Generate_Pseudo_Legal_Moves(x,y,InternalChessBoard,Switch);

        All_Enemy_legal_moves.insert(All_Enemy_legal_moves.end(),temp_legal_moves.begin(),temp_legal_moves.end());

    }

    temp_legal_moves = temp;
}

void Legal_Moves::Update_Pseudo_to_Legal(float ox,float oy,Sprite* king,char* icb)
{
    int row = (oy-155)/110,col = (ox-575)/110,pos = row*8+col;
    char curr_char = icb[pos];

    int king_pos = ((king->getPosition().x-575)/110)+((king->getPosition().y-155)/110)*8;

    vector<int>temp_am = All_Enemy_legal_moves;

    char temp_icb[64];
    for(int i=0; i<64; i++)
    {
        temp_icb[i] = icb[i];
    }

    for(int i=0; i<temp_legal_moves.size(); i++)
    {
        int np = temp_legal_moves[i];

        if(curr_char=='K'||curr_char=='k')
        {
            char tr = icb[np];

            icb[pos] = 'O';
            icb[np] = curr_char;

            All_Enemy_legal_moves.clear();

            Generate_All_Legal_Moves(icb,isupper(curr_char)?true:false,false);

            icb[pos] = curr_char;
            icb[np] = tr;

            if(find(All_Enemy_legal_moves.begin(),All_Enemy_legal_moves.end(),np)!=All_Enemy_legal_moves.end())
            {
                temp_legal_moves[i] = 1000;
            }
        }
        else if((curr_char=='P'||curr_char=='P')&&np<0)
        {
            int target_square = isupper(curr_char)?+8:-8;
            char tr = icb[-1*np+target_square];

            icb[pos] = 'O';
            icb[-1*np] = curr_char;
            icb[(-1*np)+target_square] = 'O';

            All_Enemy_legal_moves.clear();

            Generate_All_Legal_Moves(icb,isupper(curr_char)?true:false,false);

            icb[pos] = curr_char;
            icb[-1*np] = 'O';
            icb[(-1*np)+target_square] = tr;

            if(find(All_Enemy_legal_moves.begin(),All_Enemy_legal_moves.end(),king_pos)!=All_Enemy_legal_moves.end())
            {
                temp_legal_moves[i] = 1000;
            }
        }
        else
        {
            char tr = icb[np];

            icb[pos] = 'O';
            icb[np] = curr_char;

            All_Enemy_legal_moves.clear();

            Generate_All_Legal_Moves(icb,isupper(curr_char)?true:false,false);

            icb[pos] = curr_char;
            icb[np] = tr;

            if(find(All_Enemy_legal_moves.begin(),All_Enemy_legal_moves.end(),king_pos)!=All_Enemy_legal_moves.end())
            {
                temp_legal_moves[i] = 1000;
            }
        }
    }

    All_Enemy_legal_moves.clear();
    All_Enemy_legal_moves = temp_am;

    for(int i=0; i<64; i++)
    {
        icb[i] = temp_icb[i];
    }
}

void Legal_Moves::check_checkmate(Shapes* shape,Special_Moves* sm,Sprite* E_Pieces,Sprite* F_Pieces,ScreenText* Move_Count,bool turn,char* icb)
{
    int x = sm->is_check(&E_Pieces[3],All_Enemy_legal_moves);

    shape->set_chs_position((x%8)*110+575,(x/8)*110+155);

    vector<int>check_mate;

    check_mate.clear();

    vector<int>temp_tm = temp_legal_moves;

    bool Move = turn;
    char* board = icb;

    for(int i=0; i<64; i++)
    {
        char curr_piece = board[i];

        if(curr_piece=='O'||(isupper(curr_piece)&&!Move)||(islower(curr_piece)&&Move))
        {
            continue;
        }

        float nox = (i%8)*110+575;
        float noy = (i/8)*110+155;

        temp_legal_moves.clear();
        Generate_Pseudo_Legal_Moves(nox,noy,board,true);
        Update_Pseudo_to_Legal(nox,noy,&E_Pieces[3],board);

        check_mate.insert(check_mate.end(),temp_legal_moves.begin(),temp_legal_moves.end());
    }

    int Count = 0;

    for(auto i:check_mate)
    {
        if(i!=1000)
        {
            Count++;
        }
    }

    string TURN = turn==true?"  (White)":"  (Black)";

    Move_Count->screen_text_change_text(to_string(Count)+TURN);

    if(Count==0)
    {
        if(x>0)
        {
            if(!Move)
            {
                sm->Announce_Winner(&F_Pieces[3],0);
            }
            if(Move)
            {
                sm->Announce_Winner(&F_Pieces[3],1);
            }
        }
        else
        {
            Texture tex;
            Sprite image;

            if(!Move)
            {
                tex.loadFromFile("C:\\GAME\\CHESS\\IMAGES\\BOARD\\white.png");
            }
            else
            {
                tex.loadFromFile("C:\\GAME\\CHESS\\IMAGES\\BOARD\\black.png");
            }

            tex.setSmooth(true);
            image.setTexture(tex);
            image.setOrigin(165,165);
            image.setPosition(220,250);

            sm->Announce_Winner(&image,2);
        }
    }

    temp_legal_moves = temp_tm;
}

//void Legal_Moves::Verify_my_chess(Shapes* shape,Special_Moves* sm,Sprite* E_Pieces,Sprite* F_Pieces,Internal_Chess_Board* ICB,bool turn,char* icb,string Start_Fen)
//{
//    vector<int>total_legal_moves;
//    vector<int>temp_tm = temp_legal_moves;
//
//    string p,s,q,r;
//
//    bool Move = turn;
//    char* board = icb;
//
//    for(int I=0; I<depth; I++)
//    {
//        for(int i=0; i<64; i++)
//        {
//            if(board[i]=='O')
//            {
//                continue;
//            }
//
//            if(Move&&(isupper(board[i])))
//            {
//                temp_legal_moves.clear();
//                lm->Generate_Pseudo_Legal_Moves(i%8*110+575,i/8*110+155,board,true);                                //looking for all pseudo legal moves
//                lm->Update_Pseudo_to_Legal(ox,oy,&F_Pieces[3],board);
//                vector<int>vec1 = temp_legal_moves;
//
//                for(auto j:vec1)
//                {
//                    string MOVE =  Generate_Move_notation(i%8*110+575,i/8*110+155,j%8*110+575,j/8*110+155);
//                    p = s;
//                    s = updated_fen_string(s,MOVE,-1);
//
//                    ICB->Set_Initial_Internal_chess_board(s);
//                    sm->init_special_moves(s,Move);
//
//                    for(int k=0; k<64; k++)
//                    {
//                        if(board[k]=='O')
//                        {
//                            continue;
//                        }
//
//                        if(!Move&&(islower(board[k])))
//                        {
//                            temp_legal_moves.clear();
//                            lm->Generate_Pseudo_Legal_Moves(k%8*110+575,k/8*110+155,board,true);                                //looking for all pseudo legal moves
//                            lm->Update_Pseudo_to_Legal(k%8*110+575,k/8*110+155,&E_Pieces[3],board);
//
//                            total_legal_moves.insert(total_legal_moves.end(),temp_legal_moves.begin(),temp_legal_moves.end());
//                        }
//
//                    }
//
//                    ICB->Set_Initial_Internal_chess_board(p);
//                }
//
//                total_legal_moves.insert(total_legal_moves.end(),vec1.begin(),vec1.end());
//            }
//
//        }
//        cout<<"depth : "<<I<" "<<"total moves :"<<total_legal_moves.size()<<endl;
//    }
//
//    temp_legal_moves.clear();
//}
void Legal_Moves::Generate_Sliding_Moves(int curr_pos,char curr_char,char* InternalChessBoard,int start_dir,int end_dir,bool Switch)
{
    for(int dir=start_dir; dir<=end_dir; dir++)
    {
        int Legal_Square = curr_pos;

        for(int i=0; i<Nums_Square[curr_pos][dir]; i++ )
        {
            char At_Square = InternalChessBoard[Legal_Square+sliding_direction[dir]];

            if(((isupper(At_Square)&&isupper(curr_char))||(islower(At_Square)&&islower(curr_char)))&&(At_Square!='O'))
            {
                //friendly piece in a way so we skip to the next sliding direction
                if(!Switch)
                {
                    temp_legal_moves.push_back(Legal_Square+sliding_direction[dir]);
                }

                break;
            }

            temp_legal_moves.push_back(Legal_Square+sliding_direction[dir]);

            if(((isupper(At_Square)&&islower(curr_char))||(islower(At_Square)&&isupper(curr_char)))&&(At_Square!='O'))
            {
                //opposite color piece is on this square so we capture it and skip to the next sliding direction
                break;
            }

            Legal_Square+=sliding_direction[dir];
        }
    }
}

void Legal_Moves::Generate_Pawn_Moves(int curr_pos,char curr_char,char* InternalChessBoard,bool Switch)
{
    int x,y,pos;
    char At_Square;

    int scaler = curr_char=='p'?1:-1;

    if(scaler==1)
    {
        if((curr_pos/8)==1)
        {
            for(int i=0; i<4; i++)
            {
                x = curr_pos%8;
                y = curr_pos/8;

                x += pawn_direction[i][1]*scaler;
                y += pawn_direction[i][0]*scaler;

                pos = y*8+x;

                At_Square = InternalChessBoard[pos];

                if(i<2)
                {
                    if(!Switch&&(x>=0&&x<8&&y>=0&&y<8))
                    {
                        temp_legal_moves.push_back(pos);
                    }
                    else if((x>=0&&x<8&&y>=0&&y<8)&&(islower(curr_char)&&isupper(At_Square))&&(At_Square!='O'))
                    {
                        temp_legal_moves.push_back(pos);
                    }
                }
                else if(Switch)
                {
                    if((x>=0&&x<8&&y>=0&&y<8)&&(At_Square=='O'))
                    {
                        temp_legal_moves.push_back(pos);
                    }
                    else
                    {
                        break;
                    }
                }
            }

            return;
        }
    }
    else
    {
        if((curr_pos/8)==6)
        {
            for(int i=0; i<4; i++)
            {
                x = curr_pos%8;
                y = curr_pos/8;

                x += pawn_direction[i][1]*scaler;
                y += pawn_direction[i][0]*scaler;

                pos = y*8+x;

                At_Square = InternalChessBoard[pos];

                if(i<2)
                {
                    if(!Switch&&(x>=0&&x<8&&y>=0&&y<8))
                    {
                        temp_legal_moves.push_back(pos);
                    }
                    else if((x>=0&&x<8&&y>=0&&y<8)&&(islower(At_Square)&&isupper(curr_char))&&(At_Square!='O'))
                    {
                        temp_legal_moves.push_back(pos);
                    }
                }
                else if(Switch)
                {
                    if((x>=0&&x<8&&y>=0&&y<8)&&(At_Square=='O'))
                    {
                        temp_legal_moves.push_back(pos);
                    }
                    else
                    {
                        break;
                    }
                }
            }

            return;
        }
    }

    for(int i=0; i<3; i++)
    {
        x = curr_pos%8;
        y = curr_pos/8;

        x += pawn_direction[i][1]*scaler;
        y += pawn_direction[i][0]*scaler;

        pos = y*8+x;

        At_Square = InternalChessBoard[pos];

        if(i<2)
        {
            if(!Switch&&(x>=0&&x<8&&y>=0&&y<8))
            {
                temp_legal_moves.push_back(pos);
            }
            else if((x>=0&&x<8&&y>=0&&y<8)&&((islower(At_Square)&&isupper(curr_char))||(islower(curr_char)&&isupper(At_Square)))&&(At_Square!='O'))
            {
                temp_legal_moves.push_back(pos);
            }
        }
        else if(Switch)
        {
            if((x>=0&&x<8&&y>=0&&y<8)&&(At_Square=='O'))
            {
                temp_legal_moves.push_back(pos);
            }
        }
    }

    int e_pos = 0;

    if(Switch)
    {
        e_pos = sm->can_passent(curr_pos%8,curr_pos/8,InternalChessBoard);
    }
    else
    {
        return;
    }

    if(e_pos&&(Switch))
    {
        temp_legal_moves.push_back(-e_pos);
    }
}

void Legal_Moves::Generate_Knight_Moves(int curr_pos,char curr_char,char* InternalChessBoard,bool Switch)
{
    int x,y,pos;
    char At_Square;

    for(int i=0; i<8; i++)
    {
        x = curr_pos%8;
        y = curr_pos/8;

        x += horse_direction[i][0];
        y += horse_direction[i][1];

        pos = y*8+x;

        At_Square = InternalChessBoard[pos];

        if(!Switch&&(x>=0&&x<8&&y>=0&&y<8))
        {
            temp_legal_moves.push_back(pos);
        }
        else if((x>=0&&x<8&&y>=0&&y<8)&&(At_Square=='O'))
        {
            temp_legal_moves.push_back(pos);
        }
        else if((x>=0&&x<8&&y>=0&&y<8)&&((isupper(At_Square)&&islower(curr_char))||(islower(At_Square)&&isupper(curr_char))))
        {
            temp_legal_moves.push_back(pos);
        }
    }
}

void Legal_Moves::Generate_King_Moves(int curr_pos,char curr_char,char* InternalChessBoard,bool Switch)
{
    int x,y,pos;
    char At_Square;

    for(int i=0; i<8; i++)
    {
        x = curr_pos%8;
        y = curr_pos/8;

        x += king_direction[i][1];
        y += king_direction[i][0];

        pos = y*8+x;

        At_Square = InternalChessBoard[pos];

        if(!Switch&&(x>=0&&x<8&&y>=0&&y<8))
        {
            temp_legal_moves.push_back(pos);
        }
        else if((x>=0&&x<8&&y>=0&&y<8)&&(At_Square=='O'))
        {
            temp_legal_moves.push_back(pos);
        }
        else if((x>=0&&x<8&&y>=0&&y<8)&&((isupper(At_Square)&&islower(curr_char))||(islower(At_Square)&&isupper(curr_char))))
        {
            temp_legal_moves.push_back(pos);
        }
    }

    vector<int>invalid = All_Enemy_legal_moves;

    if((Switch)&&sm->can_castle_ks(invalid,curr_pos,curr_char,InternalChessBoard))
    {
        temp_legal_moves.push_back(-(curr_pos+2));
    }

    if((Switch)&&sm->can_castle_qs(invalid,curr_pos,curr_char,InternalChessBoard))
    {
        temp_legal_moves.push_back(-(curr_pos-2));
    }

}

void Legal_Moves::clear_Vector()
{
    temp_legal_moves.clear();
}

vector<int> Legal_Moves::return_Legal_Move()
{
    return temp_legal_moves;
}

void Legal_Moves::clear_Enemy()
{
    All_Enemy_legal_moves.clear();
}

vector<int> Legal_Moves::return_Enemy()
{
    return All_Enemy_legal_moves;
}

int Legal_Moves::is_legal_move(float nx,float ny,float ox,float oy,char ibc[],Sprite* Enemy)
{
    int ncol = (nx-575)/110;
    int nrow = (ny-155)/110;

    int desitination = nrow*8+ncol;

    if(!(nrow>=0&&nrow<8&&ncol>=0&&ncol<8))
    {
        return 0;
    }
    else if(find(temp_legal_moves.begin(),temp_legal_moves.end(),desitination)==temp_legal_moves.end()&&find(temp_legal_moves.begin(),temp_legal_moves.end(),-desitination)==temp_legal_moves.end())
    {
        return 0;
    }
    else
    {
        if(ibc[desitination]=='O')
        {
            return 1;
        }
        else
        {
            capture_piece(nx,ny,Enemy);
            return 2;
        }
    }
}

void Legal_Moves::capture_piece(float nx,float ny,Sprite* Enemy)
{
    for(int i=0; i<16; i++)
    {
        if((nx==Enemy[i].getPosition().x)&&(ny==Enemy[i].getPosition().y))
        {
            Enemy[i].setPosition(-55,-55);
            return;
        }
    }
}

string Legal_Moves::updated_fen_string(string Start_Fen,string Move,int spm)
{
    int curr_row = 8 - int(Move[1])+'0',des_row = 8 - int(Move[3])+'0',curr_col = int(Move[0]-'a'),des_col = int(Move[2]-'a');

    string s = Start_Fen,word,curr_seg,des_seg;
    stringstream ss(s);

    int j = 0;

    while(getline(ss,word,'/'))
    {
        // 8/8/8/2qk4/8/4P3/6PP/4K2R w K -
        if(j==curr_row)
        {
            int i = 0;

            while((i<word.size())&&word[i]!=' ')
            {
                curr_seg+=word[i];
                i++;
            }
        }
        if(j==des_row)
        {
            int i = 0;

            while((i<word.size())&&word[i]!=' ')
            {
                des_seg+=word[i];
                i++;
            }
        }
        j++;
    }

    string new_curr_seg = "";

    for(int i=0; i<curr_seg.size(); i++)
    {
        char c = curr_seg[i];

        if(!((c>='A'&&c<='Z')||(c>='a'&&c<='z')))
        {
            int n = int(c)-'0';
            string temp(n,'1');
            new_curr_seg += temp;
        }
        else
        {
            new_curr_seg+=c;
        }
    }

    string new_des_seg = "";

    for(int i=0; i<des_seg.size(); i++)
    {
        char c = des_seg[i];

        if(!((c>='A'&&c<='Z')||(c>='a'&&c<='z')))
        {
            int n = int(c)-'0';
            string temp(n,'1');
            new_des_seg += temp;
        }
        else
        {
            new_des_seg += c;
        }
    }

    bool is_Same = new_des_seg==new_curr_seg?false:true;

    char curr_char = new_curr_seg[curr_col],des_char = new_des_seg[des_col];

    new_curr_seg[curr_col] = '1';

    if((curr_char=='P'||curr_char=='p')&&spm==2)
    {
        new_curr_seg[des_col] = '1';
    }
    if((curr_char=='K'||curr_char=='k')&&spm==1)
    {
        new_curr_seg[des_col] = curr_char;
        new_curr_seg[des_col-1] = isupper(curr_char)?'R':'r';
        new_curr_seg[des_col+1] = '1';
    }
    if((curr_char=='K'||curr_char=='k')&&spm==2)
    {
        new_curr_seg[des_col] = curr_char;
        new_curr_seg[des_col+1] = isupper(curr_char)?'R':'r';
        new_curr_seg[des_col-2] = '1';
    }

    if(des_row==curr_row)
    {
        new_curr_seg[des_col] = curr_char;
    }

    spm!=3?new_des_seg[des_col] = curr_char:new_des_seg[des_col] = Move[4];

    string old_curr_seg = "";

    for(int i=0; i<new_curr_seg.size(); i++)
    {
        char c = new_curr_seg[i];

        if(c>='0'&&c<='8')
        {
            int temp = 0;

            while(new_curr_seg[i]=='1')
            {
                temp++;
                i++;
            }
            i--;
            old_curr_seg += to_string(temp);
        }
        else
        {
            old_curr_seg+=c;
        }
    }

    string old_des_seg = "";

    for(int i=0; i<new_des_seg.size(); i++)
    {
        char c = new_des_seg[i];

        if(c>='0'&&c<='8')
        {
            int temp = 0;

            while(new_des_seg[i]=='1')
            {
                temp++;
                i++;
            }
            i--;
            old_des_seg += to_string(temp);
        }
        else
        {
            old_des_seg += c;
        }
    }

    string updated_fen = "";

    int k=0;

    string m = Start_Fen,w;
    stringstream kk(m);

    while(getline(kk,w,'/'))
    {
        if(k==curr_row)
        {
            updated_fen+=old_curr_seg+'/';
        }
        else if(k==des_row)
        {
            updated_fen+=old_des_seg+'/';
        }
        else
        {
            updated_fen+=w+'/';
        }
        k++;
    }

    updated_fen.pop_back();

    string updated_fen_dup = updated_fen;

    int p=0;

    string o = updated_fen_dup,x;
    stringstream jj(o);

    while(getline(jj,x,' '))
    {
        if(p==0)
        {
            updated_fen = x;
            break;
        }
        p++;
    }

    int l=0;

    string back_part = "";

    string n = word,v;
    stringstream ll(n);

    while(getline(ll,v,' '))
    {
        if(l==1)
        {
            if(v=="w")
            {
                back_part+="b ";
            }
            else
            {
                back_part+="w ";
            }
        }
        else if(l==3)
        {
            if(curr_char=='p'&&(curr_row+2==des_row))
            {
                back_part+= Move[0]+to_string(7-curr_row)+' ';
            }
            else if(curr_char=='P'&&(curr_row-2==des_row))
            {
                back_part+= Move[0]+to_string(9-curr_row)+' ';
            }
            else
            {
                back_part+="- ";
            }
        }
        else if(l==2)
        {
            vector<bool>per = sm->castling_permissions();
            bool dash = true;

            if(per[0])
            {
                back_part+='K';
                dash=false;
            }
            if(per[1])
            {
                back_part+='Q';
                dash=false;
            }
            if(per[2])
            {
                back_part+='k';
                dash=false;
            }
            if(per[3])
            {
                back_part+='q';
                dash=false;
            }

            if(dash)
            {
                back_part+="-";
            }

            back_part+=' ';
        }
        else if(l==4)
        {
            int x = stoi(v);

            if(curr_char=='p'||curr_char=='P')
            {
                x = 0;
            }
            else if(des_char!='1')
            {
                x = 0;
            }
            else
            {
                x++;
            }

            back_part+=to_string(x)+' ';
        }
        else if(l==5)
        {
            int x = stoi(v);

            if(islower(curr_char))
            {
                x++;
            }

            back_part+=to_string(x)+' ';
        }
        l++;
    }

    updated_fen = updated_fen+' '+ back_part;

    return updated_fen;
}

string Legal_Moves::Generate_Move_notation(float ox,float oy,float nx,float ny)
{
    int orow = (oy-155)/110,ocol = ((ox-575)/110),nrow = (ny-155)/110,ncol = ((nx-575)/110);

    orow = 8 - orow;
    nrow = 8 - nrow;

    return char(ocol+'a')+to_string(orow)+char(ncol+'a')+to_string(nrow);
}

void Legal_Moves::undo_move(Internal_Chess_Board*icb,Piece*piece,Special_Moves*sm,Shapes* shape,Sounds* sound,bool* white_turn,string* s)
{
    if(undo.size()==1)
    {
        return;
    }

    sound->play_undo_Sound();

    redo.push(undo.top());
    undo.pop();

    string s1 = undo.top().first;
    string s2 = undo.top().second;

    *s = s1;

    icb->Set_Initial_Internal_chess_board(s1);
    piece->Set_Position(s1);
    sm->init_special_moves(s1,white_turn);
    clear_Enemy();
    Generate_All_Legal_Moves(icb->InternalChessBoard(),*white_turn,false);

    int curr_row = 8 - int(s2[1])+'0',des_row = 8 - int(s2[3])+'0',curr_col = int(s2[0]-'a'),des_col = int(s2[2]-'a');

    shape->set_yls_position(curr_col*110+575,curr_row*110+155);
    shape->set_yds_position(des_col*110+575,des_row*110+155);
    shape->set_gls_position(-500,-500);
    shape->set_chs_position(-500,-500);
}

void Legal_Moves::redo_move(Internal_Chess_Board*icb,Piece*piece,Special_Moves*sm,Shapes* shape,Sounds* sound,bool* white_turn,string* s)
{
    if(redo.empty())
    {
        return ;
    }

    sound->play_redo_Sound();

    undo.push(redo.top());
    redo.pop();

    string s1 = undo.top().first;
    string s2 = undo.top().second;

    *s = s1;

    icb->Set_Initial_Internal_chess_board(s1);
    piece->Set_Position(s1);
    sm->init_special_moves(s1,white_turn);
    clear_Enemy();
    Generate_All_Legal_Moves(icb->InternalChessBoard(),*white_turn,false);

    int curr_row = 8 - int(s2[1])+'0',des_row = 8 - int(s2[3])+'0',curr_col = int(s2[0]-'a'),des_col = int(s2[2]-'a');

    shape->set_yls_position(curr_col*110+575,curr_row*110+155);
    shape->set_yds_position(des_col*110+575,des_row*110+155);
    shape->set_gls_position(-500,-500);
    shape->set_chs_position(-500,-500);

}

void Legal_Moves::push_undo_move(string s1,string s2)
{
    undo.push({s1,s2});
}

void Legal_Moves::do_empty()
{
    while(undo.size()>1)
    {
        undo.pop();
    }

    while(!redo.empty())
    {
        redo.pop();
    }
}

