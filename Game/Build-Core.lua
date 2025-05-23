project "Game"
   kind "StaticLib"  -- Changed from ConsoleApp to StaticLib
   language "C++"
   cppdialect "C++17"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"

   files { 
    "Source/**.h", 
    "Source/**.hpp",
    "Source/**.cpp",
    "ColorWave/**.h",
    "ColorWave/**.hpp",
    "ColorWave/**.cpp"
    }   
   includedirs
   {
      "Source",
      "ColorWave",
      "../Engine/Source"
   }

   targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines { }

   filter "configurations:Debug"
       defines { "DEBUG" }
       runtime "Debug"
       symbols "On"

   filter "configurations:Release"
       defines { "RELEASE" }
       runtime "Release"
       optimize "On"
       symbols "On"

   filter "configurations:Dist"
       defines { "DIST" }
       runtime "Release"
       optimize "On"
       symbols "Off"