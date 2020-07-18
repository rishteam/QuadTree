#include "shape.h"

// reference: http://davidhsu666.com/archives/gamecollisiondetection/
bool Rect::intersect(const Rect &other)
{
    // Rect1
    float minX1 = getX(),
            maxX1 = getX() + getW(),
            minY1 = getY(),
            maxY1 = getY() + getH();
    // Rect2
    float minX2 = other.getX(),
            maxX2 = other.getX() + other.getW(),
            minY2 = other.getY(),
            maxY2 = other.getY() + other.getH();

    return maxX1 > minX2 && maxX2 > minX1 &&
           maxY1 > minY2 && maxY2 > minY1;
}
