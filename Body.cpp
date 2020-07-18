#include "Body.h"
#include "shape.h"

void Body::insertPoints(quadtree &qt)
{
    auto [x,y] = rect.getPosition();
    auto [w, h] = rect.getSize();
    glm::vec2 off[4] = {
        {x, y},  // 左上
        {x+w, y}, // 右上
        {x, y+h}, // 左下
        {x+w, y+h} // 右下
    };
    for(int i = 0; i < 4; i++)
    {
        Point p = Point(off[i], this);
        qt.insert(p);
    }
}
