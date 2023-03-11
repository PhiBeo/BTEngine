#include "GameState.h"

using namespace BTEngine;
using namespace BTEngine::Graphics;
using namespace BTEngine::Input;

void GameState::Initialize()
{

	mCamera.SetPosition({ 0.f,1.f,-3.f });
	mCamera.SetLookAt({ 0.f,0.f,0.f });

	mConstantBuffer.Initialize(sizeof(Matrix4));

	MeshPX skybox = MeshBuilder::CreateSkyBox(30.f);
	mMeshBuffer.Initialize(skybox);

	std::filesystem::path shaderFile = L"../../Assets/Shaders/DoTexturing.fx";

	mVertexShader.Initialize(shaderFile, VE_Position | VE_TexCoord);
	mPixShader.Initialize(shaderFile);
	
	mDiffuseTexture.Initialize(L"../../Assets/Textures/Images/skybox/skybox_texture.jpg");
	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
}
void GameState::Terminate()
{
	mSampler.Terminate();
	mDiffuseTexture.Terminate();
	mPixShader.Terminate();
	mVertexShader.Terminate();
	mMeshBuffer.Terminate();
	mConstantBuffer.Terminate();
}

float gRotationY = 0.f;
float gRotationX = 0.f;
void GameState::Update(float deltaTime)
{
	auto inputSystem = InputSystem::Get();
	if (inputSystem->IsKeyDown(KeyCode::S))
	{
		gRotationX -= BTMath::Constants::HalfPi * deltaTime * .5f;
	}
	if (inputSystem->IsKeyDown(KeyCode::W))
	{
		gRotationX += BTMath::Constants::HalfPi * deltaTime * .5f;
	}
	if (inputSystem->IsKeyDown(KeyCode::D))
	{
		gRotationY += BTMath::Constants::HalfPi * deltaTime * .5f;
	}
	if (inputSystem->IsKeyDown(KeyCode::A))
	{
		gRotationY -= BTMath::Constants::HalfPi * deltaTime * .5f;
	}
}

void GameState::Render()
{
	mVertexShader.Bind();
	mPixShader.Bind();

	mDiffuseTexture.BindPS(0);
	mSampler.BindPS(0);

	Matrix4 matWorldY = Matrix4::RotationY(gRotationY);
	Matrix4 matWorldX = Matrix4::RotationX(gRotationX);
	Matrix4 matView = mCamera.GetViewMatrix();
	Matrix4 matProj = mCamera.GetProjectionMatrix();
	Matrix4 wvp = Transpose(matWorldX * matWorldY * matView * matProj);

	mConstantBuffer.Update(&wvp);
	mConstantBuffer.BindVS(0);


	mMeshBuffer.Render();
}
