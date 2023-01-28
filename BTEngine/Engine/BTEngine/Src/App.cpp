#include "Precompiled.h"
#include "App.h"
#include "AppState.h"

using namespace BTEngine;
using namespace BTEngine::Core;
using namespace BTEngine::Input;


void App::ChangeState(const std::string& stateName)
{
    auto iter = mAppStates.find(stateName);
    if (iter != mAppStates.end())
    {
        mNextState = iter->second.get();
    }
}

void App::Run(const AppConfig& config)
{
    // create window
    Window myWindow;
    myWindow.Initialize(
        GetModuleHandle(nullptr),
        config.appName,
        config.winWidth,
        config.winHeight
    );
    ASSERT(myWindow.isActive(), "Failed to create window!");

    // initialize static classes
    auto handle = myWindow.GetWindowHandle();
    InputSystem::StaticInitialize(handle);

    ASSERT(mCurrentState != nullptr, "App -- need an app state");
    mCurrentState->Initialize();

    mRunning = true;
    while (mRunning)
    {
        myWindow.ProcessMessage();

        auto inputSystem = InputSystem::Get();
        inputSystem->Update();

        if (!myWindow.isActive() || inputSystem->IsKeyPressed(KeyCode::ESCAPE))
        {
            Quit();
            break;
        }

        if (mNextState != nullptr)
        {
            mCurrentState->Terminate();
            mCurrentState = std::exchange(mNextState, nullptr);
            mCurrentState->Initialize();
        }

        // run the game
        auto deltaTime = TimeUtil::GetDeltaTime();
        if (deltaTime < 0.5f)
        {
            mCurrentState->Update(deltaTime);
        }

        mCurrentState->Render();
        mCurrentState->DebugUI();

        // BUILDING APP STATES
        // STARTING MATH LIBRARY (if pix engine)
        // BUILDING SHAPES
    }

    mCurrentState->Terminate();

    // terminate static classes
    InputSystem::StaticTerminate();
    myWindow.Terminate();
}

void App::Quit()
{
    mRunning = false;
}