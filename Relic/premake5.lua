project "Relic"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
    objdir ("../build/" .. outputdir .. "/%{prj.name}")

    pchheader "pch.h"

    files 
    { 
        "source/**.h", 
        "source/**.cpp"
    }
    
    includedirs
    {
        "source",
        "source/Relic",

        "vendor/sfml/include",
        "vendor/spdlog/include"
    }

    defines { "SFML_STATIC" }
    libdirs { "vendor/sfml/lib" }

    links
    {
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
        defines { "RL_DIST" }
        runtime "Release"
        optimize "On"
        symbols "Off"
