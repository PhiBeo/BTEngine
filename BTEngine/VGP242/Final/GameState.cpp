#include "GameState.h"

using namespace BTEngine;
using namespace BTEngine::Graphics;
using namespace BTEngine::Input;

void GameState::Initialize()
{
	mCamera.SetPosition(mCameraPos);
	mCamera.SetLookAt(mCameraLookAt);

	mRenderTargetCamera.SetPosition({ .0f, 2.f, mCameraPos.z });
	mRenderTargetCamera.SetLookAt({ mCameraLookAt });
	mRenderTargetCamera.SetAspectRatio(1.f);

	mConstantBuffer.Initialize(sizeof(Matrix4));

	std::filesystem::path shaderFile = L"../../Assets/Shaders/DoTexturing.fx";
	mVertexShader.Initialize(shaderFile, VE_Position | VE_TexCoord);
	mPixShader.Initialize(shaderFile);
	
	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
	mWorldTrans = Matrix4::Identity;

	constexpr uint32_t size = 512;
	mRenderTarget.Initialize(size, size, Texture::Format::RGBA_U32);

	mSkySphere.Initialize(500.f, 0, 0, 0);
	mSun.Initialize(7.f, 0, 0, 1);
	mMercury.Initialize(1.f, 30.f, 46.f, 0.02f);
	mVenus.Initialize(2.f, 60.f, 17.9f, 0.015f);
	mEarth.Initialize(2.5f, 90.f, 11.f, 1.f);
	mMars.Initialize(1.5f, 120.f, 5.8f, 0.5f);
	mJupiter.Initialize(4.5f, 150.f, 1.f, 45.f);
	mSaturn.Initialize(4.f, 180.f, .4f, 36.f);
	mUranus.Initialize(3.5f, 210.f, .14f, 14.f);
	mNeptune.Initialize(3.f, 240.f, 0.06f, 9.f);
	mPluto.Initialize(.5f, 270.f, 0.04f, 0.04f);

	mPlanets.push_back(&mSun);
	mPlanets.push_back(&mMercury);
	mPlanets.push_back(&mVenus);
	mPlanets.push_back(&mEarth);
	mPlanets.push_back(&mMars);
	mPlanets.push_back(&mJupiter);
	mPlanets.push_back(&mSaturn);
	mPlanets.push_back(&mUranus);
	mPlanets.push_back(&mNeptune);
	mPlanets.push_back(&mPluto);
}
void GameState::Terminate()
{
	mSkySphere.Terminate();
	mSun.Terminate();
	mMercury.Terminate();
	mVenus.Terminate();
	mEarth.Terminate();
	mMars.Terminate();
	mJupiter.Terminate();
	mSaturn.Terminate();
	mUranus.Terminate();
	mNeptune.Terminate();
	mPluto.Terminate();

	mRenderTarget.Terminate();
	mSampler.Terminate();
	mPixShader.Terminate();
	mVertexShader.Terminate();
	mConstantBuffer.Terminate();
}

void GameState::Update(float deltaTime)
{
	auto inputSystem = InputSystem::Get();

	const float moveSpeed = (inputSystem->IsKeyDown(KeyCode::LSHIFT) ? 50.f : 10.f) * deltaTime;
	const float turnSpeed = -.1f * deltaTime;

	if (inputSystem->IsKeyDown(KeyCode::W)) mCamera.Walk(moveSpeed);
	else if (inputSystem->IsKeyDown(KeyCode::S)) mCamera.Walk(-moveSpeed);
	if (inputSystem->IsKeyDown(KeyCode::D)) mCamera.Strafe(moveSpeed);
	else if (inputSystem->IsKeyDown(KeyCode::A)) mCamera.Strafe(-moveSpeed);
	if (inputSystem->IsKeyDown(KeyCode::E)) mCamera.Rise(moveSpeed);
	else if (inputSystem->IsKeyDown(KeyCode::Q)) mCamera.Rise(-moveSpeed);

	if (inputSystem->IsMouseDown(MouseButton::RBUTTON) || inputSystem->IsMouseDown(MouseButton::LBUTTON))
	{
		mCamera.Yaw(inputSystem->GetMouseMoveX() * turnSpeed);
		mCamera.Pitch(inputSystem->GetMouseMoveY() * turnSpeed);
	}
	
	for (auto& planet : mPlanets)
	{
		planet->Update(deltaTime);
	}

	for (auto& planet : mPlanets)
	{
		planet->AddSpin(mMasterSpin);
		planet->AddSpeed(mMasterSpeed);
	}
	
	mRenderTargetCamera.SetPosition(mPlanets[mCurrentSelectedPlanet]->GetPosition() + mDistanceOffSet * mPlanets[mCurrentSelectedPlanet]->GetSize());
	mRenderTargetCamera.SetLookAt(mPlanets[mCurrentSelectedPlanet]->GetPosition());
}

void GameState::Render()
{
	mVertexShader.Bind();
	mPixShader.Bind();
	mSampler.BindPS(0);
	
	mRenderTarget.BeginRender();
		RenderMesh(mRenderTargetCamera, true);
	mRenderTarget.EndRender();
	RenderMesh(mCamera, true);
}

void GameState::RenderMesh(const Camera& camera, bool useTransform)
{
	mSkySphere.Render(camera, mConstantBuffer, useTransform);

	for (auto& planet : mPlanets)
	{
		planet->Render(camera, mConstantBuffer, useTransform);
	}
}

void GameState::DebugUI()
{
	ImGui::Begin("Debug Draw", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	ImGui::DragFloat("Orbit Rotation Speed", &mMasterSpeed, 0.5);
	ImGui::DragFloat("Orbit Spin Speed", &mMasterSpin, 0.5);

	ImGui::Text("Mercury");
	mMercury.DebugUI();
	ImGui::Text("\nVenus");
	mVenus.DebugUI();
	ImGui::Text("\nEarth");
	mEarth.DebugUI();
	ImGui::Text("\nMars");
	mMars.DebugUI();
	ImGui::Text("\nJupiter");
	mJupiter.DebugUI();
	ImGui::Text("\nSaturn");
	mSaturn.DebugUI();
	ImGui::Text("\nUranus");
	mUranus.DebugUI();
	ImGui::Text("\nNeptune");
	mNeptune.DebugUI();
	ImGui::Text("\nPluto");
	mPluto.DebugUI();
	
	SimpleDraw::Render(mCamera);

	ImGui::Text("\nRender Target");
	ImGui::DragInt("Select Planet", &mCurrentSelectedPlanet, 0.04f, 0, 9);
	ImGui::Image(
		mRenderTarget.GetRawData(),
		{ 256,256 },
		{ 0,0 },
		{ 1,1 },
		{ 1,1,1,1 },
		{ 1,1,1,1 }
	);
	ImGui::End();
}
