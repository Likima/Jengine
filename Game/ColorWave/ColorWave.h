#include "game.h" // TODO <- get rid of this later. Make sure no unnecessary includes

class ColorWave: public Game {
public:
    ColorWave();
    ~ColorWave() override;

    void update() override;
    void onStart() override;
private:

};