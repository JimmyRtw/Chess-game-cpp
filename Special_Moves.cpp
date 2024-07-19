#include "Special_Moves.h"

bool wks=false,wqs=false,bks=false,bqs=false;
Sounds* sound;
int MX,MY;
Sprite* piece;
char curr_char;
float NX,NY;
int POS;
int lcol=0,rcol=0;

vector<int>ep_active = {0,0,0,0,0,0,0,0};

Special_Moves::Special_Moves()
{
    //ctor
}

void Special_Moves::init_special_moves(string Start_Fen,bool* white_turn)
{
    int i=0;

    ep_active = {0,0,0,0,0,0,0,0},lcol=0,rcol=0;
    wks=false,wqs=false,bks=false,bqs=false;

    string s = Start_Fen;
    stringstream ss(s);
    string word;

    while(getline(ss,word,' '))
    {
        if(i==0)
        {
            i++;
            continue;
        }
        if(i==1)
        {
            word=="w"?*(white_turn)=true:*(white_turn)=false;
        }
        else if(i==2)
        {
            for(int j=0;j<word.size();j++)
            {
                char c = word[j];

                if(c=='K'){wks = true;}
                if(c=='Q'){wqs = true;}
                if(c=='k'){bks = true;}
                if(c=='q'){bqs = true;}
            }
        }
        else if(i==3)
        {
            if(word!='-')
            {
                int col = int(word[0])-'a';
                int row = int(word[1]-'0');

                int s_col = col;

                string n = Start_Fen,v,curr_seg = "";
                stringstream ll(n);

                int r = *white_turn==true?3:4,j=0;

                while(getline(ll,v,'/'))
                {
                    if(j==r)
                    {
                        for(int i=0;i<v.size();i++)
                        {
                            char c = v[i];

                            if(c==' '){break;}

                            if(!((c>='A'&&c<='Z')||(c>='a'&&c<='z')))
                            {
                                int n = int(c)-'0';
                                string temp(n,'1');
                                curr_seg += temp;
                            }
                            else
                            {
                                curr_seg += c;
                            }
                        }
                        break;
                    }
                    j++;
                }

                char you = *white_turn==true?'P':'p';

                if(((col+1>=0&&col+1<=7)&&(curr_seg[col+1]==you)))
                {
                    rcol = col+1;
                    ep_active[col+1] = (8-row)*8+col;
                }
                if(((col-1>=0&&col-1<=7)&&(curr_seg[col-1]==you)))
                {
                    lcol = col-1;
                    ep_active[col-1] = (8-row)*8+col;
                }
            }
        }
        i++;
    }
}

vector<bool> Special_Moves::castling_permissions()
{
    vector<bool>permissions = {wks,wqs,bks,bqs};

    return permissions;
}

bool Special_Moves::can_castle_qs(vector<int>invalid,int curr_pos,char curr_char,char* icb)
{
    int index = isupper(curr_char)?1:0;

    if((index==1)&&(wqs==false))
    {
        return false;
    }
    else if((index==0)&&(bqs==false))
    {
        return false;
    }

    if(find(invalid.begin(),invalid.end(),curr_pos)!=invalid.end())
    {
        return false;
    }

    for(int i=curr_pos-3;i<curr_pos;i++)
    {
        if(find(invalid.begin(),invalid.end(),i)!=invalid.end())
        {
            return false;
        }
        if(icb[i]!='O')
        {
            return false;
        }
    }

    if(isupper(curr_char)&&icb[curr_pos-4]!='R')
    {
        return false;
    }
    else if(islower(curr_char)&&icb[curr_pos-4]!='r')
    {
        return false;
    }

    return true;
}

