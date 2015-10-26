#include "Robby.h"

#define THRESH 5
#define ACCELERATION_FACTOR 4.0
#define INERTIAL_FACTOR 7.5

int mLeft, mRight;

Robby::Robby(const sf::RenderWindow& window,int width, int height, double _speed):
sf::RectangleShape(sf::Vector2f(width,height)), hostWindow(window) {
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

double Robby::getDistance() {
    float xPrime = cos(getRotation()*0.0174533)*hostWindow.getSize().x*2;
    float yPrime = sin(getRotation()*0.0174533)*hostWindow.getSize().x*2;
    
    sf::Vector2f pPoint(xPrime,yPrime);
    sf::Vector2f oPoint = getPosition();
    sf::Vector2f tlPoint(0,0);
    sf::Vector2f trPoint(hostWindow.getSize().x,0);
    sf::Vector2f blPoint(0,hostWindow.getSize().y);
    sf::Vector2f brPoint(hostWindow.getSize().x,hostWindow.getSize().y);
        
    sf::Vector2f topLine = findIntersection(oPoint,pPoint,tlPoint,trPoint);
    sf::Vector2f botLine = findIntersection(oPoint,pPoint,blPoint,brPoint);
    sf::Vector2f leftLine = findIntersection(oPoint,pPoint,tlPoint,blPoint);
    sf::Vector2f rightLine = findIntersection(oPoint,pPoint,trPoint,brPoint);
    
    sf::Vector2f intercept;
    
    if (topLine.x < -9) {
        if (botLine.x < -9) {
            if (leftLine.x < -9) {
                intercept = rightLine;
            } else intercept = leftLine;
        } else intercept = botLine;
    } else intercept = topLine;
    
    double distance = sqrt(pow(intercept.x-getPosition().x,2)+pow(intercept.y-getPosition().y,2));
    return distance;
}

sf::Vector2f Robby::findIntersection(sf::Vector2f p1,sf::Vector2f p2,
                              sf::Vector2f p3,sf::Vector2f p4) {
    float xD1,yD1,xD2,yD2,xD3,yD3;
    float dot,deg,len1,len2;
    float segmentLen1,segmentLen2;
    float ua,ub,div;
    
    // calculate differences
    xD1=p2.x-p1.x;
    xD2=p4.x-p3.x;
    yD1=p2.y-p1.y;
    yD2=p4.y-p3.y;
    xD3=p1.x-p3.x;
    yD3=p1.y-p3.y;
    
    // calculate the lengths of the two lines
    len1=sqrt(xD1*xD1+yD1*yD1);
    len2=sqrt(xD2*xD2+yD2*yD2);
    
    // calculate angle between the two lines.
    dot=(xD1*xD2+yD1*yD2); // dot product
    deg=dot/(len1*len2);
    
    if(fabs(deg)==1) return sf::Vector2f(-10,-10);
    
    // find intersection Pt between two lines
    sf::Vector2f pt(0,0);
    div=yD2*xD1-xD2*yD1;
    ua=(xD2*yD3-yD2*xD3)/div;
    ub=(xD1*yD3-yD1*xD3)/div;
    pt.x=p1.x+ua*xD1;
    pt.y=p1.y+ua*yD1;
    
    // calculate the combined length of the two segments
    // between Pt-p1 and Pt-p2
    xD1=pt.x-p1.x;
    xD2=pt.x-p2.x;
    yD1=pt.y-p1.y;
    yD2=pt.y-p2.y;
    segmentLen1=sqrt(xD1*xD1+yD1*yD1)+sqrt(xD2*xD2+yD2*yD2);
    
    // calculate the combined length of the two segments
    // between Pt-p3 and Pt-p4
    xD1=pt.x-p3.x;
    xD2=pt.x-p4.x;
    yD1=pt.y-p3.y;
    yD2=pt.y-p4.y;
    segmentLen2=sqrt(xD1*xD1+yD1*yD1)+sqrt(xD2*xD2+yD2*yD2);
    
    if(fabs(len1-segmentLen1)>0.01 || fabs(len2-segmentLen2)>0.01)
        return sf::Vector2f(-10,-10);
    
    // return the valid intersection
    return pt;
}