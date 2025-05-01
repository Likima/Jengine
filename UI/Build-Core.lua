project "UI"
   kind "StaticLib"
   language "C++"
   cppdialect "C++17" 
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"

   files { "Source/**.h", "Source/**.cpp" }

   includedirs
   {
      "Source"
   }

   -- Add GLFW linkage for different platforms
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