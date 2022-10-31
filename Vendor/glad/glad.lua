project "glad"
    kind "StaticLib"
    language "C"
    staticruntime "On"
    targetdir (binaries)
    objdir (objs)

    files {
        "src/gl.c",
        "src/vulkan.c",
        "include/glad/gl.h",
        "include/glad/vulkan.h",
        "include/KHR/khrplatform.h",
        "include/vk_platform.h",
    }

    includedirs {
        "include"
    }

    filter "configurations:Debug"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		runtime "Release"
		optimize "On"
		symbols "Off"

