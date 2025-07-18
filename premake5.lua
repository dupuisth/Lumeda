include "dependencies.lua"

workspace "Lumeda"
    architecture "x64"

    configurations
    {
        "Debug",
        "Staging",
        "Release"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Lumeda"
    location "Lumeda"
    kind "StaticLib"
    language "C++"
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs
    {
        "Lumeda/src",
        "%{IncludeDir.spdlog}"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"
        
        defines 
        {
            "LUMEDA_PLATFORM_WINDOWS",
            "LUMEDA_BUILD_DLL"
        }
    
    filter "configurations:Debug"
        defines "LUMEDA_DEBUG"
        symbols "On"
    
    filter "configurations:Staging"
        defines "LUMEDA_STAGING"
        optimize "On"

    filter "configurations:Release"
        defines "LUMEDA_RELEASE"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs
    {
        "Lumeda/src",
        "%{IncludeDir.spdlog}"
    }

    links
    {
        "Lumeda"
    }
    
    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"
        
        defines 
        {
            "LUMEDA_PLATFORM_WINDOWS"
        }
    
    filter "configurations:Debug"
        defines "LUMEDA_DEBUG"
        symbols "On"
    
    filter "configurations:Staging"
        defines "LUMEDA_STAGING"
        optimize "On"

    filter "configurations:Release"
        defines "LUMEDA_RELEASE"
        optimize "On"