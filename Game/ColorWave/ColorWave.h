#include "game.h" // TODO <- get rid of this later. Make sure no unnecessary includes

#include <vector>
#include "Entities/Entity.hpp"

class ColorWave : public Game
{
public:
    ColorWave();
    ~ColorWave() override;

    void update() override;
    void render() override;
    void onStart() override;

private:
    KeyHandler *kh;
    // std::vector<std::unique_ptr<Entity>> EntityList;
};