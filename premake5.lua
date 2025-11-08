include "dependencies.lua"

workspace "Lumeda"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release"
    }

    flags
	{
		"MultiProcessorCompile"
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
        "%{IncludeDir.imgui}",
        "%{IncludeDir.imgui}" .. "/backends",
        "%{IncludeDir.assimp}",
    }

    libdirs 
    { 
        "%{prj.name}/libs/%{cfg.system}/%{cfg.buildcfg}" 
    }
    
    links
    {
        "GLFW",
        "glad",
        "ImGui"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"
        
        defines 
        {
            "LUMEDA_PLATFORM_WINDOWS",
            "LUMEDA_BUILD_DLL"
        }

    filter "system:linux"
        cppdialect "C++20"
        staticruntime "Off"
        systemversion "latest"
        pic "On"
        
        defines 
        {
            "LUMEDA_PLATFORM_LINUX"
        }

        links
        {
            "dl",
            "pthread"
        }
    
    filter "configurations:Debug"
        defines "LUMEDA_DEBUG"
        symbols "On"
        runtime "Debug"
        includedirs
        {
            "%{IncludeDir.tracy}"
        }    
        links
        {
            "tracy",
            "assimpd"
        }
    
    filter "configurations:Release"
        defines "LUMEDA_RELEASE"
        runtime "Release"
        optimize "On"
        links
        {
            "libassimp"
        }

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
        "%{IncludeDir.imgui}",
    }

    libdirs 
    { 
        "Lumeda/libs/%{cfg.system}/%{cfg.buildcfg}" 
    }

    links
    {
        "Lumeda"
    }
    
    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"
        
        defines 
        {
            "LUMEDA_PLATFORM_WINDOWS"
        }

        postbuildcommands
        {
            '{COPYFILE} "%{wks.location}Lumeda/libs/windows/%{cfg.buildcfg}/%{iif(cfg.buildcfg == "Debug", "assimpd", "assimp")}.dll" "%{cfg.buildtarget.directory}"'
        }

    filter "system:linux"
        cppdialect "C++20"
        staticruntime "Off"
        systemversion "latest"
        pic "On"
        
        defines 
        {
            "LUMEDA_PLATFORM_LINUX"
        }

        -- Link order is important on Linux!
        links
        {
            "assimp",
            "ImGui",
            "glad",
            "GLFW",
            "dl",
            "pthread",
            "X11",
            "GL",
            "z",
        }
    
    filter "configurations:Debug"
        runtime "Debug"
        includedirs
        {
            "%{IncludeDir.tracy}"
        }  
        defines "LUMEDA_DEBUG"
        symbols "On"
    
    filter "configurations:Release"
        runtime "Release"
        defines "LUMEDA_RELEASE"
        optimize "On"