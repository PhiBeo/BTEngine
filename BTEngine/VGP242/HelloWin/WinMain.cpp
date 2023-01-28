#include <BTEngine/Inc/BTEngine.h>

using namespace BTEngine;
int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	AppConfig config;
	config.appName = L"Hello Window";
	
	App myApp;
	myApp.Run(config);
	return 0;
}