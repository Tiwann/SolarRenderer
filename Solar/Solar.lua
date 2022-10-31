project "Solar"
    kind "ConsoleApp"
    language "C++"
    staticruntime "On"
    cppdialect "C++20"
	targetdir (binaries)
	objdir (objs)

    files {
        "Solar.lua",
        "Include/**.h",
        "Source/**.cpp",
        "External/glm/**.hpp",
        "External/glm/**.inl",
        "Shaders/**.vert",
        "Shaders/**.frag",
        "Shaders/**.glsl",
        "Assets/**"
    }

    includedirs {
        "Include",
        "Include/Solar",
        "External/glm",
        "%{wks.location}/Vendor/glad/include",
        "%{wks.location}/Vendor/glfw/include",
        "%{wks.location}/Vendor/imgui",
        "%{wks.location}/Vendor/spdlog/include",
    }

    defines {
        "SOLAR_USE_CASSERT"
    }

    links {
        "glad",
        "glfw",
        "imgui",
        "spdlog"
    }

    filter "Configurations:Debug"
		runtime "Debug"
		symbols "On"
		defines "SOLAR_DEBUG"

	filter "Configurations:Release"
		runtime "Release"
		optimize "On"
		symbols "Off"
		defines "SOLAR_RELEASE"
		
	filter "Options:subsystem=windowed"
	    kind "WindowedApp"
	     
    filter "System:Windows"
        defines "_CRT_SECURE_NO_WARNINGS"

    