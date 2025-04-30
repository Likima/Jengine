#include "Core.h"

#include "Version.h"

#include <iostream>

namespace Core {

	void Initialize()
	{
		std::cout << "Welcome to JEngine V" << GET_VERSION << std::endl;

	}

}