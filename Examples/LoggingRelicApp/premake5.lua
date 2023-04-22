project "LoggingRelicApp"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"
    
    targetdir ("../../bin/" .. outputdir .. "/%{prj.name}")
    objdir ("../../build/" .. outputdir .. "/%{prj.name}")

    pchheader "pch.h"

    files 
    {
        "source/**.h", 
        "source/**.cpp" 
    }

    includedirs
    {
        "../../Relic/source",
        "../../Relic/vendor/spdlog/include"
    }

    defines { "SFML_STATIC" }
    libdirs { "../../Relic/vendor/sfml/lib" }

    links
    {
        "Relic",
        "sfml-graphics-s",
        "sfml-window-s",
        "sfml-system-s",
        "opengl32",
        "winmm",
        "freetype",
        "gdi32"
    }


    filter "system:windows"
        systemversion "latest"

    filter "system:linux"
        systemversion "latest"

    filter "configurations:Debug"
        defines { "RL_DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "RL_RELEASE" }
        runtime "Release"
        optimize "On"
        symbols "On"

    filter "configurations:Dist"
        kind "WindowedApp"
        defines { "RL_DIST" }
        runtime "Release"
        optimize "On"
        symbols "Off"
