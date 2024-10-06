// hello
#include <SFML/Graphics.hpp>
#include <iostream>

const int SCALE = 32;
const int width = (SCALE*32);
const int height = (SCALE*24);
sf::RenderWindow window(sf::VideoMode(width, height),
        "Unga Yngvwn Lyngu Simulator");

void handle_event(sf::Event event) {
    switch (event.type) {
        case sf::Event::Closed:
        {
            window.close();
            break;
        }

        case sf::Event::KeyPressed:
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                ;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                ;
            }
            break;
        }

        default:
            break;
    }
}

const int twidth = width/SCALE;
const int theight = height/SCALE;
int bg_array[theight][twidth];
enum {
    T_SKY,
    T_GRND,
    T_GUY
};

void set_bg(void) {
    srand(time(0));

    for (int y = 0; y < theight; y++) {
        for (int x = 0; x < twidth; x++) {
            if (y < (2*theight/3)) {
                bg_array[y][x] = T_SKY;
            } else {
                bg_array[y][x] = T_GRND;
            }
        }
    }

    bg_array[((2*theight)/3)-1][twidth/2] = T_GUY;
}

void load(sf::Texture *t, int which) {
    std::string file;
    std::string type;
    switch (which) {
        case T_SKY:
            type = "sky";
            file = "assets/sky_tile.png";
            break;
        case T_GRND:
            type = "ground";
            file = "assets/grnd_tile.png";
            break;
        case T_GUY:
            type = "cave guy";
            file = "assets/guy_tile.png";
            break;
        default:
            std::cout << "Unknown asset\n";
    }

    if (!t->loadFromFile(file)) {
        std::cout << "Failure to open asset `" << type << "`\n";
        exit(1);
    }
}

void draw_bg(void) {
    // TODO only needs to happen once
    sf::Texture sky, grnd, guy;
    load(&sky, T_SKY);
    load(&grnd, T_GRND);
    load(&guy, T_GUY);

    sf::Sprite tile;
    for (int y = 0; y < theight; y++) {
        for (int x = 0; x < twidth; x++) {

            switch (bg_array[y][x]) {
                case T_SKY:
                    tile.setTexture(sky);
                    window.draw(tile);
                    break;

                case T_GRND:
                    tile.setTexture(grnd);
                    window.draw(tile);
                    break;

                case T_GUY:
                    tile.setTexture(sky);
                    window.draw(tile);
                    tile.setTexture(guy);
                    window.draw(tile);
                    break;

                default:
                    std::cout << "[INFO] error value in array\n";
                    break;
            }

            tile.setPosition(x*SCALE, y*SCALE);
            window.draw(tile);
        }
    }
}

int main(void) {
    set_bg();


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            handle_event(event);
        }

        window.clear();
        draw_bg();
        window.display();
    }

    return 0;
}

