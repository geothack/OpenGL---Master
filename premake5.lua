
workspace "OpenGLBreakout"
    configurations {"Debug","Release"}
    

project "OpenGLBreakout"
    kind "ConsoleApp"

    language "C++"
    cppdialect "C++latest"
    targetdir "bin/%{cfg.buildcfg}"

    architecture ("x64")

    includedirs 
    { 
        --"libs/sdl3/include", 
        "src", 
        --"libs/glad/glad/include", 
        
  }

    --libdirs { "libs/sdl3/lib/x64", "libs/ttf/lib", "libs/openal/libs", "libs/snd/libs" }

    --links { "SDL3.dll","SDL3.lib","freetype.lib","freetype.dll","OpenAL32.lib","OpenAL32.dll" }

   files
    { 
      "src/**.h", 
      "src/**.cpp", 
      "src/**.c"
    }

    --pchheader "Utility/PreLibrary.h"
    --pchsource "src/Game/Utility/PreLibrary.cpp"

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"
      buildoptions { "/MP" }
      kind "ConsoleApp"

      --links { "dsndfile.lib" }

      --postbuildcommands { "{COPY} libs/sdl3/lib/x64/SDL3.dll bin/Debug" }
      --postbuildcommands { "{COPY} libs/openal/libs/OpenAL32.dll bin/Debug" }

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
      buildoptions { "/MP" }
      kind "WindowedApp"

      --links { "rsndfile.lib" }

    --filter "files:**.c"
      --flags { "NoPCH" }

      --postbuildcommands { "{COPY} libs/sdl3/lib/x64/SDL3.dll bin/Release" }
      --postbuildcommands { "{COPY} libs/openal/libs/OpenAL32.dll bin/Release" }

    