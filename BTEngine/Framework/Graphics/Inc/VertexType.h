#pragma once

#include "Common.h"
#include "Colors.h"

namespace BTEngine::Graphics
{
	constexpr uint32_t VE_Position		= 0x1 << 0;
	constexpr uint32_t VE_Normal		= 0x1 << 1;
	constexpr uint32_t VE_Tangent		= 0x1 << 2;
	constexpr uint32_t VE_Color			= 0x1 << 3;
	constexpr uint32_t VE_TexCoord		= 0x1 << 4;
	constexpr uint32_t VE_BlendIndex	= 0x1 << 5;
	constexpr uint32_t VE_BlendWeight	= 0x1 << 6;

	#define VERTEX_FORMAT(fmt)\
		static constexpr uint32_t Format = fmt

	struct VertexP
	{
		VERTEX_FORMAT(VE_Position);
		BTMath::Vector3 position;
	};

	struct VertexPC
	{
		VERTEX_FORMAT(VE_Position);
		BTMath::Vector3 position;
		Color color;
	};

	struct VertexPX
	{
		VERTEX_FORMAT(VE_Position | VE_TexCoord);
		BTMath::Vector3 position;
		BTMath::Vector2 uvCoord;
	};

	struct Vertex
	{
		VERTEX_FORMAT(VE_Position | VE_Normal | VE_Tangent | VE_TexCoord);
		BTMath::Vector3 position;
		BTMath::Vector3 normal;
		BTMath::Vector3 tangent;
		BTMath::Vector2 uvCoord;
	};
}