#include "quadtree.h"

#include <set>

void quadtree::insert(const Point &p)
{
    if(!contains(p))
        return;
    if(data.size() < capacity)
    {
        data.push_back(p);
    }
    else
    {
        subdivide();
        // 如果只剩 1 pixel 寬就不要再建下去
        if(boundary.getW() / 2.f <= 1.f && boundary.getH() / 2.f <= 1.f)
            return;
        for(int i = 0; i < 4; i++)
            if(child[i]->contains(p))
                child[i]->insert(p);
    }
}

bool quadtree::contains(const Point &p)
{
    auto [x1, y1] = boundary.getPosition();
    float x2 = x1 + boundary.getW(), y2 = y1 + boundary.getH();
    float px = p.pos.x, py = p.pos.y;

    return x1 <= px && px <= x2 &&
           y1 <= py && py <= y2;
}

void quadtree::subdivide()
{
    if(child[0] != nullptr)
        return;
    //
    auto [x, y] = boundary.getPosition();
    float halfW = boundary.getW() / 2, halfH = boundary.getH() / 2;

    if(halfW <= 1 && halfH <= 1)
        return;

    glm::vec2 off[4] = {
        {0, 0},  // 左上
        {halfW, 0}, // 右上
        {0, halfH}, // 左下
        {halfW, halfH} // 右下
    };
    // Build children
    for(int i = 0; i < 4; i++)
        child[i] = new quadtree(glm::vec4(x + off[i].x, y + off[i].y, halfW, halfH), capacity);
}

void quadtree::clear()
{
    data.clear();
    for(int i = 0; i < 4; i++)
    {
        if (child[i])
            child[i]->clear();
        child[i] = nullptr;
    }
}

std::vector<Point>& quadtree::query(std::vector<Point> &li, const Rect &r)
{
    if(boundary.intersect(r))
    {
        for(auto &p : data)
            li.push_back(p);
        for(int i = 0; i < 4; i++)
        {
            if(!child[i])
                continue;
            child[i]->query(li, r);
        }
    }

    return li;
}

std::vector<Body *> &quadtree::query(std::vector<Body *> &li, const Rect &r)
{
    std::vector<Point> pList;
    std::set<Body*> possibleBodySet;
    query(pList, r);
    for(auto p : pList)
    {
        if(p.parent && !possibleBodySet.count(p.parent))
        {
            possibleBodySet.insert(p.parent);
            li.push_back(p.parent);
        }
    }
    return li;
}