bool Special_Moves::can_castle_ks(vector<int>invalid,int curr_pos,char curr_char,char* icb)
{
    int index = isupper(curr_char)?1:0;

    if((index==1)&&(wks==false))
    {
        return false;
    }
    else if((index==0)&&(bks==false))
    {
        return false;
    }

    if(find(invalid.begin(),invalid.end(),curr_pos)!=invalid.end())
    {
        return false;
    }

    for(int i=curr_pos+1;i<curr_pos+3;i++)
    {
        if(find(invalid.begin(),invalid.end(),i)!=invalid.end())
        {
            return false;
        }
        if(icb[i]!='O')
        {
            return false;
        }
    }

    if(isupper(curr_char)&&icb[curr_pos+3]!='R')
    {
        return false;
    }
    else if(islower(curr_char)&&icb[curr_pos+3]!='r')
    {
        return false;
    }

    return true;
}

int Special_Moves::Castle(float ox,float oy,float nx,float ny,char* icb,Sprite* pieces)
{
    int np = ((nx-575)/110) + ((ny-155)/110)*8;
    int op = ((ox-575)/110) + ((oy-155)/110)*8;

    char curr_char = icb[np];

    if(curr_char=='K'||curr_char=='k')
    {
        if(np==(op+2))
        {
            pieces[7].setPosition(nx-110,ny);

            icb[np+1] = 'O';
            icb[np-1] = isupper(icb[np])?'R':'r';

            return 1;
        }
        else if(np==(op-2))
        {
            pieces[0].setPosition(nx+110,ny);

            icb[np-2] = 'O';
            icb[np+1] = isupper(icb[np])?'R':'r';

            return 2;
        }
    }

    return 0;
}

void Special_Moves::false_castle(bool Turn,int n)
{
    int turn = Turn==true?1:0;

    if(n==3)
    {
        if(turn==1)
        {
            wks = false;
            wqs = false;
        }
        else
        {
            bks = false;
            bqs = false;
        }
    }
    if(n==0)
    {
        if(turn==1)
        {
            wqs = false;
        }
        else
        {
            bqs = false;
        }
    }

    if(n==7)
    {
       if(turn==1)
        {
            wks = false;
        }
        else
        {
            bks = false;
        }
    }
}

int Special_Moves::set_passent(float ox,float oy,float nx,float ny,char* icb,Sprite* Enemy)
{
    int orow = (oy-155)/110,ocol = (ox-575)/110,nrow = (ny-155)/110,ncol = (nx-575)/110;

    int op = orow*8+ocol;
    int np = nrow*8+ncol;

    char curr_char = icb[np];

    int colour = isupper(curr_char)?1:0;

    if(((np==(op+16))||(np==(op-16)))&&(curr_char=='P'||curr_char=='p'))
    {
        int l=np-1,r=np+1;

        char opponent = colour==1?'p':'P';

        if((l%8>=0&&l%8<=7)&&(icb[l]==opponent))
        {
            ep_active[l%8] = colour==1?np+8:np-8;
            lcol = l%8;
        }
        if((r%8>=0&&r%8<=7)&&(icb[r]==opponent))
        {
            ep_active[r%8] = colour==1?np+8:np-8;
            rcol = r%8;
        }
    }
    else if((np==ep_active[lcol]||np==ep_active[rcol])&&(curr_char=='P'||curr_char=='p'))
    {
        ep_active[lcol] = 0;
        ep_active[rcol] = 0;

        for(int i=8;i<16;i++)
        {
            if(Enemy[i].getPosition().x==nx)
            {
                if(Enemy[i].getPosition().y==(ny-110)||Enemy[i].getPosition().y==(ny+110))
                {
                    int col = (nx-575)/110,row = (Enemy[i].getPosition().y-155)/110;

                    Enemy[i].setPosition(-55,-55);

                    icb[row*8+col] = 'O';

                    return 2;
                }
            }
        }
    }
    else
    {
        ep_active[lcol] = 0;
        ep_active[rcol] = 0;
    }

    return 1;
}

int Special_Moves::can_passent(int ocol,int orow,char* icb)
{
    char curr_char = icb[orow*8+ocol];

    int colour = isupper(curr_char)?1:0;

    if(colour)
    {
        if(orow=3&&ep_active[ocol])
        {
            return ep_active[ocol];
        }
    }
    else
    {
        if(orow=4&&ep_active[ocol])
        {
            return ep_active[ocol];
        }
    }

    return 0;
}

