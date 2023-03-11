#pragma once

#include <BTEngine/Inc/BTEngine.h>

#include "RenderObject.h"

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
	void RenderMesh(const Camera& camera, bool useTransform);

	Camera mCamera;
	ConstantBuffer mConstantBuffer;
	VertexShader mVertexShader;
	PixShader mPixShader;

	SkySphere mSkySphere;
	Sun mSun;
	Mercury mMercury;
	Venus mVenus;
	Earth mEarth;

	Sampler mSampler;
	Matrix4 mWorldTrans;

	float mCameraMoveSpeed = 5;

	Vector3 mCameraPos =  { 0.f,50.f,-100.f };
	Vector3 mCameraLookAt = { 0.f,0.f,0.f };

};