project "Game"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++17"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"

   files { "Source/**.h", "Source/**.cpp" }

   includedirs
   {
      "Source",
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
   
   filter {}

   targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

   -- Add other configurations as needed