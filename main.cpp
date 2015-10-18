#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include <zmq.hpp>
#include "Robby.h"

int main(int, char const**) {
    sf::RenderWindow window(sf::VideoMode(1300, 1000), "Robby the Robot");
    
    Robby robot(100,80,1.5);

    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REP);
    socket.bind ("tcp://*:5555");
    
    while (window.isOpen()) {
        zmq::message_t input;
        socket.recv(&input);
        
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
