#pragma once

#include <vector>
#include <memory>

#include "KeyHandler/KeyHandler.h"
#include "Entities/Entity.hpp"
#include "Dependancies/libs.h"

class Game
{
public:
    Game() {}
    virtual ~Game() {}

    virtual void update() {}
    virtual void render() {}
    virtual void onStart() {}

    void attachKeyHandler(KeyHandler *kh) { this->kh = kh; }
    void attachWindow(GLFWwindow *win)
    {
        this->win = win;
        this->rdr = new Renderer(win);
    }
    std::vector<std::unique_ptr<Entity>> &getEntityList() { return EntityList; }

    void addToEntityList(std::unique_ptr<Entity> e) { EntityList.push_back(std::move(e)); }

protected:
    KeyHandler *kh;
    Renderer *rdr;
    GLFWwindow *win;

    std::vector<std::unique_ptr<Entity>> EntityList;
};