#include "game.h" // TODO <- get rid of this later. Make sure no unnecessary includes

#include <vector>
#include "Entities/Entity.hpp"

class ColorWave: public Game {
public:
    ColorWave();
    ~ColorWave() override;

    void update() override;
    void onStart() override;

private:
    KeyHandler* kh;    
};