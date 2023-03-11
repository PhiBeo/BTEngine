#include "RenderObject.h"

void Earth::Initialize()
{
	MeshPX sphere = MeshBuilder::CreateSpherePX(30, 30, 3.0f);
	mMeshBuffer.Initialize(sphere);

	mDiffuseTexture.Initialize(L"../../Assets/Textures/earth.jpg");

	mTransform = Matrix4::Identity;

	mSpeed = 1;
	mDistanceFromSun = 100;
}

void Earth::Terminate()
{
	mDiffuseTexture.Terminate();
	mMeshBuffer.Terminate();
}

void Earth::Update(float deltaTime)
{
	mAngleToSun += mSpeed/10 * deltaTime;

	mPosition.x = cos(mAngleToSun) * mDistanceFromSun;
	mPosition.z = sin(mAngleToSun) * mDistanceFromSun;

	SetPosition(mPosition);
}

void Earth::Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform)
{
	mDiffuseTexture.BindPS(0);

	Matrix4 matWorld = (useTransform) ? mTransform : Matrix4::Identity;
	Matrix4 matView = camera.GetViewMatrix();
	Matrix4 matProj = camera.GetProjectionMatrix();
	Matrix4 matFinal = matWorld * matView * matProj;
	Matrix4 wvp = Transpose(matFinal);

	constantBuffer.Update(&wvp);
	constantBuffer.BindVS(0);

	mMeshBuffer.Render();
	Texture::UnbindPS(0);
}

void Earth::DebugUI()
{
	ImGui::Checkbox("Earth Orbit Line", &mOrbitLine);
	if (mOrbitLine)
	{
		SimpleDraw::AddCircle(60, 60, mDistanceFromSun, Vector3::Zero, Colors::Red);
	}
}

void SkySphere::Initialize()
{
	MeshPX skySphere = MeshBuilder::CreateSkyBoxSphere(500, 500, 500.f);
	mMeshBuffer.Initialize(skySphere);

	mDiffuseTexture.Initialize(L"../../Assets/Textures/skysphere/space.jpg");

	mTransform = Matrix4::Identity;
}

void SkySphere::Terminate()
{
	mDiffuseTexture.Terminate();
	mMeshBuffer.Terminate();
}

void SkySphere::Update(float deltaTime)
{
	return;
}

void SkySphere::Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform)
{
	mDiffuseTexture.BindPS(0);

	Matrix4 matWorld = (useTransform) ? mTransform : Matrix4::Identity;
	Matrix4 matView = camera.GetViewMatrix();
	Matrix4 matProj = camera.GetProjectionMatrix();
	Matrix4 matFinal = matWorld * matView * matProj;
	Matrix4 wvp = Transpose(matFinal);

	constantBuffer.Update(&wvp);
	constantBuffer.BindVS(0);

	mMeshBuffer.Render();
	Texture::UnbindPS(0);
}

void Sun::Initialize()
{
	MeshPX sphere = MeshBuilder::CreateSpherePX(60, 60, 10.0f);
	mMeshBuffer.Initialize(sphere);

	mDiffuseTexture.Initialize(L"../../Assets/Textures/planets/sun.jpg");

	mTransform = Matrix4::Identity;
	mSelfSpinSpeed = 5;
}

void Sun::Terminate()
{
	mDiffuseTexture.Terminate();
	mMeshBuffer.Terminate();
}

void Sun::Update(float deltaTime)
{
	mYAngle += mSelfSpinSpeed/10 * deltaTime;
	Matrix4 rotMatrix = Matrix4::RotationY(mYAngle);
	Matrix4 transMatrix = Matrix4::Translation(0.0f, 0.0f, 0.0f);
	mTransform = rotMatrix * transMatrix;

}

void Sun::Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform)
{
	mDiffuseTexture.BindPS(0);

	Matrix4 matWorld = (useTransform) ? mTransform : Matrix4::Identity;
	Matrix4 matView = camera.GetViewMatrix();
	Matrix4 matProj = camera.GetProjectionMatrix();
	Matrix4 matFinal = matWorld * matView * matProj;
	Matrix4 wvp = Transpose(matFinal);

	constantBuffer.Update(&wvp);
	constantBuffer.BindVS(0);

	mMeshBuffer.Render();
	Texture::UnbindPS(0);
}

void Jupiter::Initialize()
{
	MeshPX sphere = MeshBuilder::CreateSpherePX(30, 30, 1.0f);
	mMeshBuffer.Initialize(sphere);

	mDiffuseTexture.Initialize(L"../../Assets/Textures/planets/jupiter.jpg");

	mTransform = Matrix4::Identity;
}

