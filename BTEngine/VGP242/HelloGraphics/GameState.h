#pragma once

#include "BTEngine/Inc/AppState.h"

using namespace BTEngine;

class GameState : public AppState
{
public:
	void Initialize() {}
	void Terminate() {}
	void Update(float deltaTime) 
	{
		auto inputSystem = Input::InputSystem::Get();
		auto graphicsSystem = Graphics::GraphicsSystem::Get();

		if (inputSystem->IsKeyDown(Input::KeyCode::SPACE))
			graphicsSystem->SetClearColor(Colors::AliceBlue);
		else if (inputSystem->IsKeyDown(Input::KeyCode::ENTER))
			graphicsSystem->SetClearColor(Colors::Black);
	}
	void Render() {}
	void DebugUI() {}
};