bool Special_Moves::set_promotion(Sprite*pieces,float nx,float ny,char* icb,int n,int Move,Sounds* sound)
{
    int nrow = (ny-155)/110,ncol = (nx-575)/110,pos = nrow*8+ncol;

    if((nrow==7||nrow==0)&&(icb[pos]=='P'||icb[pos]=='p'))
    {
        piece = &pieces[n];
        curr_char = icb[pos];
        NX = nx,NY = ny;
        pieces[16].setPosition(571-110*2,isupper(curr_char)?155:155+440);
        POS = pos;

        Move==1?sound->play_move_Sound():sound->play_capture_Sound();

        return true;
    }
    return false;
}

char Special_Moves::promote(Sprite*pieces,char* icb,int MX,int MY,int n,bool *white_turn)
{
    int nx = pieces[16].getPosition().x-55,ny = pieces[16].getPosition().y-55;

    if(n==16&&(MX>=nx&&MX<nx+110))
    {
        if((MY>=ny)&&(MY<ny+110))
        {
            *piece = pieces[4];
            icb[POS] = isupper(curr_char)?'Q':'q';
        }
        else if((MY>=ny+110)&&(MY<ny+220))
        {
            *piece = pieces[0];
            icb[POS] = isupper(curr_char)?'R':'r';
        }
        else if((MY>=ny+220)&&(MY<ny+330))
        {
            *piece = pieces[1];
            icb[POS] = isupper(curr_char)?'N':'n';
        }
        else if((MY>=ny+330)&&(MY<ny+440))
        {
            *piece = pieces[2];
            icb[POS] = isupper(curr_char)?'B':'b';
        }

        piece->setPosition(NX,NY);
        *white_turn=!*white_turn;
        pieces[16].setPosition(-500,-500);
    }

    return icb[POS];
}

int Special_Moves::is_check(Sprite* king,vector<int>invalid)
{
    int pos = (king->getPosition().x-575)/110 + ((king->getPosition().y-155)/110)*8;

    if(find(invalid.begin(),invalid.end(),pos)!=invalid.end())
    {
        return pos;
    }
    else
    {
        return -500;
    }
}

int Special_Moves::is_checkmate(int x,vector<int>moves)
{
    if(moves.size()==0)
    {
        if(x>0)
        {
            return 1;
        }
        else
        {
            return 2;
        }
    }

    return 0;
}

void Special_Moves::Announce_Winner(Sprite* pawn,int Move)
{
        Texture bgt,wft;string suffix;Sprite bgs,wfs;Sprite Pawn;

        if(Move==1)
        {suffix = "Whitewon";}
        if(Move==0)
        {suffix = "Blackwon";}
        if(Move==2)
        {suffix="Stalemate";}

        bgt.loadFromFile("C:\\GAME\\CHESS\\IMAGES\\SHAPES\\Background.png");
        wft.loadFromFile("C:\\GAME\\CHESS\\IMAGES\\BOARD\\"+suffix+".png");

        bgs.setTexture(bgt);bgs.setPosition(220,220),wfs.setTexture(wft),wfs.setOrigin(220,220),wfs.setPosition(220,220);
        bgs.setOrigin(220,220);Pawn = *pawn;

        if(Move!=2){Pawn.setOrigin(55,55);Pawn.setScale(2,2);Pawn.setPosition(220,250);}

        RenderWindow* window = new RenderWindow(VideoMode(440,440),"winner",Style::Close);
        window->setFramerateLimit(120);

        while(window->isOpen())
        {
            Event event;

            while(window->pollEvent(event))
            {
               if(event.type == Event::Closed)
               {
                   window->close();
               }

               if ((event.type == sf::Event::KeyPressed)&&(event.key.code == Keyboard::Escape))
               {
                   window->close();
               }
            }

            window->draw(bgs);window->draw(Pawn);window->draw(wfs);

            window->display();
            window->clear();
        }

}
