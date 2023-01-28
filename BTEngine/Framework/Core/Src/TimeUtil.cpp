#include "Precompiled.h"
#include "TimeUtil.h"

float BTEngine::Core::TimeUtil::GetTime()
{
	static const auto startTime = std::chrono::high_resolution_clock::now();
	const auto currentTime = std::chrono::high_resolution_clock::now();
	const auto miliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();

	return miliseconds / 1000.f;
}

float BTEngine::Core::TimeUtil::GetDeltaTime()
{
	static auto lastCallTime = std::chrono::high_resolution_clock::now();
	const auto currentTime = std::chrono::high_resolution_clock::now();
	const auto miliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastCallTime).count();

	lastCallTime = currentTime;

	return miliseconds / 1000.f;
}