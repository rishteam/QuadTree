#pragma once

#include <cstdint>
#include <SFML/Graphics.hpp>

extern sf::Font font;;
extern sf::RenderWindow window;

int randInt(int lower, int upper);
void drawText(const std::string &s, const sf::Vector2f &pos, uint32_t size, const sf::Color &color, uint32_t style=sf::Text::Regular);

enum CircleMode
{
    CirLeftUp,
    CirCenter
};
void drawCircle(const sf::Vector2f &pos, uint32_t radius, const sf::Color &fill, float thickness=0.f, const sf::Color &outline=sf::Color::Red, uint32_t mode=CirCenter);
void drawRect(const sf::Vector2f &pos, const sf::Vector2f &size, const sf::Color &fill, float thickness=0.f, const sf::Color &outline=sf::Color::Red);