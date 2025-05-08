#include "ColorWave.h"
#include "Entities/Player.hpp"

#include <iostream>

ColorWave::ColorWave()
{
    addToEntityList(std::make_unique<Player>());
}

ColorWave::~ColorWave()
{
}

void ColorWave::update()
{
    for(auto &entity : getEntityList()) {
        entity->update();
    }
}

void ColorWave::onStart()
{
    for (auto &entity : getEntityList())
    {
        entity->onStart();
    }
}

void ColorWave::render()
{
    rdr->initialize();

    for (auto &entity : getEntityList())
    {
        entity->render(rdr);
    }
}