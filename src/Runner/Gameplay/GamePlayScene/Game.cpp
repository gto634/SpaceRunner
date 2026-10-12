#include "Game.h"

#include "GameOverMenu.h"
#include "Text.h"
#include "../GameSceneController/GameController.h"
#include "../Character.h"
#include "../../Camera.h"
#include "../../App.h"
#include "../LevelGenerator/LevelGenerator.h"
#include "../Background.h"
#include "../BoundaryCage.h"
#include "../LevelGenerator/Tile.h"


run::Game::Game()
{
    m_pLevelGenerator = new LevelGenerator();
    m_pBackground = new Background();
    m_pBoundaryCage = new BoundaryCage();
    m_pCharacter = new Character();
    m_pController = new GameController();
    m_scoreText = new sr::Text();
}

void run::Game::OnInit()
{
    m_pLevelGenerator->Init();
    
    //Base settings for the camera
    APP.GetCamera()->SetPosition(cameraPositionOffset);
    APP.GetCamera()->SetRotation(cameraRotationOffset);
    APP.GetCamera()->SetFOV(gce::PI/3.0f);
    APP.GetCamera()->SetNearPlane(10.f);
    APP.GetCamera()->SetFarPlane(2000.0f);

    // Base settings for the character
    m_pCharacter->SetPosition({0.f,0.f,0.f});
    m_pCharacter->SetScale({0.75f,0.75f,0.75f});
    m_pCharacter->SetColor({0.5f,0.5f,0.5f});
    sr::Texture* texture = APP.GetTexture("res/Textures/SpaceshipUV.png");
    m_pCharacter->SetTexture(*texture);
#ifdef GIZMOS
    m_pCharacter->GetGizmo()->SetScale({3.f,3.f,3.f});
#endif
    
    //Base settings for the controller
    m_pController->Init(m_pCharacter, cameraPositionOffset, cameraRotationOffset);

    //Base settings for the score
    m_scoreText->SetText(L" Score : " + std::to_wstring(m_score));
    m_scoreText->SetPosition({0.0f, 0.0f});
    m_scoreText->SetColor(sr::Color::Yellow);
}

void run::Game::OnUpdate(float32 deltatime)
{
    m_pController->CheckInputs(deltatime);

    sr::Vector3 playerPos = m_pCharacter->GetPosition();
    m_pLevelGenerator->Update(deltatime, *m_pCharacter);
    m_pBackground->Update(deltatime, playerPos);
    m_pBoundaryCage->Update(playerPos);

    m_score = static_cast<int32>(m_pCharacter->GetPosition().z * 10.f);
    m_scoreText->SetText(L" Score : " + std::to_wstring(m_score));

    float32 speed = m_pCharacter->GetSpeed();
    speed = min(50.f ,  speed += (0.1f * deltatime));
    m_pCharacter->SetSpeed(speed);
}

void run::Game::OnFixedUpdate(float32 deltatime)
{
    // Collision
    for (Tile* tiles : m_pLevelGenerator->m_tiles)
    {
        for (auto& obstacle  : tiles->m_geoms)
        {
            if (m_pCharacter->IsColliding(obstacle->GetPosition(), obstacle->GetScale().x / 2))
            {
                //GameOver
                run::GameOverMenu* gameOverMenu = APP.GetScene<run::GameOverMenu>();
                gameOverMenu->Resume();
                gameOverMenu->Show();
                APP.GetScene<run::Game>()->Pause();
            }
        }
    }
}

void run::Game::OnDisplay(sr::Window* window)
{
    run::Camera::Draw(window, m_pBackground);
    run::Camera::Draw(window, m_pBoundaryCage);
    run::Camera::Draw(window, m_pLevelGenerator);

    run::Camera::Draw(window, m_pCharacter);
    run::Camera::Draw(window, m_scoreText);

#ifdef GIZMOS
    run::Camera::Draw(window, m_pCharacter->GetGizmo());
    
#endif
    
}

void run::Game::Restart()
{
    m_score = 0.0f;
    APP.GetCamera()->SetPosition(cameraPositionOffset);
    m_pCharacter->SetPosition({0.0f,0.0f,0.0f});
    m_pCharacter->SetSpeed(15.f);
    m_pBoundaryCage->InitializeCylinders();
    m_pLevelGenerator->Restart();
}
