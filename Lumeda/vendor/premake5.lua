project "GLFW"
    kind "StaticLib"
    language "C"
    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
    
    files
    {
        "glfw/include/GLFW/glfw3.h",
        "glfw/include/GLFW/glfw3native.h",
        "glfw/src/glfw_config.h",
        "glfw/src/context.c",
        "glfw/src/init.c",
        "glfw/src/input.c",
        "glfw/src/monitor.c",
        "glfw/src/vulkan.c",
        "glfw/src/window.c",
        "glfw/src/platform.c",
        "glfw/src/null_init.c",
        "glfw/src/null_joystick.c",
        "glfw/src/null_monitor.c",
        "glfw/src/null_window.c"
    }
    
    filter "system:windows"
        systemversion "latest"
        staticruntime "On"
        
        files
        {
            "glfw/src/win32*.c",
            "glfw/src/wgl_context.c",
            "glfw/src/egl_context.c",
            "glfw/src/osmesa_context.c"
        }
        
        defines 
        { 
            "_GLFW_WIN32",
            "_CRT_SECURE_NO_WARNINGS"
        }
    
    filter "system:linux"
        pic "On"
        staticruntime "On"
        
        files
        {
            "glfw/src/x11_init.c",
            "glfw/src/x11_monitor.c",
            "glfw/src/x11_window.c",
            "glfw/src/xkb_unicode.c",
            "glfw/src/posix_time.c",
            "glfw/src/posix_thread.c",
            "glfw/src/posix_module.c",
            "glfw/src/glx_context.c",
            "glfw/src/egl_context.c",
            "glfw/src/osmesa_context.c",
            "glfw/src/linux_joystick.c",
            "glfw/src/posix_poll.c"
        }
        
        defines
        {
            "_GLFW_X11"
        }
    
    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"
    
    filter "configurations:Release"
        runtime "Release"
        optimize "on"

project "glad"
    kind "StaticLib"
    language "C"
    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
    
    files
    {
        "glad/src/glad.c"
    }
    
    includedirs
    {
        "glad/include"
    }
    
    filter "system:windows"
        systemversion "latest"
        staticruntime "On"
        cppdialect "C++20"
    
    filter "system:linux"
        pic "On"
        staticruntime "On"
        cppdialect "C++20"
    
    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"
    
    filter "configurations:Release"
        runtime "Release"
        optimize "on"

project "tracy"
    kind "StaticLib"
    language "C++"
    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
    
    files
    {
        "tracy/public/TracyClient.cpp"
    }
    
    includedirs
    {
        "tracy/public"
    }
    
    filter "system:windows"        
        systemversion "latest"
        staticruntime "on"
    
    filter "system:linux"
        pic "On"
        staticruntime "On"
    
    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"
        defines "TRACY_ENABLE"
    
    filter "configurations:Release"
        runtime "Release"
        optimize "on"

project "ImGui"
    kind "StaticLib"
    language "C++"
    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
    
    includedirs
    {
        "imgui/",
        "glfw/include/"
    }
    
    files
    {
        "imgui/imconfig.h",
        "imgui/imgui.h",
        "imgui/imgui.cpp",
        "imgui/imgui_draw.cpp",
        "imgui/imgui_internal.h",
        "imgui/imgui_widgets.cpp",
        "imgui/imstb_rectpack.h",
        "imgui/imstb_textedit.h",
        "imgui/imstb_truetype.h",
        "imgui/imgui_demo.cpp",
        "imgui/imgui_tables.cpp",
        "imgui/backends/imgui_impl_glfw.h",
        "imgui/backends/imgui_impl_glfw.cpp",
        "imgui/backends/imgui_impl_opengl3.h",
        "imgui/backends/imgui_impl_opengl3.cpp"
    }
    
    filter "system:windows"
        systemversion "latest"
        cppdialect "C++20"
        staticruntime "On"
    
    filter "system:linux"
        pic "On"
        cppdialect "C++20"
        staticruntime "On"
    
    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"
    
    filter "configurations:Release"
        runtime "Release"
        optimize "on"