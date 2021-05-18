workspace "Bamboo"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Import GLFW and GLAD and ImGui---------------------------------------
IncludeDir = {}
IncludeDir["GLFW"]		= "Bamboo/vendor/glfw/include"
IncludeDir["GLAD"]		= "Bamboo/vendor/glad/include"
IncludeDir["ImGui"]		= "Bamboo/vendor/imgui"
IncludeDir["glm"]		= "Bamboo/vendor/glm"
IncludeDir["stb_image"]	= "Bamboo/vendor/stb_image"
IncludeDir["entt"]		= "Bamboo/vendor/entt/include"

include "Bamboo/vendor/glfw"
include "Bamboo/vendor/glad"
include "Bamboo/vendor/imgui"
-- ---------------------------------------------------

project "Bamboo"
	location "Bamboo"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("tmp/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/assets/shaders/**.glsl",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}",
	}

	links
	{
		"GLFW",
		"GLAD",
		"ImGui",
		"OpenGL32.Lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"BB_PLATFORM_WINDOWS",
			"BB_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "BAMBOO_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "BAMBOO_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "BAMBOO_DIST"
		runtime "Release"
		optimize "on"

	filter {"system:windows","configurations:Debug"}
		buildoptions "/MTd"

	filter {"system:windows","configurations:Release"}
		buildoptions "/MT"

	filter {"system:windows","configurations:Dist"}
		buildoptions "/MT"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("tmp/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"Bamboo/vendor/spdlog/include",
		"Bamboo/src",
		"Bamboo/vender",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
	}

	links
	{
		"Bamboo"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"BB_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "SANDBOX_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "SANDBOX_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "SANDBOX_DIST"
		runtime "Release"
		optimize "on"

	filter {"system:windows","configurations:Debug"}
		buildoptions "/MTd"

	filter {"system:windows","configurations:Release"}
		buildoptions "/MT"

	filter {"system:windows","configurations:Dist"}
		buildoptions "/MT"
