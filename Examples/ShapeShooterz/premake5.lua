project "ShapeShooterz"
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

    libdirs 
    { 
        "../../Relic/vendor/sfml/lib",
        "../../Relic/vendor/imgui/lib",
    }

    filter "system:windows"
        defines { "SFML_STATIC" }
        links
        {
            "Relic",
            "ImGui", 
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
            "ogg", 
        }
        postbuildcommands
        {
            "cp -rf assets ../../bin/" .. outputdir .. "/%{prj.name}",
            "cp -rf data ../../bin/" .. outputdir .. "/%{prj.name}",
            "cp -f %{wks.location}/vendor/windows/bin/* ../../bin/" .. outputdir .. "/%{prj.name}"
        }
        systemversion "latest"   

    filter "system:linux"
        links
        {
            "Relic",
            "ImGui",
            "sfml-graphics",
            "sfml-window",
            "sfml-audio",
            "sfml-system"
        }
        postbuildcommands
        {
            "cp -rf assets ../../bin/" .. outputdir .. "/%{prj.name}",
            "cp -rf data ../../bin/" .. outputdir .. "/%{prj.name}",
            "cp -f %{wks.location}/vendor/windows/bin/* ../../bin/" .. outputdir .. "/%{prj.name}"
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
