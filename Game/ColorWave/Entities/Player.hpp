#pragma once

#include <vector>
#include "Entity.hpp"

class Player : public Entity
{
public:
    Player()
    {
        setCenterAndSize(0.0f, 0.0f, 0.2f, 0.2f); // Creates a 0.2x0.2 square at center
        updateVertices(); // This will update vertices using inherited coordinates
    }

    Player(float x_left, float x_right, float y_up, float y_down)
        : Entity(x_left, x_right, y_up, y_down) 
    {
        updateVertices();
    }

    ~Player() override {};
    
    void update() override;
    void render(Renderer* r) override;
    void onStart() override;

private:
    std::string filepath;
    bool onScreen = true;
};