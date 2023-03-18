#include <BTEngine/Inc/BTEngine.h>
#include "GameState.h"

using namespace BTEngine;

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	AppConfig config;
	config.appName = L"Solar System";
	
	App myApp;
	myApp.AddState<GameState>("GameState");
	myApp.Run(config);
	return 0;
}