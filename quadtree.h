#pragma once

#include <cstdint>
#include <vector>
//
#include <glm/glm.hpp>
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <fmt/format.h>
//
#include "helper.h"
#include "shape.h"

class quadtree
{
public:
    quadtree(const glm::vec4 &boundary_, uint32_t capacity_)
        : boundary(boundary_), debug(randInt(1, 255), randInt(1, 255), randInt(1, 255), 128)
    {
        capacity = capacity_;
        data.reserve(4);
    }
    ~quadtree()
    {
        for(int i = 0; i < 4; i++)
            delete child[i];
    }

    sf::Color debug;
    void debugDraw(sf::RenderTarget &target) // ugly
    {
        sf::RectangleShape rect;
        rect.setPosition(boundary.getX(), boundary.getY());
        rect.setSize(sf::Vector2f(boundary.getW(), boundary.getH()));
        rect.setFillColor(sf::Color::Transparent);
        rect.setOutlineThickness(1);
        rect.setOutlineColor(sf::Color::White);
        target.draw(rect);

        for(int i = 0; i < 4; i++)
            if(child[i])
                child[i]->debugDraw(target);
    }

    void imguiDebug()
    {
        if(ImGui::TreeNode("Points"))
        {
            for (auto &p : data) {
                ImGui::PushID(&p);
                ImGui::Text("%p %.2f %.2f", p.parent, p.pos.x, p.pos.y);
                ImGui::PopID();
            }
            ImGui::TreePop();
        }
        for(int i = 0; i < 4; i++)
        {
            if(!child[i]) continue;
            auto ID = fmt::format("{}", i);
            ImGui::PushID(ID.c_str());
            if(ImGui::TreeNode(fmt::format("Node {}: {}", ID, child[i]->data.size()).c_str()))
            {
                child[i]->imguiDebug();
                ImGui::TreePop();
            }
            ImGui::PopID();
        }
    }

    /**
     * 插入一個點 p 到 quadtree 中
     * @param p 點座標
     */
    void insert(const Point &p);

    /**
     * 查詢給定區域 r 可能產生碰撞的點集合
     * @param r 集合
     */
    std::vector<Point>& query(std::vector<Point> &li, const Rect &r);

    /**
     * 查詢給定區域 r 可能產生碰撞的 Body 集合
     * @param r 集合
     */
    std::vector<Body*>& query(std::vector<Body*> &li, const Rect &r);

    /**
     * 清空整棵樹
     */
    void clear();

    /**
     * 判斷點 p 是否在區域內(boundary)
     * @param p 點座標
     * @return true/false
     */
    bool contains(const Point &p);

    /**
     * 分割成四個子區域
     */
    void subdivide();

    Rect boundary; // 當前節點的邊界 (x, y, w, h)
    uint32_t capacity;  // 容量
    std::vector<Point> data; // 點資料
    quadtree *child[4] = {nullptr};
};
