#pragma once

#include <vector>
#include <memory>

#include "KeyHandler/KeyHandler.h"
#include "Entities/Entity.hpp"

class Game {
public:
    Game(){}
    virtual ~Game(){}
    
    virtual void update(){}
    virtual void onStart(){}

    void attachKeyHandler(KeyHandler* kh) { this->kh = kh; }
    std::vector<std::unique_ptr<Entity>>& getEntityList() { return EntityList; }

private:
    KeyHandler* kh;
    std::vector<std::unique_ptr<Entity>> EntityList;  // Change to store pointers
};