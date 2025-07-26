
workspace "OpenGL-Master"
    configurations {"Debug","Release"}    

    startproject "OpenGL-Master"

project "OpenGL-Master"
    kind "ConsoleApp"

    language "C++"
    cppdialect "C++latest"
    targetdir "bin/%{cfg.buildcfg}"

    architecture ("x64")

    includedirs 
    { 
        "deps/glfw/include", 
        "src", 
        "deps/glad/include", 
        "deps/glm/include",
        "deps/assimp/include",
        "deps/ttf/include",
        "deps/box2d/include",
        "deps/entt/include",
        "deps/imgui/include",
    }

    libdirs 
    {
       "deps/glfw/lib", 
       "deps/assimp/lib", 
       "deps/ttf/lib", 
       "deps/box2d/lib",
    }

    links 
    {
       "glfw3.dll",
       "glfw3.lib",
       "Dear-ImGui",
       --"freetype.lib",
       --"freetype.dll",
       --"OpenAL32.lib",
       --"OpenAL32.dll"
    }

   files
    { 
      "src/**.h", 
      "src/**.cpp", 
      "src/**.c"
    }

    pchheader "Core/Core.h"
    pchsource "src/Core/Core.cpp"

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"
      buildoptions { "/MP" }
      kind "ConsoleApp"

      links 
      {
          "assimp-vc143-mtd.lib",
          "assimp-vc143-mtd.dll",
          "freetyped.lib",
          "box2dd.lib",
      }

      postbuildcommands { "{COPY} deps/glfw/lib/glfw3.dll bin/Debug" }
      postbuildcommands { "{COPY} deps/assimp/lib/assimp-vc143-mtd.dll bin/Debug" }

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
      buildoptions { "/MP" }
      kind "WindowedApp"

      links 
      {
          "assimp-vc143-mt.lib",
          "assimp-vc143-mt.dll",
          "freetype.lib",
          "rbox2d.lib",
      }

    filter "files:**.c"
      flags { "NoPCH" }

      --postbuildcommands { "{COPY} libs/sdl3/lib/x64/SDL3.dll bin/Release" }
      --postbuildcommands { "{COPY} libs/openal/libs/OpenAL32.dll bin/Release" }


project "Dear-ImGui"
    kind "StaticLib"

    language "C++"
    cppdialect "C++latest"
    targetdir "bin/%{cfg.buildcfg}"

    architecture ("x64")

    files
    { 
      "deps/imgui/**.h", 
      "deps/imgui/**.cpp"
    }

    includedirs 
    { 
        "deps/glfw/include", 
    }
