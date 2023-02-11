#pragma once

#include <BTEngine/Inc/BTEngine.h>

using namespace BTEngine;
using namespace BTEngine::BTMath;
using namespace BTEngine::Graphics;

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

protected:
	struct Vertex
	{
		Vector3 position;
		Color color;
	};

	using Vertices = std::vector<Vertex>;
	Vertices mVertices;

	Camera mCamera;
	MeshBuffer mMeshBuffer;
	VertexShader mVertexShader;
	PixShader mPixShader;

	int pictureAt = 0;
};