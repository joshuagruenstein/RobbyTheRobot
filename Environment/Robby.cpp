#include "Robby.h"

#define THRESH 5
#define ACCELERATION_FACTOR 4.0
#define INERTIAL_FACTOR 7.5

int mLeft, mRight;

Robby::Robby(int width, int height, double _speed):
sf::RectangleShape(sf::Vector2f(width,height)) {
    setFillColor(sf::Color(0, 0, 0));
    setPosition(500,400);
    setOrigin(width/2,height/2);
    setRotation(90);
    speed = _speed;
}

sf::RectangleShape Robby::drawLine(sf::Vector2f pOne, sf::Vector2f pTwo, int width) {
    float length = sqrt(pow(pTwo.x-pOne.x,2)+pow(pTwo.y-pOne.y,2));
    
    sf::RectangleShape line(sf::Vector2f(width, length));
    
    line.setOrigin(width/2,0);
    line.setFillColor(sf::Color(0, 0, 0));
    line.setOutlineColor(sf::Color(0, 0, 0));
    
    line.rotate(getRotation()+90);
    line.setPosition(pOne);
    
    return line;
}

std::vector<sf::RectangleShape> Robby::drawPen(int traceWidth) {
    if (traceWidth != 0)
        penLines.push_back(drawLine(lastPoint,getPosition(),traceWidth));
    lastPoint = getPosition();
    return penLines;
}


void Robby::goAccel(int x, int y) {
    mLeft = (abs(x) > THRESH) ? (x + mLeft * ACCELERATION_FACTOR) / (ACCELERATION_FACTOR + 1)
                              : (mLeft * INERTIAL_FACTOR) / (INERTIAL_FACTOR + 1);
    mRight = (abs(y) > THRESH) ? (y + mRight * ACCELERATION_FACTOR) / (ACCELERATION_FACTOR + 1)
                               : (mRight * INERTIAL_FACTOR) / (INERTIAL_FACTOR + 1);
    go(mLeft,mRight);
}

void Robby::go(int motLeft,int motRight) {
    double mLeft = -(((double)motLeft)/200)*speed;
    double mRight = -(((double)motRight)/200)*speed;
    
    double xprime,yprime,rprime;
    double length = getSize().x;
    deltat = moveClock.restart().asMilliseconds();
    
    double rX = getPosition().x;
    double rY = getPosition().y;
    double rTheta = getRotation()*0.0174532925;
    
    if (mLeft == mRight) {
        xprime = rX + mLeft*cos(rTheta)*deltat;
        yprime = rY + mLeft*sin(rTheta)*deltat;
        rprime = rTheta;
        deltar = 0;
    } else {
        double radius = (length/2)*(mLeft+mRight)/(mRight-mLeft);
        double omega = (mRight-mLeft)/length;
        
        double iccX = rX - radius*sin(rTheta);
        double iccY = rY + radius*cos(rTheta);
        
        xprime = iccX + (cos(omega*deltat)*(rX-iccX)+
                         -sin(omega*deltat)*(rY-iccY));
        yprime = iccY + (sin(omega*deltat)*(rX-iccX)+
                         cos(omega*deltat)*(rY-iccY));
        deltar = omega*deltat;
        rprime = rTheta + deltar;
    }
    
    setPosition(xprime,yprime);
    setRotation(rprime*57.2957795);
}

double Robby::getGyro() {
    return (deltar/deltat)*1000;
}