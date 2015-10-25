#ifndef Robby_h
#define Robby_h

#include <stdio.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <vector>


/// adapted from the Fido simulator developed by
/// Josh Gruenstein and Michael Truell
class Robby : public sf::RectangleShape {
public:
    Robby(const sf::RenderWindow& window,int width, int height, double _speed);
    void go(int motLeft, int motRight);
    void goAccel(int motLeft, int motRight);
    double getGyro(); /// given in radians/sec
    double getDistance();
    std::vector<sf::RectangleShape> drawPen(int traceWidth);
protected:
    sf::RectangleShape drawLine(sf::Vector2f pOne, sf::Vector2f pTwo, int width);
    const sf::RenderWindow& hostWindow;
    sf::Clock moveClock;
    std::vector<sf::RectangleShape> penLines;
    sf::Vector2f lastPoint;
    double speed, deltat, deltar;
    int mLeft, mRight;
    sf::Vector2f findIntersection(sf::Vector2f p1,sf::Vector2f p2,
                                  sf::Vector2f p3,sf::Vector2f p4);
};

#endif