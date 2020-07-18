#pragma once

#include <glm/glm.hpp>

struct Body;

struct Point
{
    Point() : pos(0.f, 0.f) {}
    Point(const glm::vec2& p, Body *par=nullptr) : pos(p), parent(par)
    {
    }
    Point(float x, float y, Body *par) : pos(x, y), parent(par)
    {
    }

    operator const glm::vec2() const { return pos; }

    float getX() const { return pos.x; }
    float getY() const { return pos.y; }

    glm::vec2 pos;
    Body *parent = nullptr;
};

struct Rect
{
    Rect() : rect(0.f, 0.f, 0.f, 0.f) {}
    Rect(const glm::vec4 &r) : rect(r)
    {
    }
    Rect(float x, float y, float w, float h) : rect(x, y, w, h)
    {
    }

    bool intersect(const Rect &other);

    float getX() const { return rect.x; }
    float getY() const { return rect.y; }
    float getW() const { return rect.z; }
    float getH() const { return rect.w; }
    std::pair<float, float> getPosition() const { return std::make_pair(getX(), getY()); }
    std::pair<float, float> getSize() const { return std::make_pair(getW(), getH()); }

    operator const glm::vec4() const { return rect; }

    glm::vec4 rect; // (x, y, w, h)
    Body *parent = nullptr;
};
