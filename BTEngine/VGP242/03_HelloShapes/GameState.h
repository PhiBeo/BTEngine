#pragma once

#include "BTEngine/Inc/AppState.h"

using namespace BTEngine;
using namespace BTEngine::Input;
using namespace BTEngine::Graphics;

class GameState : public AppState
{
public:
	void Initialize() {}
	void Terminate() {}
	void Update(float deltaTime) 
	{
		auto inputSystem = InputSystem::Get();
		auto graphicsSystem = GraphicsSystem::Get();

		if (inputSystem->IsKeyDown(KeyCode::SPACE))
			graphicsSystem->SetClearColor(Colors::AliceBlue);
		else if (inputSystem->IsKeyDown(KeyCode::BACKSPACE))
			graphicsSystem->SetClearColor(Colors::Black);
		else if (inputSystem->IsKeyDown(KeyCode::UP))
			graphicsSystem->SetClearColor(Colors::DarkRed);
		else if (inputSystem->IsKeyDown(KeyCode::DOWN))
			graphicsSystem->SetClearColor(Colors::LightYellow);
		else if (inputSystem->IsKeyDown(KeyCode::RIGHT))
			graphicsSystem->SetClearColor(Colors::Chocolate);
		else if (inputSystem->IsKeyDown(KeyCode::LEFT))
			graphicsSystem->SetClearColor(Colors::Aqua);
	}
	void Render() {}
	void DebugUI() {}
};