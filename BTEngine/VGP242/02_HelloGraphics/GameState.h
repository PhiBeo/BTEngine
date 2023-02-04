#pragma once

#include <BTEngine/Inc/BTEngine.h>

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

public:
	void SwitchPicture(int pictureNum);
	void Refresh();

private:
	struct Vertex
	{
		Vector3 position;
		Color color;
	};

	using Vertices = std::vector<Vertex>;
	Vertices mVertices;

	ID3D11Buffer* mVertexBuffer = nullptr;
	ID3D11VertexShader* mVertexShader = nullptr;
	ID3D11InputLayout* mInputLayout = nullptr;
	ID3D11PixelShader* mPixelShader = nullptr;

	int pictureAt = 0;
};