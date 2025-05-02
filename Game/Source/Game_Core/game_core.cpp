#include "game_core.h"
#include "ColorWave.h" // TODO <- this should be made into a generic later on

namespace Game_Core {
    Game* getGame() {
        static Game* instance = new ColorWave();
        return instance;
    }
}