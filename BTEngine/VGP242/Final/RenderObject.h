#pragma once
#include <BTEngine/Inc/BTEngine.h>

using namespace BTEngine;
using namespace BTEngine::Graphics;
using namespace BTEngine::BTMath;

class RenderObject
{
public:
	virtual void Initialize(const float& size, const float& distance, const float& moveSpeed, const float& spinSpeed) {}
	virtual void Terminate() {}
	virtual void Update(float deltaTime) {}
	virtual void Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform) {}
	virtual void DebugUI() {}

	void SetPosition(const Vector3& pos) { mTransform._41 = pos.x, mTransform._42 = pos.y, mTransform._43 = pos.z; };
	void SetSpeed(const float& speed) { mSpeed = speed; };
	void SetDistanceFromSun(const float& distance) { mDistanceFromSun = distance; };
	void SetSelfSpinSpeed(const float& speed) { mSelfSpinSpeed = speed; };

protected:

	MeshBuffer mMeshBuffer;
	Texture mDiffuseTexture;
	Matrix4 mTransform;

	float mSpeed = 0;
	Vector3 mPosition = Vector3::Zero;
	float mDistanceFromSun = 0;
	float mAngleToSun = 0;
	bool mOrbitLine = true;

	float mSelfSpinSpeed = 0;
	float mYAngle = 0;
};

class SkySphere : public RenderObject
{
public:
	void Initialize(const float& size, const float& distance, const float& moveSpeed, const float& spinSpeed) override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform) override;
};

class Earth : public RenderObject
{
public:
	void Initialize(const float& size, const float& distance, const float& moveSpeed, const float& spinSpeed) override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform) override;
	void DebugUI() override;
};

class Sun : public RenderObject
{
public:
	void Initialize(const float& size, const float& distance, const float& moveSpeed, const float& spinSpeed) override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform) override;
};

class Jupiter : public RenderObject
{
public:
	void Initialize(const float& size, const float& distance, const float& moveSpeed, const float& spinSpeed) override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform) override;
	void DebugUI() override;
};

class Mars : public RenderObject
{
public:
	void Initialize(const float& size, const float& distance, const float& moveSpeed, const float& spinSpeed) override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform) override;
	void DebugUI() override;
};

class Mercury : public RenderObject
{
public:
	void Initialize(const float& size, const float& distance, const float& moveSpeed, const float& spinSpeed) override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform) override;
	void DebugUI() override;
};

class Neptune : public RenderObject
{
public:
	void Initialize(const float& size, const float& distance, const float& moveSpeed, const float& spinSpeed) override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform) override;
	void DebugUI() override;
};

class Pluto : public RenderObject
{
public:
	void Initialize(const float& size, const float& distance, const float& moveSpeed, const float& spinSpeed) override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform) override;
	void DebugUI() override;
};

class Saturn : public RenderObject
{
public:
	void Initialize(const float& size, const float& distance, const float& moveSpeed, const float& spinSpeed) override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform) override;
	void DebugUI() override;
};

class Uranus : public RenderObject
{
public:
	void Initialize(const float& size, const float& distance, const float& moveSpeed, const float& spinSpeed) override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform) override;
	void DebugUI() override;
};

class Venus : public RenderObject
{
public:
	void Initialize(const float& size, const float& distance, const float& moveSpeed, const float& spinSpeed) override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform) override;
	void DebugUI() override;
};