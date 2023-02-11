#include "GameState.h"

using namespace BTEngine;
using namespace BTEngine::Graphics;
using namespace BTEngine::Input;

void GameState::Initialize()
{
	SwitchPicture(pictureAt);
	mCamera.SetPosition({ 0.f,1.f,-1.f });
	mCamera.SetLookAt({ 0.f,0.f,0.f });

	mMeshBuffer.Initialize(mVertices.data(), sizeof(Vertex), mVertices.size());

	std::filesystem::path shaderFile = L"../../Assets/Shaders/DoSomething.fx";

	mVertexShader.Initialize(shaderFile, VE_Position | VE_Color);
	mPixShader.Initialize(shaderFile);
	
}
void GameState::Terminate()
{
	mVertices.clear();
	mVertexShader.Terminate();
	mPixShader.Terminate();
	mMeshBuffer.Terminate();
}
void GameState::Update(float deltaTime)
{
	auto inputSystem = InputSystem::Get();
	if (inputSystem->IsKeyPressed(KeyCode::RIGHT) && pictureAt < 2)
	{
		pictureAt++;
		SwitchPicture(pictureAt);
		Refresh();
	}
	else if (inputSystem->IsKeyPressed(KeyCode::LEFT) && pictureAt > 0)
	{
		pictureAt--;
		SwitchPicture(pictureAt);
		Refresh();
	}
}
void GameState::Render()
{
	mVertexShader.Bind();
	mPixShader.Bind();

	Matrix4 matWorld = Matrix4::Identity;
	Matrix4 matView = mCamera.GetViewMatrix();
	Matrix4 matProj = mCamera.GetProjectionMatrix();
	Matrix4 matFinal = matWorld * matView * matProj;

	mMeshBuffer.Render();
}

void GameState::DebugUI()
{

}

void GameState::SwitchPicture(int pictureNum)
{
	mVertices.clear();

	switch (pictureAt)
	{
	case 0:
		mVertices.push_back({ Vector3(-0.5f, 0.3f, 0.0f), Colors::Red });
		mVertices.push_back({ Vector3(-0.3f, 0.7f, 0.0f), Colors::Red });
		mVertices.push_back({ Vector3(0.0f, 0.3f, 0.0f), Colors::Red });

		mVertices.push_back({ Vector3(-0.0f, 0.3f, 0.0f), Colors::Red });
		mVertices.push_back({ Vector3(0.3f, 0.7f, 0.0f), Colors::Red });
		mVertices.push_back({ Vector3(0.5f, 0.3f, 0.0f), Colors::Red });

		mVertices.push_back({ Vector3(0.0f, -0.5f, 0.0f), Colors::Red });
		mVertices.push_back({ Vector3(-0.5f, 0.3f, 0.0f), Colors::Red });
		mVertices.push_back({ Vector3(0.5f, 0.3f, 0.0f), Colors::Red });
		break;
	case 1:
		mVertices.push_back({ Vector3(0.0f, 0.6f, 0.0f), Colors::Red });
		mVertices.push_back({ Vector3(0.0f, 0.0f, 0.0f), Colors::Cyan });
		mVertices.push_back({ Vector3(-0.3f, 0.0f, 0.0f), Colors::Yellow });

		mVertices.push_back({ Vector3(0.0f, 0.6f, 0.0f), Colors::Aqua });
		mVertices.push_back({ Vector3(0.3f, 0.0f, 0.0f), Colors::DarkGreen });
		mVertices.push_back({ Vector3(0.0f, 0.0f, 0.0f), Colors::LightSalmon });

		mVertices.push_back({ Vector3(0.0f, -0.6f, 0.0f), Colors::Magenta });
		mVertices.push_back({ Vector3(-0.3f, 0.0f, 0.0f), Colors::DarkSalmon });
		mVertices.push_back({ Vector3(0.0f, 0.0f, 0.0f), Colors::HotPink });

		mVertices.push_back({ Vector3(0.3f, 0.0f, 0.0f), Colors::AliceBlue });
		mVertices.push_back({ Vector3(0.0f, -0.6f, 0.0f), Colors::DarkOrchid });
		mVertices.push_back({ Vector3(0.0f, 0.0f, 0.0f), Colors::PaleTurquoise });
		break;
	case 2:
		mVertices.push_back({ Vector3(0.0f, -0.3f, 0.0f), Colors::Red });
		mVertices.push_back({ Vector3(0.15f, 0.0f, 0.0f), Colors::Red });
		mVertices.push_back({ Vector3(0.3f, -0.3f, 0.0f), Colors::Red });

		mVertices.push_back({ Vector3(0.0f, -0.3f, 0.0f), Colors::Red });
		mVertices.push_back({ Vector3(-0.3f, -0.3f, 0.0f), Colors::Red });
		mVertices.push_back({ Vector3(-0.15f, 0.0f, 0.0f), Colors::Red });

		mVertices.push_back({ Vector3(-0.15f, 0.0f, 0.0f), Colors::Red });
		mVertices.push_back({ Vector3(0.0f, 0.3f, 0.0f), Colors::Red });
		mVertices.push_back({ Vector3(0.15f, 0.0f, 0.0f), Colors::Red });
		
		break;
	default:
		break;
	}
}

void GameState::Refresh()
{
	//Terminate();

	mMeshBuffer.Initialize(mVertices.data(), sizeof(Vertex), mVertices.size());

	std::filesystem::path shaderFile = L"../../Assets/Shaders/DoSomething.fx";

	mVertexShader.Initialize(shaderFile, VE_Position | VE_Color);
	mPixShader.Initialize(shaderFile);
}

