#include <bits/stdc++.h>
#include <fmt/core.h>
#include <imgui.h>
#include <imgui-SFML.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;
#include "helper.h"
#include "quadtree.h"
#include "Body.h"

sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML window");
sf::Font font;

int main()
{
    window.setFramerateLimit(60);
//    font.loadFromFile("/Users/roy4801/Library/Fonts/Consolas.ttf");
    ImGui::SFML::Init(window);
    //
    vector<Body> bodyList;
    int genLimit[4] = {10, 300, 10, 300};
    quadtree qt({0.f, 0.f, 1280.f, 720.f}, 4);
    //
    sf::Clock clk, imgui;
    float elapsed = 0.f, fpsElapsed = 0.f;
    int fps = 0;
    int cnt = 0;
    while (window.isOpen())
    {
        float dt = clk.restart().asSeconds();
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
            else if(!ImGui::IsAnyItemHovered() && !ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow) &&
                event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                bodyList.emplace_back(event.mouseButton.x, event.mouseButton.y, randInt(genLimit[0], genLimit[1]), randInt(genLimit[2], genLimit[3]));
            }
        }
        ImGui::SFML::Update(window, imgui.restart());
        ImGui::Begin("Debug");
        {
            ImGui::Text("num = %d", bodyList.size());
            ImGui::DragInt4("Region", genLimit);
            if (ImGui::Button("Generate 100 Points") || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                for (int i = 0; i < 100; i++) {
                    bodyList.emplace_back(randInt(0, 1280), randInt(0, 720), randInt(genLimit[0], genLimit[1]), randInt(genLimit[2], genLimit[3]));
                }
            }
            if (ImGui::Button("Clean"))
            {
                bodyList.clear();
            }
            auto mpos = sf::Mouse::getPosition(window);
            ImGui::Text("mpos = %d %d", mpos.x, mpos.y);
            ImGui::Text("fps = %d", fps);
        }
        ImGui::End();
        // Update

        // Build quad tree
        qt.clear();
        // Insert all points of all bodies
        for(auto &r : bodyList)
            r.insertPoints(qt);
        qt.imguiDebug();
        // Query for possible collision points
        std::vector<Point> possible;
        auto [mx, my] = sf::Mouse::getPosition(window);
        Rect m(mx, my, 100, 100);
        qt.query(possible, m);

        vector<Body*> possBody;
        qt.query(possBody, m);
        ImGui::Begin("Possible Body");
        {
            ImGui::Text("%d", possBody.size());
            for (int i = 0; i < possBody.size(); i++) {
                ImGui::PushID(i);
                ImGui::Text("%p", possBody[i]);
                ImGui::PopID();
            }
        }
        ImGui::End();
        //
        window.clear();

        qt.debugDraw(window);
        // Draw the mouse rect
        drawRect({m.getX(), m.getY()}, {m.getW(), m.getH()}, sf::Color::Transparent, 1, sf::Color::Blue);
        // Draw all bodies
        for(auto &r : bodyList)
            drawRect({r.rect.getX(), r.rect.getY()}, {r.rect.getW(), r.rect.getH()}, sf::Color::Transparent, 1, sf::Color::Green);
        // debugDraw possible points
        for(auto &p : possible)
            drawCircle({p.getX(), p.getY()}, 2, sf::Color::Yellow);
        // debugDraw possible bodies
        for(auto i : possBody)
            drawRect({i->rect.getX(), i->rect.getY()}, {i->rect.getW(), i->rect.getH()}, sf::Color(255, 0, 0, 128));
#if 0
        drawText(fmt::format("frame time = {:.4f}\n", dt), {0.f, 0.f}, 24, sf::Color::White);
        drawText(fmt::format("fps = {}", fps), {0.f, 20.f}, 24, sf::Color::White);
        drawText(fmt::format("elapsed = {:.2f}", elapsed), {0.f, 40.f}, 24, sf::Color::White);
#endif
        ImGui::SFML::Render(window);
        window.display();

        cnt++;
        elapsed += dt;
        fpsElapsed += dt;
        if(fpsElapsed >= 1.f)
        {
            fps = cnt;
            cnt = 0;
            fpsElapsed = 0.f;
        }
    }
}