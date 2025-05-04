#include "Core.h"

#include "Version.h"

#include "Dependancies/libs.h"

#include <iostream>

namespace Core {

	void Initialize()
	{
		std::cout << "Welcome to JEngine V" << GET_VERSION << std::endl;
		// load_gl_extensions();
	}

}