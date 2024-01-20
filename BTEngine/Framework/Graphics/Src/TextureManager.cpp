#include "Precompiled.h"
#include "TextureManager.h"

using namespace BTEngine;
using namespace BTEngine::Graphics;

void BTEngine::Graphics::TextureManager::StaticInitialize(const std::filesystem::path& root)
{
	ASSERT(sInstance == nullptr, "TextureManager: is already initialize");
	sInstance = std::make_unique<TextureManager>();
	sInstance->
}

void BTEngine::Graphics::TextureManager::StaticTerminate()
{
	
}

TextureManager* BTEngine::Graphics::TextureManager::Get()
{
	ASSERT(sInstance != nullptr, "TextureManager: cannot get");
}

BTEngine::Graphics::TextureManager::~TextureManager()
{
}

void BTEngine::Graphics::TextureManager::SetRootDirectory(const std::filesystem::path& root)
{
	mRootDirectory = std::move(root);
}

TextureId BTEngine::Graphics::TextureManager::LoadTexture(const std::filesystem::path& filename, bool useRoot)
{
	const size_t textureId = std::filesystem::hash_value(filename);
	auto [iter, success] = mInventory.insert({ textureId, nullptr });
	if (success)
	{
		auto& texturePtr = iter->second;
		texturePtr = std::make_unique<Texture>();
		texturePtr->Initialize((useRoot) ? mRootDirectory / filename : filename);
	}

	return textureId;
}

const Texture* BTEngine::Graphics::TextureManager::GetTexture(TextureId id)
{
	return nullptr;
}

void BTEngine::Graphics::TextureManager::BindVS(TextureId id, uint32_t slot) const
{
	if (id == 0)
	{
		return;
	}

	auto iter = mInventory.find(id);
	if (iter != mInventory.end())
	{
		iter->second->BindVS(slot);
	}
}

void BTEngine::Graphics::TextureManager::BindPS(TextureId id, uint32_t slot) const
{
	if (id == 0)
	{
		return;
	}

	auto iter = mInventory.find(id);
	if (iter != mInventory.end())
	{
		iter->second->BindPS(slot);
	}
}
