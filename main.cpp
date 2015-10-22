#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <sstream>

#include "Robby.h"
#include "Socket.h"



int main(int, char const**) {
        
    sf::RenderWindow window(sf::VideoMode(1300, 1000), "Robby the Robot");
    
    Robby robot(100,80,1.5);
    Socket sock;
    
    while (window.isOpen()) {
        std::vector<double> mVect = sock.getMotors();
        robot.goAccel(mVect[0],mVect[1]);

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }

        window.clear(sf::Color(255,255,255));
        window.draw(robot);
        window.display();
        
    }
    return EXIT_SUCCESS;
}
