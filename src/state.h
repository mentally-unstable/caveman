// hello
#ifndef STATE_INCLUDED
#define STATE_INCLUDED

#include "raylib.h"
#include <time.h>

const int SCALE = 32;

// const int width = 32*SCALE;
// const int height = 24*SCALE;
const int ground = (2*height)/3;
// values scaled down; for array use
const int wscale = width/SCALE;
const int hscale = height/SCALE;
const int gscale = (2*hscale)/3;

enum {
    TGROUND,
    TSKY,
    TROCK,

    MSTAND,
    MTHROW,

    COUNT,
};
Texture2D textures[COUNT];

struct State {
    int tiles[hscale][wscale];

    Vector2 man;
    int man_state;
    Vector2 rock;

    int thrown;
    time_t start;
    time_t eta;
};

#endif
