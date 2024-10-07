// hello
#pragma once

#include <SFML/Graphics.hpp>

const int SCALE = 32;

const int width = 32*SCALE;
const int height = 24*SCALE;
const int ground = (2*height)/3;
// values scaled down; for array use
const int wscale = width/SCALE;
const int hscale = height/SCALE;
const int gscale = (2*hscale)/3;

class TileMap {
private:
    enum {
        T_GROUND,
        T_SKY,
        COUNT,
    };
    sf::Texture textures[COUNT];
    int tiles[hscale][wscale];

    void load(sf::Texture *t, int which);

public:
    TileMap();
    void draw_to(sf::RenderWindow *window);
    void update_tiles(void);
};
