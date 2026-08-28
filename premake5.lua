include "dependencies.lua"

workspace "Lumeda"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Profiling"
    }

    flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Vendor"
    include "Lumeda/vendor"
group ""

group "TestVendor"
    include "LumedaTest/vendor"
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
        "%{IncludeDir.tinyxml2}",
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

        buildoptions { "/Zc:preprocessor" }

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
        links
        {
            "assimpd"
        }
    
    filter "configurations:Release"
        defines "LUMEDA_RELEASE"
        runtime "Release"
        optimize "On"
        links
        {
            "assimp"
        }

    filter "configurations:Profiling"
        defines
        {
            "LUMEDA_PROFILING"
        }
        runtime "Release"
        optimize "On"
        symbols "On"
        includedirs
        {
            "%{IncludeDir.tracy}"
        }
        links
        {
            "tracy",
            "assimp"
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
        "Sandbox/src",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.imgui}",
        "%{IncludeDir.glfw}",
        "%{IncludeDir.glad}",
        "%{IncludeDir.tinyxml2}",
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

        buildoptions { "/Zc:preprocessor" }

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
        defines "LUMEDA_DEBUG"
        symbols "On"
    
    filter "configurations:Release"
        runtime "Release"
        defines "LUMEDA_RELEASE"
        optimize "On"

    filter "configurations:Profiling"
        runtime "Release"
        defines "LUMEDA_PROFILING"
        optimize "On"
        symbols "On"
        includedirs
        {
            "%{IncludeDir.tracy}"
        }
        filter { "system:linux", "configurations:Profiling" }
        links
        {
            "tracy"
        }

project "LumedaTest"
    location "LumedaTest"
    --kind "ConsoleApp"
    kind "None" -- Skip for now, the lumedaMain prevent tests from working...
    language "C++"
    removeconfigurations { "Profiling" }

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    defines
    {
        "LUMEDA_TESTING"
    }

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
        "%{IncludeDir.googletest}",
    }

    libdirs 
    { 
        "Lumeda/libs/%{cfg.system}/%{cfg.buildcfg}" 
    }

    links
    {
        "Lumeda",
        "googletest"
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
        defines "LUMEDA_DEBUG"
        symbols "On"
    
    filter "configurations:Release"
        runtime "Release"
        defines "LUMEDA_RELEASE"
        optimize "On"
