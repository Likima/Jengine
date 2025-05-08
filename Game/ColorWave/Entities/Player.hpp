#pragma once

#include <vector>

#include "Entity.hpp"

class Player : public Entity
{
public:
    Player()
    {
        // Initialize player as a square
        vertices = {
            // Position (x, y)
            0.1f, 0.1f,   // top right
            0.1f, -0.1f,  // bottom right
            -0.1f, -0.1f, // bottom left
            -0.1f, 0.1f   // top left
        };

        // indices = {
        //     // Note: counter-clockwise winding
        //     0, 1, 3, // first triangle
        //     1, 2, 3  // second triangle
        // };
    }
    Player(float x_left, float x_right, float y_up, float y_down)
        : Entity(x_left, x_right, y_up, y_down) {}
    ~Player() override {};
    
    void update() override;
    void render(Renderer* r) override;
    void onStart() override;

private:
    std::string filepath;
    bool onScreen = true;
};