#pragma once

#include "Entity.hpp"

class Player : public Entity
{
public:
    Player() {};
    Player(float x_left, float x_right, float y_up, float y_down)
        : Entity(x_left, x_right, y_up, y_down) {}
    ~Player() override {};

    void setImgPath(std::string filepath) override { this->filepath = filepath; }

    void update() override;
    void render() override;
    void onStart() override;

private:

    std::string filepath;
    bool onScreen = true;

};