#include "RenderObject.h"

void Earth::Initialize(const float& size, const float& distance, const float& moveSpeed, const float& spinSpeed)
{
	MeshPX sphere = MeshBuilder::CreateSpherePX(30, 30, size);
	mMeshBuffer.Initialize(sphere);

	mDiffuseTexture.Initialize(L"../../Assets/Textures/earth.jpg");

	mTransform = Matrix4::Identity;
	mSpeed = moveSpeed;
	mDistanceFromSun = distance;
	mSelfSpinSpeed = spinSpeed;
}

void Earth::Terminate()
{
	mDiffuseTexture.Terminate();
	mMeshBuffer.Terminate();
}

void Earth::Update(float deltaTime)
{
	//spining itself
	mYAngle += mSelfSpinSpeed / 10 * deltaTime;
	Matrix4 rotMatrix = Matrix4::RotationY(mYAngle);
	Matrix4 transMatrix = Matrix4::Translation(0.0f, 0.0f, 0.0f);
	mTransform = rotMatrix * transMatrix;

	//rotate around the sun calculation
	mAngleToSun += mSpeed / 10 * deltaTime;

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
	ImGui::DragFloat("Earth Rotating Speed", &mSpeed);
	ImGui::DragFloat("Earth Spinning Speed", &mSelfSpinSpeed);
}

