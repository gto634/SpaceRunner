#include "Scene.h"

void run::Scene::Resume()
{
    m_shouldBeRunning = true;
}

void run::Scene::Pause()
{
    m_shouldBeRunning = false;
}

void run::Scene::Show()
{
    m_shouldBeVisible = true;
}

void run::Scene::Hide()
{
    m_shouldBeVisible = false;
}

void run::Scene::Init()
{
    OnInit();
}

void run::Scene::Update(float32 deltatime)
{
    if (m_running == false)
        return;

    OnUpdate(deltatime);
}

void run::Scene::FixedUpdate(float32 deltatime)
{
    if (m_running == false)
        return;

    OnFixedUpdate(deltatime);
}

void run::Scene::Display(sr::Window* window)
{
    if (m_visible == false)
        return;

    OnDisplay(window);
}

void run::Scene::UpdateStatus()
{
    m_running = m_shouldBeRunning;
    m_visible = m_shouldBeVisible;
}
