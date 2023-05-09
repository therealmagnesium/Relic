project "ShapeShooterz"
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

    libdirs { "../../Relic/vendor/sfml/lib" }

    filter "system:windows"
        defines { "SFML_STATIC" }
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
        systemversion "latest"   
    
    filter "system:linux"
        links
        {
            "Relic",
            "sfml-graphics",
            "sfml-window",
            "sfml-system"
        } 
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
