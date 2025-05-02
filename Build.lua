workspace "JEngine"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "App"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

-- Process projects in dependency order
group "Dependencies"
   include "Core/Build-Core.lua"
   include "UI/Build-Core.lua"
   include "Game/Build-Core.lua" 
group ""

group "Engine"
   include "Engine/Build-Core.lua"
group ""

include "App/Build-App.lua"