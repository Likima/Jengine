#pragma once
#include <array>
#include <string>

#include "KeyHandler/KeyHandler.h"
#include "Renderer/Renderer.h"

class Entity
{
public:
    Entity() = default;
    virtual ~Entity() = default;
    Entity(Entity const &e)
        : x_left(e.x_left), y_up(e.y_up), x_right(e.x_right), y_down(e.y_down), kh(e.kh) {}
    Entity(float center_x, float center_y, float width, float height)
        : kh(nullptr)
    {
        setCenterAndSize(center_x, center_y, width, height);
    }

    void setImgPath(std::string filepath) { this->filepath = filepath; }
    void setCenterAndSize(float center_x, float center_y, float width, float height)
    {
        float half_width = width / 2.0f;
        float half_height = height / 2.0f;
        x_left = center_x - half_width;
        x_right = center_x + half_width;
        y_up = center_y - half_height;
        y_down = center_y + half_height;
    }

    virtual void update() = 0;
    virtual void render(Renderer* r) = 0;
    virtual void onStart() = 0;

    void attachKeyHandler(KeyHandler *kh) { this->kh = kh; }

    std::pair<float, float> getXY() { return std::make_pair((x_left + x_right) / 2, (y_up + y_down) / 2); }

protected:
    float x_left;
    float y_up;
    float x_right;
    float y_down;

    std::string filepath;
    KeyHandler *kh;
    bool onScreen;

    std::array<float,8> vertices;
};