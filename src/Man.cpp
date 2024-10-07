// hello
#include <iostream>
#include "Man.h"

Man::Man(int x, int y) {
    this->x = x;
    this->y = y;
    state = STAND;

    for (int i = 0; i < COUNT; i++) {
        load(&textures[i], i);
    }
}

void Man::draw_to(sf::RenderWindow *window) {
    sf::Sprite sprite;
    sprite.setTexture(textures[state]);
    sprite.setPosition(x, y);
    window->draw(sprite);
}

void Man::load(sf::Texture *t, int which) {
    std::string file;
    switch (which) {
        case STAND:
            file = "assets/guy_tile.png";
            break;
        case THROW:
            file = "assets/throw_tile.png";
            break;
        default:
            break;
    }

    if (!t->loadFromFile(file)) {
        std::cout << "Failure to load texture asset `" << file << "`\n";
        exit(1);
    }
}
