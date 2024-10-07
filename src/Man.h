// hello
#pragma once

#include <SFML/Graphics.hpp>

class Man {
public:
    enum {
        STAND,
        THROW,
        COUNT,
    };
    sf::Texture textures[COUNT];
    int state;

    int x;
    int y;

    Man(int x, int y);
    void draw_to(sf::RenderWindow *window);

private:
    void load(sf::Texture *t, int which);
};
