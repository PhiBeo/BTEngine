#include "Precompiled.h"
#include "BTEngine.h"

BTEngine::App& BTEngine::MainApp()
{
	static App sApp;
	return sApp;
}