#include "GameState.h"

using namespace BTEngine;
using namespace BTEngine::Graphics;
using namespace BTEngine::Input;

void GameState::Initialize()
{

	mCamera.SetPosition(mCameraPos);
	mCamera.SetLookAt(mCameraLookAt);

	mConstantBuffer.Initialize(sizeof(Matrix4));

	std::filesystem::path shaderFile = L"../../Assets/Shaders/DoTexturing.fx";
	mVertexShader.Initialize(shaderFile, VE_Position | VE_TexCoord);
	mPixShader.Initialize(shaderFile);
	
	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
	mWorldTrans = Matrix4::Identity;

	mSkySphere.Initialize();
	mSun.Initialize();
	mMercury.Initialize();
	mVenus.Initialize();
	mEarth.Initialize();
}
void GameState::Terminate()
{
	mSkySphere.Terminate();
	mSun.Terminate();
	mMercury.Terminate();
	mVenus.Terminate();
	mEarth.Terminate();

	mSampler.Terminate();
	mPixShader.Terminate();
	mVertexShader.Terminate();
	mConstantBuffer.Terminate();
}

void GameState::Update(float deltaTime)
{
	auto inputSystem = InputSystem::Get();
	if (inputSystem->IsKeyDown(KeyCode::S))
	{
		mCameraPos.z -= BTMath::Constants::HalfPi * deltaTime * mCameraMoveSpeed;
		if(mCameraLookAt.y > 0)
			mCameraPos.y -= BTMath::Constants::HalfPi * deltaTime * mCameraMoveSpeed;
		else if(mCameraLookAt.y < 0)
			mCameraPos.y += BTMath::Constants::HalfPi * deltaTime * mCameraMoveSpeed;
		mCamera.SetPosition(mCameraPos);
	}
	if (inputSystem->IsKeyDown(KeyCode::W))
	{
		mCameraPos.z += BTMath::Constants::HalfPi * deltaTime * mCameraMoveSpeed;
		if (mCameraLookAt.y > 0)
			mCameraPos.y += BTMath::Constants::HalfPi * deltaTime * mCameraMoveSpeed;
		else if (mCameraLookAt.y < 0)
			mCameraPos.y -= BTMath::Constants::HalfPi * deltaTime * mCameraMoveSpeed;
		mCamera.SetPosition(mCameraPos);
	}
	if (inputSystem->IsKeyDown(KeyCode::D))
	{
		mCameraPos.x += BTMath::Constants::HalfPi * deltaTime * mCameraMoveSpeed;
		mCamera.SetPosition(mCameraPos);
	}
	if (inputSystem->IsKeyDown(KeyCode::A))
	{
		mCameraPos.x -= BTMath::Constants::HalfPi * deltaTime * mCameraMoveSpeed;
		mCamera.SetPosition(mCameraPos);
	}

	if (inputSystem->IsMouseDown(MouseButton::LBUTTON) || inputSystem->IsMouseDown(MouseButton::RBUTTON))
	{
		mCameraLookAt.x += inputSystem->GetMouseMoveX() * deltaTime;
		mCameraLookAt.y -= inputSystem->GetMouseMoveY() * deltaTime;
		mCamera.SetLookAt(mCameraLookAt);
	}

	mSun.Update(deltaTime);
	mMercury.Update(deltaTime);
	mVenus.Update(deltaTime);
	mEarth.Update(deltaTime);
}

void GameState::Render()
{
	mVertexShader.Bind();
	mPixShader.Bind();
	mSampler.BindPS(0);

	RenderMesh(mCamera, true);
}

void GameState::RenderMesh(const Camera& camera, bool useTransform)
{
	mSkySphere.Render(camera, mConstantBuffer, useTransform);
	mSun.Render(camera, mConstantBuffer, useTransform);
	mMercury.Render(camera, mConstantBuffer, useTransform);
	mVenus.Render(camera, mConstantBuffer, useTransform);
	mEarth.Render(camera, mConstantBuffer, useTransform);
}

void GameState::DebugUI()
{
	ImGui::Begin("Debug Draw", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	mEarth.DebugUI();
	
	SimpleDraw::Render(mCamera);
	ImGui::End();
}
