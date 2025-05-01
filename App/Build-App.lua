project "App"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++17"  -- Make consistent with other projects
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"

   files { "Source/**.h", "Source/**.cpp" }

   includedirs
   {
      "Source",

      -- Include Core
      "../Core/Source",
      "../UI/Source",
      "../Engine/Source"
   }

   links
   {
      "Engine",
      "UI",
      "Core"

   }
   
   -- Add GLFW linkage for the executable
   filter "system:linux"
       links { "glfw", "GL", "X11", "pthread", "dl" }
   
   filter "system:windows"
       links { "glfw3", "opengl32" }
       
   filter "system:macosx"
       links { "glfw3", "Cocoa.framework", "OpenGL.framework", "IOKit.framework", "CoreVideo.framework" }
   
   filter {}  -- Reset filter

   targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines { "WINDOWS" }

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