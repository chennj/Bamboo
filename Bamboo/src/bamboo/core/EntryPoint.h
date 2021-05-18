#pragma once

#ifdef BB_PLATFORM_WINDOWS
#include "Application.h"

extern BAMBOO::Application* BAMBOO::CreateApplication();

int main(int argc, char** args)
{
	BAMBOO::Log::Init();

	BB_PROFILE_BEGIN_SESSION("Startup", "SEProfile-Startup.json");
	auto app = BAMBOO::CreateApplication();
	BB_PROFILE_END_SESSION();

	BB_PROFILE_BEGIN_SESSION("Startup", "SEProfile-Runtime.json");
	app->Run();
	BB_PROFILE_END_SESSION();

	BB_PROFILE_BEGIN_SESSION("Startup", "SEProfile-Shutdown.json");
	delete app;
	BB_PROFILE_END_SESSION();
}

#endif