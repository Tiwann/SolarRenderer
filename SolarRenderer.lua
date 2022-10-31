workspace "SolarRenderer"
	architecture "x64"
	configurations { "Debug", "Release" }
	flags "MultiProcessorCompile"
	startproject "Solar"

	binaries = "%{wks.location}/Binaries/%{cfg.buildcfg}"
	objs = "%{wks.location}/Intermediate"

	include "Vendor/Premake5/Clean.lua"
	include "Solar/Solar.lua"
	include "Vendor/glfw/glfw.lua"
	include "Vendor/glad/glad.lua"
	include "Vendor/imgui/imgui.lua"	
	include "Vendor/spdlog/spdlog.lua"
	
	newaction {
        trigger = "clean",
        description = "Clean all the generated files",
        
        onStart = function()
            print("Cleaning all the generated files...")
        end,
    
        execute = function()
            os.rmdir("Binaries")
            os.rmdir("Intermediate")
            os.rmdir(".vs")
            os.rmdir(".idea")
            os.remove("**.vcxproj")
            os.remove("**.vcxproj.filters")
            os.remove("**.vcxproj.user")
            os.remove("**.sln")
            os.remove("**.make")
            os.remove("**Makefile")
        end,
    
        onEnd = function()
            print("Done.")
        end
    }

	newoption {
		trigger = "subsystem",
		value = "SUBSYSTEM",
		description = "Use default console subsytem or WindowedApp",
		allowed = {
		   { "windowed", "Windowed application (Windows)" },
		   { "console",  "Default console application" }
		},
		default = "console"
	 }