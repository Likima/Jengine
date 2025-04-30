#include "Core.h"
#include "../Version.h"

#include <iostream>

namespace Core {

	void PrintHelloWorld()
	{
		std::cout << "Welcome to JEngine V" << GET_VERSION << std::endl;

		std::cin.get();
	}

}