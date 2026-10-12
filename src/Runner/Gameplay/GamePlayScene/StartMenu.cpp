#include "StartMenu.h"

#include "App.h"
#include "Text.h"
#include "../../Camera.h"
#include "../GameSceneController/StartMenuController.h"

void run::StartMenu::OnInit()
{
    m_pController = new StartMenuController();
    m_pController->Init();

    //Create UI
    run::AppConfig windowParameter = run::AppConfig();
    
    sr::Text* pStart = new sr::Text(L"ENTER to start");
    pStart->SetPosition({3.f * static_cast<float32>(windowParameter.width) / 8.f, static_cast<float32>(windowParameter.height) / 2.f});
    pStart->SetColor(sr::Color::Yellow);

    sr::Text* pQuit = new sr::Text(L"ESCAPE to quit");
    pQuit->SetPosition({3.f * static_cast<float32>(windowParameter.width) / 8.f, 3.f * static_cast<float32>(windowParameter.height) / 4.f});
    pQuit->SetColor(sr::Color::Yellow);
    
    m_pUI.push_back(pStart);
    m_pUI.push_back(pQuit);
}

void run::StartMenu::OnUpdate(float32 deltatime)
{
    m_pController->CheckInputs(deltatime);
}

void run::StartMenu::OnDisplay(sr::Window* window)
{
    for (sr::Text* ui : m_pUI)
        run::Camera::Draw(window, ui);
}