void Jupiter::Terminate()
{
	mDiffuseTexture.Terminate();
	mMeshBuffer.Terminate();

}

void Jupiter::Update(float deltaTime)
{

}

void Jupiter::Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform)
{
	mDiffuseTexture.BindPS(0);

	Matrix4 matWorld = (useTransform) ? mTransform : Matrix4::Identity;
	Matrix4 matView = camera.GetViewMatrix();
	Matrix4 matProj = camera.GetProjectionMatrix();
	Matrix4 matFinal = matWorld * matView * matProj;
	Matrix4 wvp = Transpose(matFinal);

	constantBuffer.Update(&wvp);
	constantBuffer.BindVS(0);

	mMeshBuffer.Render();
	Texture::UnbindPS(0);
}

void Mars::Initialize()
{
	MeshPX sphere = MeshBuilder::CreateSpherePX(30, 30, 1.0f);
	mMeshBuffer.Initialize(sphere);

	mDiffuseTexture.Initialize(L"../../Assets/Textures/planets/mars.jpg");

	mTransform = Matrix4::Identity;
}

void Mars::Terminate()
{
	mDiffuseTexture.Terminate();
	mMeshBuffer.Terminate();
}

void Mars::Update(float deltaTime)
{
}

void Mars::Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform)
{
	mDiffuseTexture.BindPS(0);

	Matrix4 matWorld = (useTransform) ? mTransform : Matrix4::Identity;
	Matrix4 matView = camera.GetViewMatrix();
	Matrix4 matProj = camera.GetProjectionMatrix();
	Matrix4 matFinal = matWorld * matView * matProj;
	Matrix4 wvp = Transpose(matFinal);

	constantBuffer.Update(&wvp);
	constantBuffer.BindVS(0);

	mMeshBuffer.Render();
	Texture::UnbindPS(0);
}

void Mercury::Initialize()
{
	MeshPX sphere = MeshBuilder::CreateSpherePX(30, 30, 1.0f);
	mMeshBuffer.Initialize(sphere);

	mDiffuseTexture.Initialize(L"../../Assets/Textures/planets/mercury.jpg");

	mTransform = Matrix4::Identity;

	mSpeed = 1;
	mDistanceFromSun = 20;
}

void Mercury::Terminate()
{
	mDiffuseTexture.Terminate();
	mMeshBuffer.Terminate();
}

void Mercury::Update(float deltaTime)
{
	mAngleToSun += mSpeed / 10 * deltaTime;

	mPosition.x = cos(mAngleToSun) * mDistanceFromSun;
	mPosition.z = sin(mAngleToSun) * mDistanceFromSun;

	SetPosition(mPosition);
}

void Mercury::Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform)
{
	mDiffuseTexture.BindPS(0);

	Matrix4 matWorld = (useTransform) ? mTransform : Matrix4::Identity;
	Matrix4 matView = camera.GetViewMatrix();
	Matrix4 matProj = camera.GetProjectionMatrix();
	Matrix4 matFinal = matWorld * matView * matProj;
	Matrix4 wvp = Transpose(matFinal);

	constantBuffer.Update(&wvp);
	constantBuffer.BindVS(0);

	mMeshBuffer.Render();
	Texture::UnbindPS(0);
}

void Neptune::Initialize()
{
	MeshPX sphere = MeshBuilder::CreateSpherePX(30, 30, 1.0f);
	mMeshBuffer.Initialize(sphere);

	mDiffuseTexture.Initialize(L"../../Assets/Textures/planets/neptune.jpg");

	mTransform = Matrix4::Identity;
}

void Neptune::Terminate()
{
	mDiffuseTexture.Terminate();
	mMeshBuffer.Terminate();
}

void Neptune::Update(float deltaTime)
{
}

void Neptune::Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform)
{
	mDiffuseTexture.BindPS(0);

	Matrix4 matWorld = (useTransform) ? mTransform : Matrix4::Identity;
	Matrix4 matView = camera.GetViewMatrix();
	Matrix4 matProj = camera.GetProjectionMatrix();
	Matrix4 matFinal = matWorld * matView * matProj;
	Matrix4 wvp = Transpose(matFinal);

	constantBuffer.Update(&wvp);
	constantBuffer.BindVS(0);

	mMeshBuffer.Render();
	Texture::UnbindPS(0);
}

