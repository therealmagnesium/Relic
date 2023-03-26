project "RelicApp"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++14"
    staticruntime "off"

    files { "source/**.h", "source/**.cpp" }

    includedirs
    {
        "source",
        "../Relic/source",
        "../Relic/vendor/spdlog/include",
        "../Relic/SDL2/include"
    }

    links
    {
        "Relic",
        "SDL2main",
        "SDL2",
        "SDL2_image"
    }

    targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
    objdir ("../build/" .. outputdir .. "/%{prj.name}")

    filter "system:windows"
    systemversion "latest"
    defines { "GL_PLATFORM_WINDOWS" }

    filter "configurations:Debug"
        defines { "GL_DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "GL_RELEASE" }
        runtime "Release"
        optimize "On"
        symbols "On"

    filter "configurations:Dist"
        kind "WindowedApp"
        defines { "GL_DIST" }
        runtime "Release"
        optimize "On"
        symbols "Off"