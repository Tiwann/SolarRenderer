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
	

	newoption {
		trigger = "console",
		description = "Use default console subsystem or WindowedApp",
	}
	
	newoption {
    		trigger = "windowed",
    		description = "Use default console subsystem or WindowedApp",
    }