#include "ui_core.h"
#include "JWindow.h"

#include <iostream>


namespace UI_Core {

	void Initialize()
	{
		std::cout << "...Initializing UI..." << std::endl;
        JWindow jw;
        std::cout << "... Success! ..." << std::endl;
	}

}