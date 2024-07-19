#include "Shapes.h"

Shapes::Shapes()
{
    init_shapes();
}

void Shapes::init_shapes()
{
    shape_texture();
    shape_sprite();
}

void Shapes::shape_texture()
{
    ylt.loadFromFile(common_path+"NEWsquare.png");
    ydt.loadFromFile(common_path+"OLDsquare.png");
    glt.loadFromFile(common_path+"CLICKsquare.png");
    rdt.loadFromFile(common_path+"REDsquare.png");
    aat.loadFromFile(common_path+"WhiteArea.png");
    cht.loadFromFile(common_path+"CheckArea.png");
    vt.loadFromFile(common_path+"VioletSquare.png");
}

void Shapes::shape_sprite()
{
    yls.setTexture(ylt);
    yds.setTexture(ydt);
    gls.setTexture(glt);
    chs.setTexture(cht);

    yls.setOrigin(55,55);
    yds.setOrigin(55,55);
    gls.setOrigin(55,55);
    chs.setOrigin(55,55);

    yls.setPosition(-55,-55);
    yds.setPosition(-55,-55);
    gls.setPosition(-55,-55);
    chs.setPosition(-55,-55);
}

void Shapes::set_yds_position(float x,float y)
{
    yds.setPosition(x,y);
}

void Shapes::set_yls_position(float x,float y)
{
    yls.setPosition(x,y);
}

void Shapes::set_gls_position(float x,float y)
{
    gls.setPosition(x,y);
}

void Shapes::set_chs_position(float x,float y)
{
    chs.setPosition(x,y);
}

void Shapes::set_rds_position(vector<int>position)
{
    vector<Sprite>temp(position.size());

    for(int i=0;i<position.size();i++)
    {
        Sprite image;

        float x = (abs(position[i])%8)*110+575;
        float y = (abs(position[i])/8)*110+155;

        position[i]<0?image.setTexture(vt):image.setTexture(rdt);
        image.setOrigin(55,55);
        image.setPosition(x,y);

        temp[i] = image;
    }

    rds = temp;
}

void Shapes::set_aas_position(vector<int>Position)
{
    set<int>position(Position.begin(),Position.end());

    vector<Sprite>temp;

    for(auto i:position)
    {
        Sprite image;

        float x = (i%8)*110+575;
        float y = (i/8)*110+155;

        image.setTexture(aat);
        image.setOrigin(55,55);
        image.setPosition(x,y);

        temp.push_back(image);
    }

    aas = temp;
}

void Shapes::draw_shapes(RenderWindow* window)
{
    window->draw(gls);
    window->draw(yds);
    window->draw(yls);

    for(int i=0;i<rds.size();i++)
    {
        window->draw(rds[i]);
    }

    for(int i=0;i<aas.size();i++)
    {
        window->draw(aas[i]);
    }

    window->draw(chs);
}
