project "Engine"
     kind "StaticLib"
     language "C++"
     cppdialect "C++17"
     targetdir "Binaries/%{cfg.buildcfg}"
     staticruntime "off"

     defines {
          "PROJECT_ROOT=\"" .. os.getcwd() .. "\"",
      }

     files { "Source/**.h", "Source/**.cpp" }

     includedirs
     {
          "Source",
          "../UI/Source",
          "../Game/Source",
          "../Game/ColorWave",
          "../Core/Source"
     }

     links
     {
         "UI",
         "Game",
     }

    
     filter "system:linux"
         links { "GL", "GLEW", "glfw" }
         
     filter "system:windows"
         links { "opengl32", "glew32", "glfw3" }
         
     filter "system:macosx"
         links { "OpenGL.framework", "GLEW", "glfw" }
    filter "system:macosx"
         links { "OpenGL.framework", "glfw" }  -- Link OpenGL and GLFW on macOS

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
