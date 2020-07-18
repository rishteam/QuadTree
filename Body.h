#pragma once

#include "shape.h"
#include "quadtree.h"

/*
 * 實際上他是個 RectBody
 */
class Body
{
public:
    Body(float x, float y, float w, float h) : rect(x, y, w, h)
    {
    }

    ~Body()
    {
    }

    void insertPoints(quadtree &qt);

    Rect rect;
};
