#pragma once

#include "Colors.h"

namespace BTEngine::Graphics
{
	struct DirectionalLight
	{
		BTMath::Vector3 direction = BTMath::Vector3::Zero;
		float padding = 0.0f;
		Color ambient = Colors::White;
		Color diffuse = Colors::White;
		Color specular = Colors::White;
	};

	struct PointLight
	{
		BTMath::Vector3 direction = BTMath::Vector3::Zero;
		float padding0 = 0.0f;
		BTMath::Vector3 position = BTMath::Vector3::Zero;
		float padding1 = 0.0f;
		Color ambient = Colors::White;
		Color diffuse = Colors::White;
		Color specular = Colors::White;
		float attenConstant = -1.0f;
		float attenLinear = 0.0f;
		float attenQuad = 0.0f;
		float padding2 = 0.0f;
	};
}