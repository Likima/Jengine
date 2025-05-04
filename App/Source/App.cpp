#include "Core/Core.h"
#include "UI_Core/ui_core.h"
#include "Engine_Core/jengine_core.h"

#include <GL/glew.h>
#define GLFW_INCLUDE_GLEXT
#include <GLFW/glfw3.h>

int main()
{
	Core::Initialize();

	load_gl_extensions();

	// UI_Core::Initialize();

	JEngine_Core::Initialize();
}