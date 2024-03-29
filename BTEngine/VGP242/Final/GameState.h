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
	Camera mRenderTargetCamera;
	ConstantBuffer mConstantBuffer;
	VertexShader mVertexShader;
	PixShader mPixShader;
	RenderTarget mRenderTarget;

	//render object
	SkySphere mSkySphere;
	Sun mSun;
	Mercury mMercury;
	Venus mVenus;
	Earth mEarth;
	Mars mMars;
	Jupiter mJupiter;
	Saturn mSaturn;
	Uranus mUranus;
	Neptune mNeptune;
	Pluto mPluto;

	Sampler mSampler;
	Matrix4 mWorldTrans;

	std::vector<RenderObject*> mPlanets;
	float mRenderTargetDistance;
	Vector3 mDistanceOffSet = { 0.f,0.f,-3.f };

	float mMasterSpeed = 1;
	float mMasterSpin = 1;

	int mCurrentSelectedPlanet = 0;

	Vector3 mCameraPos =  { 0.f,50.f,-100.f };
	Vector3 mCameraLookAt = { 0.f,0.f,0.f };

};