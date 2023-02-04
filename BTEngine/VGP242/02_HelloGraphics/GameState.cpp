#include "GameState.h"

using namespace BTEngine;
using namespace BTEngine::Graphics;
using namespace BTEngine::Input;

void GameState::Initialize()
{
	mVertices.push_back({ Vector3(-0.5f, 0.3f, 0.0f), Colors::Red });
	mVertices.push_back({ Vector3(-0.3f, 0.7f, 0.0f), Colors::Red });
	mVertices.push_back({ Vector3(0.0f, 0.3f, 0.0f), Colors::Red });

	mVertices.push_back({ Vector3(-0.0f, 0.3f, 0.0f), Colors::Red });
	mVertices.push_back({ Vector3(0.3f, 0.7f, 0.0f), Colors::Red });
	mVertices.push_back({ Vector3(0.5f, 0.3f, 0.0f), Colors::Red });

	mVertices.push_back({ Vector3(0.0f, -0.5f, 0.0f), Colors::Red });
	mVertices.push_back({ Vector3(-0.5f, 0.3f, 0.0f), Colors::Red });
	mVertices.push_back({ Vector3(0.5f, 0.3f, 0.0f), Colors::Red });

	auto device = GraphicsSystem::Get()->GetDevice();

	//=================================================================
	//create a vertex buffer
	D3D11_BUFFER_DESC bufferDesc{};
	bufferDesc.ByteWidth = static_cast<UINT>(mVertices.size() * sizeof(Vertex));
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initData{};
	initData.pSysMem = mVertices.data();

	HRESULT hr = device->CreateBuffer(&bufferDesc, &initData, &mVertexBuffer);
	ASSERT(SUCCEEDED(hr), "Failed to create vertex buffer");

	//=================================================================
	//create a vertex shader
	std::filesystem::path shaderFile = L"../../Assets/Shaders/DoNothing.fx";

	DWORD shaderFlag = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;
	ID3DBlob* shaderBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;
	hr = D3DCompileFromFile(
		shaderFile.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"VS", "vs_5_0",
		shaderFlag, 0,
		&shaderBlob,
		&errorBlob);
	if (errorBlob && errorBlob->GetBufferPointer())
	{
		LOG("%s", static_cast<const char*> (errorBlob->GetBufferPointer()));
	}
	ASSERT(SUCCEEDED(hr), "Failed to compile vertex shader");

	hr = device->CreateVertexShader(
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		nullptr,
		&mVertexShader);
	ASSERT(SUCCEEDED(hr), "Failed to compile vertex shader");

	//=================================================================
	//create a input layout
	std::vector<D3D11_INPUT_ELEMENT_DESC> vertexLayout;
	vertexLayout.push_back({ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT });
	vertexLayout.push_back({ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT });

	hr = device->CreateInputLayout(
		vertexLayout.data(),
		(UINT)vertexLayout.size(),
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		&mInputLayout);
	ASSERT(SUCCEEDED(hr), "Failed to create input layout");
	SafeRelease(shaderBlob);
	SafeRelease(errorBlob);

	//=================================================================
	//create a pixel shader
	hr = D3DCompileFromFile(
		shaderFile.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"PS", "ps_5_0",
		shaderFlag, 0,
		&shaderBlob,
		&errorBlob);
	if (errorBlob && errorBlob->GetBufferPointer())
	{
		LOG("%s", static_cast<const char*> (errorBlob->GetBufferPointer()));
	}
	ASSERT(SUCCEEDED(hr), "Failed to compile pixel shader");

	hr = device->CreatePixelShader(
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		nullptr,
		&mPixelShader);
	ASSERT(SUCCEEDED(hr), "Failed to compile pixel shader");
	SafeRelease(shaderBlob);
	SafeRelease(errorBlob);
}
void GameState::Terminate()
{
	SafeRelease(mVertexBuffer);
	SafeRelease(mVertexShader);
	SafeRelease(mInputLayout );
	SafeRelease(mPixelShader );
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
	auto context = GraphicsSystem::Get()->GetContext();

	context->VSSetShader(mVertexShader, nullptr, 0);
	context->IASetInputLayout(mInputLayout);
	context->PSSetShader(mPixelShader, nullptr, 0);

	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
	context->Draw((UINT)mVertices.size(), 0);
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
		mVertices.push_back({ Vector3(0.0f, 0.0f, 0.0f), Colors::Red });
		mVertices.push_back({ Vector3(-0.3f, 0.0f, 0.0f), Colors::Red });

		mVertices.push_back({ Vector3(0.0f, 0.6f, 0.0f), Colors::Red });
		mVertices.push_back({ Vector3(0.3f, 0.0f, 0.0f), Colors::Red });
		mVertices.push_back({ Vector3(0.0f, 0.0f, 0.0f), Colors::Red });

		mVertices.push_back({ Vector3(0.0f, -0.6f, 0.0f), Colors::Red });
		mVertices.push_back({ Vector3(-0.3f, 0.0f, 0.0f), Colors::Red });
		mVertices.push_back({ Vector3(0.0f, 0.0f, 0.0f), Colors::Red });

		mVertices.push_back({ Vector3(0.3f, 0.0f, 0.0f), Colors::Red });
		mVertices.push_back({ Vector3(0.0f, -0.6f, 0.0f), Colors::Red });
		mVertices.push_back({ Vector3(0.0f, 0.0f, 0.0f), Colors::Red });
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
	Terminate();
	auto device = GraphicsSystem::Get()->GetDevice();
	//=================================================================
	//create a vertex buffer
	D3D11_BUFFER_DESC bufferDesc{};
	bufferDesc.ByteWidth = static_cast<UINT>(mVertices.size() * sizeof(Vertex));
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initData{};
	initData.pSysMem = mVertices.data();

	HRESULT hr = device->CreateBuffer(&bufferDesc, &initData, &mVertexBuffer);
	ASSERT(SUCCEEDED(hr), "Failed to create vertex buffer");

	//=================================================================
	//create a vertex shader
	std::filesystem::path shaderFile = L"../../Assets/Shaders/DoNothing.fx";

	DWORD shaderFlag = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;
	ID3DBlob* shaderBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;
	hr = D3DCompileFromFile(
		shaderFile.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"VS", "vs_5_0",
		shaderFlag, 0,
		&shaderBlob,
		&errorBlob);
	if (errorBlob && errorBlob->GetBufferPointer())
	{
		LOG("%s", static_cast<const char*> (errorBlob->GetBufferPointer()));
	}
	ASSERT(SUCCEEDED(hr), "Failed to compile vertex shader");

	hr = device->CreateVertexShader(
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		nullptr,
		&mVertexShader);
	ASSERT(SUCCEEDED(hr), "Failed to compile vertex shader");

	//=================================================================
	//create a input layout
	std::vector<D3D11_INPUT_ELEMENT_DESC> vertexLayout;
	vertexLayout.push_back({ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT });
	//vertexLayout.push_back({ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT });

	hr = device->CreateInputLayout(
		vertexLayout.data(),
		(UINT)vertexLayout.size(),
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		&mInputLayout);
	ASSERT(SUCCEEDED(hr), "Failed to create input layout");
	SafeRelease(shaderBlob);
	SafeRelease(errorBlob);

	//=================================================================
	//create a pixel shader
	hr = D3DCompileFromFile(
		shaderFile.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"PS", "ps_5_0",
		shaderFlag, 0,
		&shaderBlob,
		&errorBlob);
	if (errorBlob && errorBlob->GetBufferPointer())
	{
		LOG("%s", static_cast<const char*> (errorBlob->GetBufferPointer()));
	}
	ASSERT(SUCCEEDED(hr), "Failed to compile pixel shader");

	hr = device->CreatePixelShader(
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		nullptr,
		&mPixelShader);
	ASSERT(SUCCEEDED(hr), "Failed to compile pixel shader");
	SafeRelease(shaderBlob);
	SafeRelease(errorBlob);
}

