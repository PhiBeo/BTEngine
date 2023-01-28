#include "Precompiled.h"
#include "App.h"

using namespace BTEngine;
using namespace BTEngine::Core;

void App::Run(const AppConfig& config)
{
	Window myWindow;
	myWindow.Initialize(
		GetModuleHandle(nullptr),
		config.appName,
		config.winWidth,
		config.winHeight
	);
	//ASSERT(myWindow.isActive(), "Failed to create window!");

	mRunning = true;
	while (mRunning)
	{
		myWindow.ProcessMessage();

		if (!myWindow.isActive())
		{
			Quit();
		}
		//running game
		auto deltaTime = TimeUtil::GetDeltaTime();
	}

	//terminate static classes
	myWindow.Terminate();
}

void App::Quit()
{
	mRunning = false;
}