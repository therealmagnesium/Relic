project "Relic"
    kind "StaticLib"
    language "C++"
    cppdialect "C++14"
    staticruntime "on"

    targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
    objdir ("../build/" .. outputdir .. "/%{prj.name}")
    
    files 
    { 
        "source/**.h", 
        "source/**.cpp"
    }
    
    includedirs
    {
        "source",

        "vendor/sfml/include",
        "vendor/spdlog/include"
    }

    libdirs { "vendor/sfml/lib" }

    links
    {
        "sfml-main",
        "sfml-system",
        "sfml-graphics",
        "sfml-window"
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