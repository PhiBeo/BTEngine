#pragma once

#include "BTEngine/Inc/AppState.h"

using namespace BTEngine;
using namespace BTEngine::BTMath;

class GameState : public AppState
{
public:
	void Initialize();
	void Terminate();
	void Update(float deltaTime);
	void Render();
	void DebugUI();

private:
	struct Vertex
	{
		Vector3 position;
		Color color;
	};

	ID3D11Buffer* mVertexBuffer = nullptr;
	ID3D11VertexShader* mVertexShader = nullptr;
	ID3D11InputLayout* mInputLayout = nullptr;
	ID3D11PixelShader* mPixelShader = nullptr;
};