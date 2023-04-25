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

    libdirs { "vendor/sfml/lib" }

    filter "system:windows"
        defines { "SFML_STATIC" }
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
        systemversion "latest"   
    
    filter "system:linux"
        links
        {
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
        defines { "RL_DIST" }
        runtime "Release"
        optimize "On"
        symbols "Off"
