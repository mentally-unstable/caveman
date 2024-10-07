// hello
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Man.h"
#include "TileMap.h"

sf::RenderWindow window(sf::VideoMode(width, height),
        "Dyn Taflu Roc Simulator");

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