void SkySphere::Initialize(const float& size, const float& distance, const float& moveSpeed, const float& spinSpeed)
{
	MeshPX skySphere = MeshBuilder::CreateSkyBoxSphere(500, 500, size);
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

void Sun::Initialize(const float& size, const float& distance, const float& moveSpeed, const float& spinSpeed)
{
	MeshPX sphere = MeshBuilder::CreateSpherePX(60, 60, size);
	mMeshBuffer.Initialize(sphere);

	mDiffuseTexture.Initialize(L"../../Assets/Textures/planets/sun.jpg");

	mTransform = Matrix4::Identity;
	mSpeed = moveSpeed;
	mDistanceFromSun = distance;
	mSelfSpinSpeed = spinSpeed;
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

void Jupiter::Initialize(const float& size, const float& distance, const float& moveSpeed, const float& spinSpeed)
{
	MeshPX sphere = MeshBuilder::CreateSpherePX(30, 30, size);
	mMeshBuffer.Initialize(sphere);

	mDiffuseTexture.Initialize(L"../../Assets/Textures/planets/jupiter.jpg");

	mTransform = Matrix4::Identity;
	mSpeed = moveSpeed;
	mDistanceFromSun = distance;
	mSelfSpinSpeed = spinSpeed;
}

void Jupiter::Terminate()
{
	mDiffuseTexture.Terminate();
	mMeshBuffer.Terminate();

}

void Jupiter::Update(float deltaTime)
{
	//spining itself
	mYAngle += mSelfSpinSpeed / 10 * deltaTime;
	Matrix4 rotMatrix = Matrix4::RotationY(mYAngle);
	Matrix4 transMatrix = Matrix4::Translation(0.0f, 0.0f, 0.0f);
	mTransform = rotMatrix * transMatrix;

	//rotate around the sun calculation
	mAngleToSun += mSpeed / 10 * deltaTime;

	mPosition.x = cos(mAngleToSun) * mDistanceFromSun;
	mPosition.z = sin(mAngleToSun) * mDistanceFromSun;

	SetPosition(mPosition);
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

void Jupiter::DebugUI()
{
	ImGui::Checkbox("Jupiter Orbit Line", &mOrbitLine);
	if (mOrbitLine)
	{
		SimpleDraw::AddCircle(60, 60, mDistanceFromSun, Vector3::Zero, Colors::Red);
	}
	ImGui::DragFloat("Jupiter Rotating Speed", &mSpeed);
	ImGui::DragFloat("Jupiter Spinning Speed", &mSelfSpinSpeed);
}

void Mars::Initialize(const float& size, const float& distance, const float& moveSpeed, const float& spinSpeed)
{
	MeshPX sphere = MeshBuilder::CreateSpherePX(30, 30, size);
	mMeshBuffer.Initialize(sphere);

	mDiffuseTexture.Initialize(L"../../Assets/Textures/planets/mars.jpg");

	mTransform = Matrix4::Identity;
	mSpeed = moveSpeed;
	mDistanceFromSun = distance;
	mSelfSpinSpeed = spinSpeed;
}

void Mars::Terminate()
{
	mDiffuseTexture.Terminate();
	mMeshBuffer.Terminate();
}

void Mars::Update(float deltaTime)
{
	//spining itself
	mYAngle += mSelfSpinSpeed / 10 * deltaTime;
	Matrix4 rotMatrix = Matrix4::RotationY(mYAngle);
	Matrix4 transMatrix = Matrix4::Translation(0.0f, 0.0f, 0.0f);
	mTransform = rotMatrix * transMatrix;

	//rotate around the sun calculation
	mAngleToSun += mSpeed / 10 * deltaTime;

	mPosition.x = cos(mAngleToSun) * mDistanceFromSun;
	mPosition.z = sin(mAngleToSun) * mDistanceFromSun;

	SetPosition(mPosition);
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

void Mars::DebugUI()
{
	ImGui::Checkbox("Mars Orbit Line", &mOrbitLine);
	if (mOrbitLine)
	{
		SimpleDraw::AddCircle(60, 60, mDistanceFromSun, Vector3::Zero, Colors::Red);
	}
	ImGui::DragFloat("Mars Rotating Speed", &mSpeed);
	ImGui::DragFloat("Mars Spinning Speed", &mSelfSpinSpeed);
}

void Mercury::Initialize(const float& size, const float& distance, const float& moveSpeed, const float& spinSpeed)
{
	MeshPX sphere = MeshBuilder::CreateSpherePX(30, 30, size);
	mMeshBuffer.Initialize(sphere);

	mDiffuseTexture.Initialize(L"../../Assets/Textures/planets/mercury.jpg");

	mTransform = Matrix4::Identity;
	mSpeed = moveSpeed;
	mDistanceFromSun = distance;
	mSelfSpinSpeed = spinSpeed;
}

void Mercury::Terminate()
{
	mDiffuseTexture.Terminate();
	mMeshBuffer.Terminate();
}

void Mercury::Update(float deltaTime)
{
	//spining itself
	mYAngle += mSelfSpinSpeed / 10 * deltaTime;
	Matrix4 rotMatrix = Matrix4::RotationY(mYAngle);
	Matrix4 transMatrix = Matrix4::Translation(0.0f, 0.0f, 0.0f);
	mTransform = rotMatrix * transMatrix;

	//rotate around the sun calculation
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

void Mercury::DebugUI()
{
	ImGui::Checkbox("Mercury Orbit Line", &mOrbitLine);
	if (mOrbitLine)
	{
		SimpleDraw::AddCircle(60, 60, mDistanceFromSun, Vector3::Zero, Colors::Red);
	}
	ImGui::DragFloat("Mercury Rotating Speed", &mSpeed);
	ImGui::DragFloat("Mercury Spinning Speed", &mSelfSpinSpeed);
}

void Neptune::Initialize(const float& size, const float& distance, const float& moveSpeed, const float& spinSpeed)
{
	MeshPX sphere = MeshBuilder::CreateSpherePX(30, 30, size);
	mMeshBuffer.Initialize(sphere);

	mDiffuseTexture.Initialize(L"../../Assets/Textures/planets/neptune.jpg");

	mTransform = Matrix4::Identity;
	mSpeed = moveSpeed;
	mDistanceFromSun = distance;
	mSelfSpinSpeed = spinSpeed;
}

void Neptune::Terminate()
{
	mDiffuseTexture.Terminate();
	mMeshBuffer.Terminate();
}

void Neptune::Update(float deltaTime)
{
	//spining itself
	mYAngle += mSelfSpinSpeed / 10 * deltaTime;
	Matrix4 rotMatrix = Matrix4::RotationY(mYAngle);
	Matrix4 transMatrix = Matrix4::Translation(0.0f, 0.0f, 0.0f);
	mTransform = rotMatrix * transMatrix;

	//rotate around the sun calculation
	mAngleToSun += mSpeed / 10 * deltaTime;

	mPosition.x = cos(mAngleToSun) * mDistanceFromSun;
	mPosition.z = sin(mAngleToSun) * mDistanceFromSun;

	SetPosition(mPosition);
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

void Neptune::DebugUI()
{
	ImGui::Checkbox("Neptune Orbit Line", &mOrbitLine);
	if (mOrbitLine)
	{
		SimpleDraw::AddCircle(60, 60, mDistanceFromSun, Vector3::Zero, Colors::Red);
	}
	ImGui::DragFloat("Neptune Rotating Speed", &mSpeed);
	ImGui::DragFloat("Neptune Spinning Speed", &mSelfSpinSpeed);
}

void Pluto::Initialize(const float& size, const float& distance, const float& moveSpeed, const float& spinSpeed)
{
	MeshPX sphere = MeshBuilder::CreateSpherePX(30, 30, size);
	mMeshBuffer.Initialize(sphere);

	mDiffuseTexture.Initialize(L"../../Assets/Textures/planets/pluto.jpg");

	mTransform = Matrix4::Identity;
	mSpeed = moveSpeed;
	mDistanceFromSun = distance;
	mSelfSpinSpeed = spinSpeed;
}

void Pluto::Terminate()
{
	mDiffuseTexture.Terminate();
	mMeshBuffer.Terminate();
}

void Pluto::Update(float deltaTime)
{
	//spining itself
	mYAngle += mSelfSpinSpeed / 10 * deltaTime;
	Matrix4 rotMatrix = Matrix4::RotationY(mYAngle);
	Matrix4 transMatrix = Matrix4::Translation(0.0f, 0.0f, 0.0f);
	mTransform = rotMatrix * transMatrix;

	//rotate around the sun calculation
	mAngleToSun += mSpeed / 10 * deltaTime;

	mPosition.x = cos(mAngleToSun) * mDistanceFromSun;
	mPosition.z = sin(mAngleToSun) * mDistanceFromSun;

	SetPosition(mPosition);
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

void Pluto::DebugUI()
{
	ImGui::Checkbox("Pluto Orbit Line", &mOrbitLine);
	if (mOrbitLine)
	{
		SimpleDraw::AddCircle(60, 60, mDistanceFromSun, Vector3::Zero, Colors::Red);
	}
	ImGui::DragFloat("Pluto Rotating Speed", &mSpeed);
	ImGui::DragFloat("Pluto Spinning Speed", &mSelfSpinSpeed);
}

void Saturn::Initialize(const float& size, const float& distance, const float& moveSpeed, const float& spinSpeed)
{
	MeshPX sphere = MeshBuilder::CreateSpherePX(30, 30, size);
	mMeshBuffer.Initialize(sphere);

	mDiffuseTexture.Initialize(L"../../Assets/Textures/planets/saturn.jpg");

	mTransform = Matrix4::Identity;
	mSpeed = moveSpeed;
	mDistanceFromSun = distance;
	mSelfSpinSpeed = spinSpeed;
}

void Saturn::Terminate()
{
	mDiffuseTexture.Terminate();
	mMeshBuffer.Terminate();
}

void Saturn::Update(float deltaTime)
{
	//spining itself
	mYAngle += mSelfSpinSpeed / 10 * deltaTime;
	Matrix4 rotMatrix = Matrix4::RotationY(mYAngle);
	Matrix4 transMatrix = Matrix4::Translation(0.0f, 0.0f, 0.0f);
	mTransform = rotMatrix * transMatrix;

	//rotate around the sun calculation
	mAngleToSun += mSpeed / 10 * deltaTime;

	mPosition.x = cos(mAngleToSun) * mDistanceFromSun;
	mPosition.z = sin(mAngleToSun) * mDistanceFromSun;

	SetPosition(mPosition);
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

void Saturn::DebugUI()
{
	ImGui::Checkbox("Saturn Orbit Line", &mOrbitLine);
	if (mOrbitLine)
	{
		SimpleDraw::AddCircle(60, 60, mDistanceFromSun, Vector3::Zero, Colors::Red);
	}
	ImGui::DragFloat("Saturn Rotating Speed", &mSpeed);
	ImGui::DragFloat("Saturn Spinning Speed", &mSelfSpinSpeed);
}

void Uranus::Initialize(const float& size, const float& distance, const float& moveSpeed, const float& spinSpeed)
{
	MeshPX sphere = MeshBuilder::CreateSpherePX(30, 30, size);
	mMeshBuffer.Initialize(sphere);

	mDiffuseTexture.Initialize(L"../../Assets/Textures/planets/uranus.jpg");

	mTransform = Matrix4::Identity;
	mSpeed = moveSpeed;
	mDistanceFromSun = distance;
	mSelfSpinSpeed = spinSpeed;
}

void Uranus::Terminate()
{
	mDiffuseTexture.Terminate();
	mMeshBuffer.Terminate();
}

void Uranus::Update(float deltaTime)
{
	//spining itself
	mYAngle += mSelfSpinSpeed / 10 * deltaTime;
	Matrix4 rotMatrix = Matrix4::RotationY(mYAngle);
	Matrix4 transMatrix = Matrix4::Translation(0.0f, 0.0f, 0.0f);
	mTransform = rotMatrix * transMatrix;

	//rotate around the sun calculation
	mAngleToSun += mSpeed / 10 * deltaTime;

	mPosition.x = cos(mAngleToSun) * mDistanceFromSun;
	mPosition.z = sin(mAngleToSun) * mDistanceFromSun;

	SetPosition(mPosition);
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

void Uranus::DebugUI()
{
	ImGui::Checkbox("Uranus Orbit Line", &mOrbitLine);
	if (mOrbitLine)
	{
		SimpleDraw::AddCircle(60, 60, mDistanceFromSun, Vector3::Zero, Colors::Red);
	}
	ImGui::DragFloat("Uranus Rotating Speed", &mSpeed);
	ImGui::DragFloat("Uranus Spinning Speed", &mSelfSpinSpeed);
}

void Venus::Initialize(const float& size, const float& distance, const float& moveSpeed, const float& spinSpeed)
{
	MeshPX sphere = MeshBuilder::CreateSpherePX(30, 30, size);
	mMeshBuffer.Initialize(sphere);

	mDiffuseTexture.Initialize(L"../../Assets/Textures/planets/venus.jpg");

	mTransform = Matrix4::Identity;
	mSpeed = moveSpeed;
	mDistanceFromSun = distance;
	mSelfSpinSpeed = spinSpeed;
}

void Venus::Terminate()
{
	mDiffuseTexture.Terminate();
	mMeshBuffer.Terminate();
}

void Venus::Update(float deltaTime)
{
	//spining itself
	mYAngle += mSelfSpinSpeed / 10 * deltaTime;
	Matrix4 rotMatrix = Matrix4::RotationY(mYAngle);
	Matrix4 transMatrix = Matrix4::Translation(0.0f, 0.0f, 0.0f);
	mTransform = rotMatrix * transMatrix;

	//rotate around the sun calculation
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

void Venus::DebugUI()
{
	ImGui::Checkbox("Venus Orbit Line", &mOrbitLine);
	if (mOrbitLine)
	{
		SimpleDraw::AddCircle(60, 60, mDistanceFromSun, Vector3::Zero, Colors::Red);
	}
	ImGui::DragFloat("Venus Rotating Speed", &mSpeed);
	ImGui::DragFloat("Venus Spinning Speed", &mSelfSpinSpeed);
}
