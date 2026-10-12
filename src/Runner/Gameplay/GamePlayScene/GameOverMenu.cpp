#include "GameOverMenu.h"

#include "App.h"
#include "Camera.h"
#include "../GameSceneController/GameOverMenuController.h"
#include "Text.h"

void run::GameOverMenu::OnInit()
{
    m_pController = new run::GameOverMenuController();
    m_pController->Init();

    //Create UI
    run::AppConfig windowParameter = run::AppConfig();
    
    sr::Text* pGameOver = new sr::Text(L"GAME OVER");
    pGameOver->SetPosition({3.f * static_cast<float32>(windowParameter.width) / 8.f, static_cast<float32>(windowParameter.height) / 4.f});
    pGameOver->SetColor(sr::Color::Yellow);

    sr::Text* pRestart = new sr::Text(L"R to restart");
    pRestart->SetPosition({3.f * static_cast<float32>(windowParameter.width) / 8.f, static_cast<float32>(windowParameter.height) / 2.f});
    pRestart->SetColor(sr::Color::Yellow);

    sr::Text* pQuit = new sr::Text(L"ESCAPE to quit");
    pQuit->SetPosition({3.f * static_cast<float32>(windowParameter.width) / 8.f, 3.f * static_cast<float32>(windowParameter.height) / 4.f});
    pQuit->SetColor(sr::Color::Yellow);
    
    m_pUI.push_back(pRestart);
    m_pUI.push_back(pGameOver);
    m_pUI.push_back(pQuit);
}

void run::GameOverMenu::OnUpdate(float32 deltatime)
{
    m_pController->CheckInputs(deltatime);
}

void run::GameOverMenu::OnDisplay(sr::Window* window)
{
    for (sr::Text* ui : m_pUI)
        run::Camera::Draw(window, ui);
}
