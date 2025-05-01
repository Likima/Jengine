#include "ui_core.h"
#include <iostream>

namespace UI_Core {

    void Initialize()
    {
        std::cout << "...Initializing UI..." << std::endl;
        std::cout << "... Success! ..." << std::endl;
    }

    JWindow* CreateJWindow() {
        return new JWindow();  // Properly allocate a new JWindow
    }
}