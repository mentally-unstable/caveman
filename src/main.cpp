// hello
#include <SFML/Graphics.hpp>
#include <iostream>

#include "gstate.h"
State state;

sf::RenderWindow window(sf::VideoMode(width, height),
        "Dyn Taflu Roc Simulator");


void load(sf::Texture *t, int which);
void init(void);
void handle_event(sf::RenderWindow *window, sf::Event e);
void draw(sf::RenderWindow *window);

int main(void) {
    init();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            handle_event(&window, event);
        }

        if (state.thrown) {
            std::time_t cur = std::time(0);
            if (cur - state.start >= state.eta) {
                state.thrown = 0;
                state.man_state = MSTAND;
            }
        }

        window.clear();
        draw(&window);
        window.display();
    }

    return 0;
}



void init(void) {
    for (int i = 0; i < COUNT; i++) {
        load(&textures[i], i);
    }

    for (int y = 0; y < hscale; y++) {
        for (int x = 0; x < wscale; x++) {
            state.tiles[y][x] = y > gscale ? TGROUND : TSKY;
        }
    }

    state.man = sf::Vector2i(width/2, (2*height)/3);
    state.man_state = MSTAND;
}

void draw(sf::RenderWindow *window) {
    sf::Sprite tile;
    for (int y = 0; y < hscale; y++) {
        for (int x = 0; x < wscale; x++) {
            switch (state.tiles[y][x]) {
                case TSKY:
                    tile.setTexture(textures[TSKY]);
                    break;
                case TGROUND:
                    tile.setTexture(textures[TGROUND]);
                    break;
                default:
                    break;
            }

            tile.setPosition(x*SCALE, y*SCALE);
            window->draw(tile);
        }
    }

    sf::Sprite man;
    man.setTexture(textures[state.man_state]);
    man.setPosition(state.man.x, state.man.y);
    window->draw(man);
}

void throw_to(sf::Vector2i pos) {
    state.man_state = MTHROW;
    state.thrown = 1;
    state.rock = sf::Vector2i(state.man.x+SCALE, state.man.y+SCALE);
    state.start = std::time(0);
    state.eta = 5; // TODO
}

void load(sf::Texture *t, int which) {
    std::string file;
    switch (which) {
        case TSKY:
            file = "assets/sky_tile.png";
            break;
        case TGROUND:
            file = "assets/grnd_tile.png";
            break;
        case MSTAND:
            file = "assets/guy_tile.png";
            break;
        case MTHROW:
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

void handle_event(sf::RenderWindow *window, sf::Event e) {
    switch (e.type) {
        case sf::Event::Closed:
        {
            window->close();
            break;
        }

        case sf::Event::KeyPressed:
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                state.man.x-=4;
                // man.move_left();
                break;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                state.man.x+=4;
                // man.move_right();
                break;
            }
        }

        case sf::Event::MouseButtonPressed:
        {
            sf::Vector2i pos = sf::Mouse::getPosition();
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                throw_to(pos);
            }
        }

        default:
            break;
    }
}
