#include "ColorWave.h"

#include <iostream>

ColorWave::ColorWave() {

}

ColorWave::~ColorWave() { 
    
}

void ColorWave::update() {
    
}

void ColorWave::onStart() {
    
}

void ColorWave::render() {
    for(auto &entity : getEntityList()) {
        entity->render();
    }   
}

/*
-- Goals --

- utilize the engine to instantiate an initial ui.
- utilize the engine to create a basic game loop

...

*/