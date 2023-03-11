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
	void Refresh();
	void StartMesh();
	//virtual void DrawMesh() = 0;

protected:
	struct Vertex
	{
		Vector3 position;
		Color color;
	};

	using Vertices = std::vector<Vertex>;
	Vertices mVertices;

	Camera mCamera;
	ConstantBuffer mConstantBuffer;
	MeshBuffer mMeshBuffer;
	VertexShader mVertexShader;
	PixShader mPixShader;
};

class RectState : public GameState
{
public:
	void DrawMesh();
	void Update(float deltaTime);
};