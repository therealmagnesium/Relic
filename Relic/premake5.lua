project "Relic"
    kind "StaticLib"
    language "C++"
    cppdialect "C++14"
    staticruntime "on"

    files { "source/**.h", "source/**.cpp" }

    includedirs
    {
        "source",

        "../vendor/SDL2/include"
    }

    libdirs { "../vendor/SDL2/lib" }

    links
    {
        "mingw32",
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
        defines { "GL_DIST" }
        runtime "Release"
        optimize "On"
        symbols "Off"