#include "Core/Core.h"
#include "UI_Core/ui_core.h"
#include "JEngine_Core/jengine_core.h"

int main()
{
	Core::Initialize();

	UI_Core::Initialize();

	JEngine_Core::Initialize();
}