#pragma once
#include <array>
#include <string>

class Entity
{
public:
    Entity();
    virtual ~Entity();

    virtual bool setImgPath(std::string filepath);
    virtual bool setCoordinates(float x_left, float x_right, float y_up, float y_down);

    virtual void update();
    virtual void render();
    virtual void onStart();

    std::pair<float, float> getXY() {return std::make_pair((x_left+x_right)/2,(y_up+y_down)/2);}
private:
    float x_left;
    float y_up;
    float x_right;
    float y_down;
};