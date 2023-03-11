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

protected:

	Camera mCamera;
	ConstantBuffer mConstantBuffer;
	MeshBuffer mMeshBuffer;
	VertexShader mVertexShader;
	PixShader mPixShader;

	Texture mDiffuseTexture;
	Sampler mSampler;
};