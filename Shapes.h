#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

using namespace std;
using namespace sf;

#ifndef SHAPES_H
#define SHAPES_H

class Shapes
{
    private:

    Texture ylt,ydt,glt,rdt,aat,cht,vt;
    Sprite yls,yds,gls,chs;

    vector<Sprite>rds;
    vector<Sprite>aas;

    string common_path = "./IMAGES/SHAPES/";

    public:

    Shapes();

    void init_shapes();

    void set_yds_position(float x,float y);
    void set_yls_position(float x,float y);
    void set_gls_position(float x,float y);
    void set_chs_position(float x,float y);

    void set_rds_position(vector<int>position);
    void set_aas_position(vector<int>position);

    void shape_texture();
    void shape_sprite();

    void draw_shapes(RenderWindow* window);
};

#endif // SHAPES_H
