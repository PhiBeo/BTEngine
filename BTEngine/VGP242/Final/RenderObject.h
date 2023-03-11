#pragma once
#include <BTEngine/Inc/BTEngine.h>

using namespace BTEngine;
using namespace BTEngine::Graphics;
using namespace BTEngine::BTMath;

class RenderObject
{
public:
	virtual void Initialize() {}
	virtual void Terminate() {}
	virtual void Update(float deltaTime) {}
	virtual void Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform) {}
	
	void SetPosition(const Vector3& pos) { mTransform._41 = pos.x, mTransform._42 = pos.y, mTransform._43 = pos.z; };

	virtual void DebugUI() {}
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
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform) override;
};

class Earth : public RenderObject
{
public:
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform) override;
	void DebugUI();
};

class Sun : public RenderObject
{
public:
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform) override;
};

class Jupiter : public RenderObject
{
public:
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform) override;
};

class Mars : public RenderObject
{
public:
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform) override;
};

class Mercury : public RenderObject
{
public:
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform) override;
};

class Neptune : public RenderObject
{
public:
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform) override;
};

class Pluto : public RenderObject
{
public:
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform) override;
};

class Saturn : public RenderObject
{
public:
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform) override;
};

class Uranus : public RenderObject
{
public:
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform) override;
};

class Venus : public RenderObject
{
public:
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform) override;
};