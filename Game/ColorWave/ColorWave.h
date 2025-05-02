#include "game.h"

class ColorWave: public Game {
public:
    ColorWave();
    ~ColorWave() override;

    void update() override;
    void onStart() override;
private:

};