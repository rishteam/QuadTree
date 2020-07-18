#include <random>
#include "helper.h"

int randInt(int lower, int upper)
{
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> rander(lower, upper);
    auto res = rander(generator);
    return res;
}

void drawText(const std::string &s, const sf::Vector2f &pos, uint32_t size, const sf::Color &color, uint32_t style)
{
    sf::Text text;
    text.setFont(font);
    text.setPosition(pos);
    text.setString(s);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setStyle(style);
    window.draw(text);
}

// drawCircle({100, 200}, 20, sf::Color::Red);
void drawCircle(const sf::Vector2f &pos, uint32_t radius, const sf::Color &fill, float thickness, const sf::Color &outline, uint32_t mode)
{
    sf::CircleShape cir;
    cir.setPosition(pos);
    cir.setRadius(radius);
    cir.setFillColor(fill);
    cir.setOutlineColor(outline);
    cir.setOutlineThickness(thickness);
    if(mode == CirCenter)
        cir.setOrigin(0.5*radius, 0.5*radius);
    window.draw(cir);
}

// drawRect({100, 200}, {50, 50}, sf::Color::Red);
void drawRect(const sf::Vector2f &pos, const sf::Vector2f &size, const sf::Color &fill, float thickness, const sf::Color &outline)
{
    sf::RectangleShape rect;
    rect.setPosition(pos);
    rect.setSize(size);
    rect.setFillColor(fill);
    rect.setOutlineThickness(thickness);
    rect.setOutlineColor(outline);
    window.draw(rect);
}