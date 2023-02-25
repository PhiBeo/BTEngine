#include "Precompiled.h"
#include "MeshBuilder.h"

using namespace BTEngine;
using namespace BTEngine::Graphics;

namespace
{
	Color GetNextColor(int& index)
	{
		constexpr Color colorTable[] = {
			Colors::DarkMagenta,
			Colors::AliceBlue,
			Colors::DarkBlue,
			Colors::Khaki,
			Colors::Green,
			Colors::Red,
			Colors::Yellow,
			Colors::LightPink
		};

		index = (index + 1) % std::size(colorTable);
		return colorTable[index];
	};

	void CreateCubeIndices(std::vector<uint32_t>& indices)
	{
		indices = {
			//front
			0,1,2,
			0,2,3,

			//back
			7, 6, 5,
			7, 5, 4,

			//right
			3, 2, 6,
			3, 6, 7,

			//left
			0, 5, 1,
			0, 4, 5,

			//top
			1, 5, 6,
			1, 6, 2,

			//bottom
			0, 3, 7,
			0, 7, 4
		};
	}

	void CreatePlaneIndices(std::vector<uint32_t>& indices, int numRows, int numCols)
	{
		for (int r = 0; r <= numRows; ++r)
		{
			for (int c = 0; c < numCols; ++c)
			{
				int i = (r * numCols)  + c;

				//triangle 1
				indices.push_back(i);
				indices.push_back(i + numCols + 1);
				indices.push_back(i + 1);

				//triangle 2
				indices.push_back(i);
				indices.push_back(i + numCols);
				indices.push_back(i + numCols + 1);
			}
		}
	};

	void CreateCapIndices(std::vector<uint32_t>& indices, int slices, int topIndex, int bottomIndex)
	{
		for (int s = 0; s < slices; ++s)
		{
			//bottom
			indices.push_back(s);
			indices.push_back(s + 1);
			indices.push_back(bottomIndex);

			//top
			int topRowIndex = topIndex - slices - 1 + s;
			indices.push_back(topIndex);
			indices.push_back(topRowIndex + 1);
			indices.push_back(topRowIndex);
			
		}
	};
};

MeshPC MeshBuilder::CreateCubePC(float size, const Color& color)
{
	MeshPC mesh;

	const float hs = size * .5f;

	//front
	mesh.vertices.push_back({ {-hs, -hs, -hs}, color });	//0 FBL
	mesh.vertices.push_back({ {-hs, hs, -hs}, color });		//1 FTL
	mesh.vertices.push_back({ {hs, hs, -hs}, color });		//2 FTR
	mesh.vertices.push_back({ {hs, -hs, -hs}, color });		//3 FBR
	
	//back
	mesh.vertices.push_back({ {-hs, -hs, hs}, color });		//4 BBL
	mesh.vertices.push_back({ {-hs, hs, hs}, color });		//5 BTL
	mesh.vertices.push_back({ {hs, hs, hs}, color });		//6 BTR
	mesh.vertices.push_back({ {hs, -hs, hs}, color });		//7 BBR

	CreateCubeIndices(mesh.indices);

	return mesh;
}

MeshPX MeshBuilder::CreateCubePX(float size, const Color& color)
{
	MeshPX mesh;

	const float hs = size * .5f;

	//front
	mesh.vertices.push_back({ {-hs, -hs, -hs}, {.25f, .66f} });	//0 FBL
	mesh.vertices.push_back({ {-hs, hs, -hs}, {.25f, .33f} });	//1 FTL
	mesh.vertices.push_back({ {hs, hs, -hs}, {.5f, .33f} });	//2 FTR
	mesh.vertices.push_back({ {hs, -hs, -hs}, {.5f, .66f} });	//3 FBR

	//back
	mesh.vertices.push_back({ {-hs, -hs, hs}, {.25f, 1.f} });	//4 BBL
	mesh.vertices.push_back({ {-hs, hs, hs}, {.0f, .33f} });	//5 BTL
	mesh.vertices.push_back({ {hs, hs, hs}, {.5f, .0f} });		//6 BTR
	mesh.vertices.push_back({ {hs, -hs, hs}, {.5f, 1.f} });		//7 BBR

	CreateCubeIndices(mesh.indices);

	return mesh;
}

Mesh MeshBuilder::CreateCube(float size)
{
	Mesh mesh;
	return mesh;
}

