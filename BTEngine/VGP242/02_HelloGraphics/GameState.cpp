#include "GameState.h"

using namespace BTEngine;
using namespace BTEngine::Graphics;

void GameState::Initialize()
{
	auto device = GraphicsSystem::Get()->GetDevice();


	D3D11_BUFFER_DESC bufferDesc{};
	bufferDesc.byteWidth = static_cast<UINT>(mVertices.size() * sizeof(Vertex));
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;
}
void GameState::Terminate()
{

}
void GameState::Update(float deltaTime)
{

}
void GameState::Render()
{

}