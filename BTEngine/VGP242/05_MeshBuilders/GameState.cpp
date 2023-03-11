#include "GameState.h"

using namespace BTEngine;
using namespace BTEngine::Graphics;
using namespace BTEngine::Input;

void GameState::Initialize()
{

	mCamera.SetPosition({ 0.f,1.f,-3.f });
	mCamera.SetLookAt({ 0.f,0.f,0.f });

	StartMesh();

	mConstantBuffer.Initialize(sizeof(Matrix4));

	std::filesystem::path shaderFile = L"../../Assets/Shaders/DoTransform.fx";

	mVertexShader.Initialize(shaderFile, VE_Position | VE_Color);
	mPixShader.Initialize(shaderFile);
	
}
void GameState::Terminate()
{
	mVertices.clear();
	mVertexShader.Terminate();
	mPixShader.Terminate();
	mMeshBuffer.Terminate();
	mConstantBuffer.Terminate();
}

float gRotationY = 0.f;
float gRotationX = 0.f;
void GameState::Update(float deltaTime)
{
	auto inputSystem = InputSystem::Get();
	if (inputSystem->IsKeyPressed(KeyCode::D))
	{
		App& myApp = MainApp();
		myApp.ChangeState("RectState");
	}

	gRotationY += BTMath::Constants::HalfPi * deltaTime * .5f;
	gRotationX += BTMath::Constants::HalfPi * deltaTime * .25f;
}

void GameState::Render()
{
	mVertexShader.Bind();
	mPixShader.Bind();

	Matrix4 matWorldY = Matrix4::RotationY(gRotationY);
	Matrix4 matWorldX = Matrix4::RotationX(gRotationX);
	Matrix4 matView = mCamera.GetViewMatrix();
	Matrix4 matProj = mCamera.GetProjectionMatrix();
	Matrix4 wvp = Transpose(matWorldX * matWorldY * matView * matProj);

	mConstantBuffer.Update(&wvp);
	mConstantBuffer.BindVS(0);


	mMeshBuffer.Render();
}

void GameState::DebugUI()
{

}

void GameState::Refresh()
{
	//Terminate();

	mMeshBuffer.Initialize(mVertices.data(), sizeof(Vertex), mVertices.size());

	std::filesystem::path shaderFile = L"../../Assets/Shaders/DoSomething.fx";

	mVertexShader.Initialize(shaderFile, VE_Position | VE_Color);
	mPixShader.Initialize(shaderFile);
}

void GameState::StartMesh()
{
	MeshPC sphere = MeshBuilder::CreateSpherePC(5, 4,8);

	mMeshBuffer.Initialize(sphere);
}

void RectState::DrawMesh()
{
	MeshPX Rect = MeshBuilder::CreateRectPX(5, 3, 2);

	mMeshBuffer.Initialize(Rect);
}

void RectState::Update(float deltaTime)
{
	auto inputSystem = InputSystem::Get();
	if (inputSystem->IsKeyPressed(KeyCode::RIGHT))
	{
		App& myApp = MainApp();
		myApp.ChangeState("GameState");
	}

	gRotationY += BTMath::Constants::HalfPi * deltaTime * .5f;
	gRotationX += BTMath::Constants::HalfPi * deltaTime * .25f;
}
