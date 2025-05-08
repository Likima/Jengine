#pragma once
#include <array>
#include <string>

#include "KeyHandler/KeyHandler.h"

class Entity
{
public:
    Entity() = default;
    virtual ~Entity() = default;
    Entity(Entity const &e)
        : x_left(e.x_left), y_up(e.y_up), x_right(e.x_right), y_down(e.y_down), kh(e.kh) {}
    Entity(float x_left, float x_right, float y_up, float y_down)
        : x_left(x_left), x_right(x_right), y_up(y_up), y_down(y_down), kh(nullptr) {}
    

    virtual void setImgPath(std::string filepath);
    void setCoordinates(float x_left, float x_right, float y_up, float y_down)     {
        this->x_left = x_left;
        this->x_right = x_right;
        this->y_up = y_up;
        this->y_down = y_down;
    }

    virtual void update() = 0;
    virtual void render() = 0;
    virtual void onStart() = 0;

    void attachKeyHandler(KeyHandler* kh) {this->kh = kh;}

    std::pair<float, float> getXY() {return std::make_pair((x_left+x_right)/2,(y_up+y_down)/2);}

    // std::array<
private:
    float x_left;
    float y_up;
    float x_right;
    float y_down;

    KeyHandler* kh;
    bool onScreen;
};