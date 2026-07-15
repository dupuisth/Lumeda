project "googletest"
    language "C++"
    cppdialect "C++20"
    removeconfigurations { "Profiling" }

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
    
    kind "StaticLib"
    
    includedirs { 
        "googletest/googletest/include",
        "googletest/googletest",
    }
    
    files { 
        "googletest/googletest/src/*.cc",
        "googletest/googletest/include/*.h" 
    }
