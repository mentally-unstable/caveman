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

enum {
    TGROUND,
    TSKY,
    // TROCK,

    MSTAND,
    MTHROW,

    COUNT,
};
sf::Texture textures[COUNT];

struct State {
    int tiles[hscale][wscale];

    sf::Vector2i man;
    int man_state;
    sf::Vector2i rock;

    int thrown;
    std::time_t start;
    std::time_t eta;
};
