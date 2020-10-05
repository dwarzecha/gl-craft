workspace "gl-craft"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "gl-craft"
	location "gl-craft"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/Source/**.hpp",
		"%{prj.name}/Source/**.cpp",
		"%{prj.name}/Res/**.png",
		"%{prj.name}/Res/**.txt"
	}

	includedirs
	{
		"%{prj.name}/Dependencies/glm-0.9.9.7",
		"%{prj.name}/Dependencies/glew-2.1.0/include",
		"%{prj.name}/Dependencies/SFML-2.5.1/include"
	}

	libdirs
	{
		"%{prj.name}/Dependencies/glew-2.1.0/lib/Release/x64",
		"%{prj.name}/Dependencies/SFML-2.5.1/lib"
	}

	links
	{
		"glew32s.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "Off"
		systemversion "10.0.17763.0"

		defines
		{
			"GLEW_STATIC",
			"SFML_STATIC",
			"_MBCS"
		}

		--flags
		--{
		--	"ConformanceMode" --important in MSVC, not sure where else / not available yet
		--}

	filter "configurations:Debug"
		symbols "On"

		links
		{
			"sfml-graphics-s-d",
			"sfml-window-s-d",
			"sfml-system-s-d",
			"opengl32",
			"freetype",
			"sfml-system-s-d",
			"winmm",
			"gdi32",
			"sfml-audio-s-d",
			"openal32",
			"flac",
			"vorbisenc",
			"vorbisfile",
			"vorbis",
			"ogg"
		}

	filter "configurations:Release"
		optimize "Speed"
		--optimize "Full" / optimize "On" - check it! (propably "Speed" is good)

		links
		{
			"sfml-graphics-s",
			"sfml-window-s",
			"sfml-system-s",
			"opengl32",
			"freetype",
			"sfml-system-s",
			"winmm",
			"gdi32",
			"sfml-audio-s",
			"openal32",
			"flac",
			"vorbisenc",
			"vorbisfile",
			"vorbis",
			"ogg"
		}

		flags
		{
			"LinkTimeOptimization" --cool, sth like merge all code to one file
		}