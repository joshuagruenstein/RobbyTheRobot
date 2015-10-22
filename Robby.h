#ifndef __Drive__Robby__
#define __Drive__Robby__

#include <stdio.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>


/// adapted from the Fido simulator developed by
/// Josh Gruenstein and Michael Truell
class Robby : public sf::RectangleShape {
public:
    Robby(int width, int height, double _speed);
    void go(int motLeft, int motRight);
    void goAccel(int motLeft, int motRight);
    double getGyro(); /// given in radians/sec
protected:
    sf::Clock moveClock;
    double speed, deltat, deltar;
    int mLeft, mRight;
};

#endif