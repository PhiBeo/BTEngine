#pragma once
#include "Colors.h"

using namespace BTEngine::BTMath;

namespace BTEngine::Graphics
{
	class Camera;

	namespace SimpleDraw
	{
		void staticInitialize(uint32_t maxVertexCount);
		void staticTerminate();

		void AddLine(const Vector3& v0, const Vector3& v1, const Color& color);
		void AddFace(const Vector3& v0, const Vector3& v1, const Vector3& v2, const Color& color);

		void AddAABB(const Vector3& min, const Vector3& max, const Vector3& pos,const Color& color);
		void AddAABB(float minX, float maxX, float minY, float maxY, float minZ, float maxZ, const Vector3& pos,const Color& color);

		void AddFilledAABB(const Vector3& min, const Vector3& max, const Vector3& pos, const Color& color);
		void AddFilledAABB(float minX, float maxX, float minY, float maxY, float minZ, float maxZ, const Vector3& pos, const Color& color);

		void AddSphere(int slices, int rings, float radius, const Vector3& pos, const Color& color);
		
		void AddGroundPlane(float size, const Color& color);

		void AddTransform(const Matrix4& m);

		void Render(const Camera& camera);
	}
}