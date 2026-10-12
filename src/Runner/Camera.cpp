#include "Camera.h"

#include "Window.h"
#include "Gameplay/LevelGenerator/LevelGenerator.h"
#include "Gameplay/Background.h"
#include "Gameplay/BoundaryCage.h"

void run::Camera::Draw(sr::Window* pWindow, sr::Geometry* geometry)
{
    pWindow->Draw(*geometry);
}

void run::Camera::Draw(sr::Window* pWindow, sr::Text* text)
{
    pWindow->DrawText(*text);
}

void run::Camera::Draw(sr::Window* pWindow, run::LevelGenerator* pLevelGenerator)
{
    pLevelGenerator->Draw(pWindow);
}

void run::Camera::Draw(sr::Window* pWindow, run::Background* pBackground)
{
    pBackground->Draw(pWindow);
}

void run::Camera::Draw(sr::Window* pWindow, run::BoundaryCage* pBoundaryCage)
{
    pBoundaryCage->Draw(pWindow);
}
