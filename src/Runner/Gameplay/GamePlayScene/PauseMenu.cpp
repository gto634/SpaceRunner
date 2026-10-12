#include "PauseMenu.h"

#include "App.h"
#include "Text.h"
#include "../../Camera.h"
#include "../GameSceneController/PauseMenuController.h"

void run::PauseMenu::OnInit()
{
    m_pController = new PauseMenuController();
    m_pController->Init();

    //Create UI
    run::AppConfig windowParameter = run::AppConfig();
    
    sr::Text* pResume = new sr::Text(L"ENTER to resume");
    pResume->SetPosition({3.f * static_cast<float32>(windowParameter.width) / 8.f, static_cast<float32>(windowParameter.height) / 4.f});
    pResume->SetColor(sr::Color::Yellow);

    sr::Text* pRestart = new sr::Text(L"R to restart");
    pRestart->SetPosition({3.f * static_cast<float32>(windowParameter.width) / 8.f, static_cast<float32>(windowParameter.height) / 2.f});
    pRestart->SetColor(sr::Color::Yellow);

    sr::Text* pQuit = new sr::Text(L"ESCAPE to quit");
    pQuit->SetPosition({3.f * static_cast<float32>(windowParameter.width) / 8.f, 3.f * static_cast<float32>(windowParameter.height) / 4.f});
    pQuit->SetColor(sr::Color::Yellow);
    
    m_pUI.push_back(pResume);
    m_pUI.push_back(pRestart);
    m_pUI.push_back(pQuit);
}

void run::PauseMenu::OnUpdate(float32 deltatime)
{
    m_pController->CheckInputs(deltatime);
}

void run::PauseMenu::OnDisplay(sr::Window* window)
{
    for (sr::Text* ui : m_pUI)
        run::Camera::Draw(window, ui);
}
