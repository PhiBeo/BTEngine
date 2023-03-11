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

protected:

	Camera mCamera;
	ConstantBuffer mConstantBuffer;
	MeshBuffer mMeshBuffer;
	VertexShader mVertexShader;
	PixShader mPixShader;

	Texture mDiffuseTexture;
	Sampler mSampler;

	bool mDrawWorld = true;
	bool mDrawSphere = true;
	bool mDrawAABBBox = false;
	bool mDrawFillAABBBox = false;

	Color mSphereColor = Colors::White;
	Color mBoxColor = Colors::White;
	Color mFillBoxColor = Colors::White;

	Vector3 mSpherePos = { 0.f,0.f,0.f };
	Vector3 mBoxPos = { 0.f,0.f,0.f };
	Vector3 mFillBoxPos = { 0.f,0.f,0.f };

	float mSphereSize = 1.f;
	float mBoxSize = 1.f;
	float mFillBoxSize = 1.f;

};