void Pluto::Initialize()
{
	MeshPX sphere = MeshBuilder::CreateSpherePX(30, 30, 1.0f);
	mMeshBuffer.Initialize(sphere);

	mDiffuseTexture.Initialize(L"../../Assets/Textures/planets/pluto.jpg");

	mTransform = Matrix4::Identity;
}

void Pluto::Terminate()
{
	mDiffuseTexture.Terminate();
	mMeshBuffer.Terminate();
}

void Pluto::Update(float deltaTime)
{
}

void Pluto::Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform)
{
	mDiffuseTexture.BindPS(0);

	Matrix4 matWorld = (useTransform) ? mTransform : Matrix4::Identity;
	Matrix4 matView = camera.GetViewMatrix();
	Matrix4 matProj = camera.GetProjectionMatrix();
	Matrix4 matFinal = matWorld * matView * matProj;
	Matrix4 wvp = Transpose(matFinal);

	constantBuffer.Update(&wvp);
	constantBuffer.BindVS(0);

	mMeshBuffer.Render();
	Texture::UnbindPS(0);
}

void Saturn::Initialize()
{
	MeshPX sphere = MeshBuilder::CreateSpherePX(30, 30, 1.0f);
	mMeshBuffer.Initialize(sphere);

	mDiffuseTexture.Initialize(L"../../Assets/Textures/planets/saturn.jpg");

	mTransform = Matrix4::Identity;
}

void Saturn::Terminate()
{
	mDiffuseTexture.Terminate();
	mMeshBuffer.Terminate();
}

void Saturn::Update(float deltaTime)
{
}

void Saturn::Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform)
{
	mDiffuseTexture.BindPS(0);

	Matrix4 matWorld = (useTransform) ? mTransform : Matrix4::Identity;
	Matrix4 matView = camera.GetViewMatrix();
	Matrix4 matProj = camera.GetProjectionMatrix();
	Matrix4 matFinal = matWorld * matView * matProj;
	Matrix4 wvp = Transpose(matFinal);

	constantBuffer.Update(&wvp);
	constantBuffer.BindVS(0);

	mMeshBuffer.Render();
	Texture::UnbindPS(0);
}

void Uranus::Initialize()
{
	MeshPX sphere = MeshBuilder::CreateSpherePX(30, 30, 1.0f);
	mMeshBuffer.Initialize(sphere);

	mDiffuseTexture.Initialize(L"../../Assets/Textures/planets/uranus.jpg");

	mTransform = Matrix4::Identity;
}

void Uranus::Terminate()
{
	mDiffuseTexture.Terminate();
	mMeshBuffer.Terminate();
}

void Uranus::Update(float deltaTime)
{
}

void Uranus::Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform)
{
	mDiffuseTexture.BindPS(0);

	Matrix4 matWorld = (useTransform) ? mTransform : Matrix4::Identity;
	Matrix4 matView = camera.GetViewMatrix();
	Matrix4 matProj = camera.GetProjectionMatrix();
	Matrix4 matFinal = matWorld * matView * matProj;
	Matrix4 wvp = Transpose(matFinal);

	constantBuffer.Update(&wvp);
	constantBuffer.BindVS(0);

	mMeshBuffer.Render();
	Texture::UnbindPS(0);
}

void Venus::Initialize()
{
	MeshPX sphere = MeshBuilder::CreateSpherePX(30, 30, 1.0f);
	mMeshBuffer.Initialize(sphere);

	mDiffuseTexture.Initialize(L"../../Assets/Textures/planets/venus.jpg");

	mTransform = Matrix4::Identity;

	mSpeed = 1;
	mDistanceFromSun = 50;
}

void Venus::Terminate()
{
	mDiffuseTexture.Terminate();
	mMeshBuffer.Terminate();
}

void Venus::Update(float deltaTime)
{
	mAngleToSun += mSpeed / 10 * deltaTime;

	mPosition.x = cos(mAngleToSun) * mDistanceFromSun;
	mPosition.z = sin(mAngleToSun) * mDistanceFromSun;

	SetPosition(mPosition);
}

void Venus::Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform)
{
	mDiffuseTexture.BindPS(0);

	Matrix4 matWorld = (useTransform) ? mTransform : Matrix4::Identity;
	Matrix4 matView = camera.GetViewMatrix();
	Matrix4 matProj = camera.GetProjectionMatrix();
	Matrix4 matFinal = matWorld * matView * matProj;
	Matrix4 wvp = Transpose(matFinal);

	constantBuffer.Update(&wvp);
	constantBuffer.BindVS(0);

	mMeshBuffer.Render();
	Texture::UnbindPS(0);
}
