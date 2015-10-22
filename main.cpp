#include <SFML/Graphics.hpp>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

#include "ResourcePath.hpp"
#include "Robby.h"

#define MAX_BUFFER    128
#define HOST        "127.0.0.1"
#define PORT         50007

int main(int, char const**) {
    int connectionFd, rc, index = 0, limit = MAX_BUFFER;
    struct sockaddr_in servAddr, localAddr;
    char buffer[MAX_BUFFER+1];
    
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(PORT);
    servAddr.sin_addr.s_addr = inet_addr(HOST);
    
    connectionFd = socket(AF_INET, SOCK_STREAM, 0);
    
    localAddr.sin_family = AF_INET;
    localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    localAddr.sin_port = htons(0);
    rc = bind(connectionFd,(struct sockaddr *) &localAddr, sizeof(localAddr));
    
    connect(connectionFd,(struct sockaddr *)&servAddr, sizeof(servAddr));
    
    sf::RenderWindow window(sf::VideoMode(1300, 1000), "Robby the Robot");
    
    Robby robot(100,80,1.5);
    
    while (window.isOpen()) {
        sprintf( buffer, "%s", "yo" );
        send(connectionFd, buffer, strlen(buffer), 0);
        sprintf( buffer, "%s", "" );
        recv(connectionFd, buffer, MAX_BUFFER, 0);

        std::cout << buffer << "\n";
        
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
    close(connectionFd);
    return EXIT_SUCCESS;
}
