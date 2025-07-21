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

group "Vendor"
    include "Lumeda/vendor"
group ""

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
        "%{prj.name}/vendor/stb_image/stb_image.h",
        "%{prj.name}/vendor/stb_image/stb_image.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl"
    }

    includedirs
    {
        "Lumeda/src",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.glfw}",
        "%{IncludeDir.glad}",
        "%{IncludeDir.stb_image}",
        "%{IncludeDir.glm}",
    }

    links
    {
        "GLFW",
        "glad",
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
        includedirs
        {
            "%{IncludeDir.tracy}"
        }    
        links
        {
            "tracy"
        }
    
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
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.glm}",
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
        includedirs
        {
            "%{IncludeDir.tracy}"
        }  
        defines "LUMEDA_DEBUG"
        symbols "On"
    
    filter "configurations:Staging"
        defines "LUMEDA_STAGING"
        optimize "On"

    filter "configurations:Release"
        defines "LUMEDA_RELEASE"
        optimize "On"