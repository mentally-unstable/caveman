// hello
#include <SFML/Graphics.hpp>
#include <iostream>

const int SCALE = 32;

const int width = 32*SCALE;
const int height = 24*SCALE;
const int ground = (2*height)/3;
// values scaled down; for array use
const int wscale = width/SCALE;
const int hscale = height/SCALE;
const int gscale = (2*hscale)/3;

sf::RenderWindow window(sf::VideoMode(width, height),
        "Dyn Taflu Roc Simulator");

class TileMap {
private:
    enum {
        T_GROUND,
        T_SKY,
        COUNT,
    };
    sf::Texture textures[COUNT];
    int tiles[hscale][wscale];

    void load(sf::Texture *t, int which) {
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

public:
    TileMap() {
        for (int i = 0; i < COUNT; i++) {
            load(&textures[i], i);
        }

        for (int y = 0; y < hscale; y++) {
            for (int x = 0; x < wscale; x++) {
                tiles[y][x] = y > gscale ? T_GROUND : T_SKY;
            }
        }
    }

    void draw_to(sf::RenderWindow *window) {
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

    void update_tiles(void);
};

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

    Man(int x, int y) {
        this->x = x;
        this->y = y;
        state = STAND;

        for (int i = 0; i < COUNT; i++) {
            load(&textures[i], i);
        }
    }

    void draw_to(sf::RenderWindow *window) {
        sf::Sprite sprite;
        sprite.setTexture(textures[state]);
        sprite.setPosition(x, y);
        window->draw(sprite);
    }

private:
    void load(sf::Texture *t, int which) {
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
};

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
                ;
            }
            break;
        }

        case sf::Event::MouseButtonPressed:
        {
            break;
        }

        default:
            break;
    }
}

int main(void) {
    TileMap env;
    Man man(width/2, ground);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            handle_event(&window, event);
        }

        window.clear();
        env.draw_to(&window);
        man.draw_to(&window);
        window.display();
    }

    return 0;
}
