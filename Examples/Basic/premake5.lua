project "Basic"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"
    
    targetdir ("../../bin/" .. outputdir .. "/%{prj.name}")
    objdir ("../../build/" .. outputdir .. "/%{prj.name}")

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
            "sfml-audio-s",
            "sfml-system-s",
            "opengl32",
            "winmm",
            "freetype",
            "gdi32",
            "openal32",
            "FLAC",
            "vorbisenc",
            "vorbisfile",
            "vorbis",
            "ogg"
        } 
        systemversion "latest"   
    
    filter "system:linux"
        links
        {
            "Relic",
            "sfml-graphics",
            "sfml-window",
            "sfml-audio",
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