MeshPC MeshBuilder::CreateRectPC(float width, float height, float depth)
{
	MeshPC mesh;

	int index = rand() % 100;
	const float hw = width * .5f;
	const float hh = height * .5f;
	const float hd = depth * .5f;

	//front
	mesh.vertices.push_back({ {-hw, -hh, -hd}, GetNextColor(index) });		//0 FBL
	mesh.vertices.push_back({ {-hw, hh, -hd}, GetNextColor(index) });		//1 FTL
	mesh.vertices.push_back({ {hw, hh, -hd}, GetNextColor(index) });		//2 FTR
	mesh.vertices.push_back({ {hw, -hh, -hd}, GetNextColor(index) });		//3 FBR

	//back
	mesh.vertices.push_back({ {-hw, -hh, hd}, GetNextColor(index) });		//4 BBL
	mesh.vertices.push_back({ {-hw, hh, hd}, GetNextColor(index) });		//5 BTL
	mesh.vertices.push_back({ {hw, hh, hd}, GetNextColor(index) });			//6 BTR
	mesh.vertices.push_back({ {hw, -hh, hd}, GetNextColor(index) });		//7 BBR

	CreateCubeIndices(mesh.indices);

	return mesh;
}

MeshPX MeshBuilder::CreateRectPX(float width, float height, float depth)
{
	MeshPX mesh;
	return mesh;
}

MeshPC MeshBuilder::CreatePlanePC(int numRows, int numCols, float spacing)
{
	MeshPC mesh;

	int index = rand() % 100;

	const float hpw = static_cast<float>(numCols) * spacing * .5f;
	const float hph = static_cast<float>(numRows) * spacing * .5f;

	float x = -hpw;
	float y = -hph;

	for (int r = 0; r <= numRows; ++r)
	{
		for (int c = 0; c < numCols; ++c)
		{
			mesh.vertices.push_back({ {x,y,.0f},GetNextColor(index) });
			x += spacing;
		}

		x = -hpw;
		y += spacing;
	}

	CreatePlaneIndices(mesh.indices, numRows, numCols);

	return mesh;
}

MeshPC MeshBuilder::CreateCylinderPC(int slices, int rings)
{
	MeshPC mesh;

	int index = rand() % 100;
	const float hh = static_cast<float> (rings) * .5f;

	for (int r = 0; r <= rings; ++r)
	{
		float ring = static_cast<float>(r);
		for (int s = 0; s < slices + 1; ++s)
		{
			float slice = static_cast<float>(s);
			float rotation = (slice / static_cast<float>(slices)) * BTMath::Constants::TwoPi;

			mesh.vertices.push_back({ {sin(rotation), ring - hh, -cos(rotation)}, GetNextColor(index) });
		}

	}

	mesh.vertices.push_back({ {.0f, hh, .0f}, GetNextColor(index) });
	mesh.vertices.push_back({ {.0f, -hh, .0f}, GetNextColor(index) });

	CreatePlaneIndices(mesh.indices, rings, slices);
	CreateCapIndices(mesh.indices, slices, mesh.vertices.size() - 2, mesh.vertices.size() - 1);


	return mesh;
}

MeshPC MeshBuilder::CreateSpherePC(int slices, int rings, float radius)
{
	MeshPC mesh;

	int index = rand() % 100;

	float vertRotation = BTMath::Constants::Pi / static_cast<float>(rings - 1);
	float horzRotaion = BTMath::Constants::TwoPi / static_cast <float> (slices);
	for (int r = 0; r <= rings; ++r)
	{
		float ring = static_cast<float>(r);
		float phi = ring * vertRotation;
		for (int s = 0; s < slices + 1; ++s)
		{
			float slice = static_cast<float>(s);
			float rotation = slice * horzRotaion;

			mesh.vertices.push_back({ {
				radius * sin(rotation) * sin(phi),
				radius * cos(phi),
				radius * cos(rotation) * sin(phi)},
				GetNextColor(index)
				});
		}
	}

	CreatePlaneIndices(mesh.indices, rings, slices);

	return mesh;
}

MeshPX MeshBuilder::CreateSpherePX(int slices, int rings, float radius)
{
	MeshPX mesh;
	return mesh;
}

Mesh MeshBuilder::CreateSphere(int slices, int rings, float radius)
{
	Mesh mesh;
	return mesh;
}
