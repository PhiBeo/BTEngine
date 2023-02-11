#include "Precompiled.h"
#include "PixShader.h"
#include "GraphicsSystem.h"

using namespace BTEngine;
using namespace BTEngine::Graphics;

void PixShader::Initialize(const std::filesystem::path& filePath)
{
	auto device = GraphicsSystem::Get()->GetDevice();

	DWORD shaderFlag = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;
	ID3DBlob* shaderBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;


	//=================================================================
	//create a pixel shader
	HRESULT hr = D3DCompileFromFile(
		filePath.c_str(),
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

void PixShader::Terminate()
{
	SafeRelease(mPixelShader);
}

void PixShader::Bind()
{
	auto context = GraphicsSystem::Get()->GetContext();

	context->PSSetShader(mPixelShader, nullptr, 0);
}
