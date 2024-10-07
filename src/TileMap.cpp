// hello
#include <iostream>
#include "TileMap.h"

TileMap::TileMap() {
    for (int i = 0; i < COUNT; i++) {
        load(&textures[i], i);
    }

    for (int y = 0; y < hscale; y++) {
        for (int x = 0; x < wscale; x++) {
            tiles[y][x] = y > gscale ? T_GROUND : T_SKY;
        }
    }
}

void TileMap::draw_to(sf::RenderWindow *window) {
    sf::Sprite tile;
    for (int y = 0; y < hscale; y++) {
        for (int x = 0; x < wscale; x++) {
            switch (tiles[y][x]) {
                case T_SKY:
                    tile.setTexture(textures[T_SKY]);
                    break;
                case T_GROUND:
                    tile.setTexture(textures[T_GROUND]);
                    break;
                default:
                    break;
            }

            tile.setPosition(x*SCALE, y*SCALE);
            window->draw(tile);
        }
    }
}

// void TileMap::update_tiles(void);

void TileMap::load(sf::Texture *t, int which) {
    std::string file;
    switch (which) {
        case T_GROUND:
            file = "assets/grnd_tile.png";
            break;
        case T_SKY:
            file = "assets/sky_tile.png";
            break;
        default:
            break;
    }

    if (!t->loadFromFile(file)) {
        std::cout << "Failure to load texture asset `" << file << "`\n";
        exit(1);
    }
}
