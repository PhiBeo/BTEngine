#include "Precompiled.h"
#include "GraphicsSystem.h"

using namespace BTEngine;
using namespace BTEngine::Graphics;

namespace
{
	std::unique_ptr<GraphicsSystem> sGraphicsSystem;
	Core::WindowMessageHandler sWindowMessageHandler;
}

LRESULT CALLBACK GraphicsSystem::GraphicsSystemMessageHandler(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	if(sGraphicsSystem)
	{
		switch (message)
		{
			case WM_SIZE:
			{
				const uint32_t width = static_cast<uint32_t>(LOWORD(lParam));
				const uint32_t height = static_cast<uint32_t>(HIWORD(lParam));
				sGraphicsSystem->Resize(width, height);
				break;
			}
		}
	}
	return sWindowMessageHandler.ForwardMessage(handle, message, wParam, lParam);
}

void GraphicsSystem::StaticInitialize(HWND window, bool fullscreen)
{
	ASSERT(sGraphicsSystem == nullptr, "Graphics system already initialize");
	sGraphicsSystem = std::make_unique<GraphicsSystem>();
	sGraphicsSystem->Initialize(window, fullscreen);
}

void GraphicsSystem::StaticTerminate()
{
	if (sGraphicsSystem != nullptr)
	{
		sGraphicsSystem->Terminate();
		sGraphicsSystem.reset();
	}
}

GraphicsSystem::~GraphicsSystem()
{
	ASSERT(mD3DDevice == nullptr, "Graphics system must be terminate first to do clean up");
}

void GraphicsSystem::Initialize(HWND window, bool fullscreen)
{
}

void GraphicsSystem::Terminate()
{
}

void GraphicsSystem::BeginRender()
{
}

void GraphicsSystem::EndRender()
{
}

void GraphicsSystem::ToggleFullscreen()
{
	BOOL fullscreen;
	mSwapChain->GetFullscreenState(&fullscreen, nullptr);
	mSwapChain->SetFullscreenState(!fullscreen, nullptr);
}

void GraphicsSystem::Resize(uint32_t width, uint32_t height)
{
}

void GraphicsSystem::ResetRenderTarget()
{
	mImmediateContext->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);
}

void GraphicsSystem::ResetViewport()
{
	mImmediateContext->RSSetViewports(1, &mViewport);
}

void GraphicsSystem::SetClearColor(const Color& color)
{
	mClearColor = color;
}

void GraphicsSystem::SetVSync(bool vSync)
{
	mVSync = vSync ? 1 : 0;
}

uint32_t GraphicsSystem::GetBackBufferWidth() const
{
	return mSwapChainDesc.BufferDesc.Width;
}

uint32_t GraphicsSystem::GetBackBufferHeight() const
{
	return mSwapChainDesc.BufferDesc.Height;
}

float GraphicsSystem::GetBackBufferAspectRatio() const
{
	return static_cast<float>(GetBackBufferWidth()) / static_cast<float>(GetBackBufferHeight());
}
