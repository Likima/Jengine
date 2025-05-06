#pragma once

#include <vector>

#include "KeyHandler.h"
#include "Entities/Entity.hpp"

class Game {
public:
    Game(){}
    virtual ~Game(){}
    
    virtual void update(){}
    virtual void onStart(){}

    void attachKeyHandler(KeyHandler* kh) { this->kh = kh; }
    std::vector<Entity> getEntityList() { return EntityList; }

private:
    KeyHandler* kh;
    std::vector<Entity> EntityList;
};