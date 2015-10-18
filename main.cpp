#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include "Robby.h"

int main(int, char const**) {
    sf::RenderWindow window(sf::VideoMode(1300, 1000), "Robby the Robot");
    
    Robby robot(100,80,1.5);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }

        window.clear(sf::Color(255,255,255));
        window.display();
    }

    return EXIT_SUCCESS;
}
