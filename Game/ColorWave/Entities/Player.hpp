#pragma once

#include "Entity.hpp"

class Player : public Entity
{
public:
    Player();
    Player(float x_left, float x_right, float y_up, float y_down)
        : x_left(x_left), x_right(x_right), y_up(y_up), y_down(y_down) {}
    ~Player();

    bool setImgPath(std::string filepath) {this->filepath = filepath;}
    bool setCoordinates(float x_left, float x_right, float y_up, float y_down)
    {
        this->x_left = x_left;
        this->x_right = x_right;
        this->y_up = y_up;
        this->y_down = y_down;
        return true;
    }

private:
    float x_left;
    float y_up;
    float x_right;
    float y_down;

    std::string filepath;
};