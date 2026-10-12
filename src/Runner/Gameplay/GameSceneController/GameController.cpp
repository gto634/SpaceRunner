#include "GameController.h"

#include <algorithm>

#include "../Character.h"
#include "MathsUtils.hpp"
#include "Inputs/InputsMethods.h"
#include "../../App.h"
#include "Gameplay/GamePlayScene/Game.h"
#include "Gameplay/GamePlayScene/PauseMenu.h"

void run::GameController::Init(Character* character, sr::Vector3 cameraPositionOffset, sr::Vector3 cameraRotationOffset)
{
    keybinds.insert({"up", sr::Keyboard::Z});
    keybinds.insert({"down", sr::Keyboard::S});
    keybinds.insert({"left", sr::Keyboard::Q});
    keybinds.insert({"right", sr::Keyboard::D});

    keybinds.insert({"pause", sr::Keyboard::ESCAPE});
    
    m_pCharacter = character;
    m_cameraPositionOffset = cameraPositionOffset;
    m_cameraRotationOffset = cameraRotationOffset;
}

void run::GameController::CheckInputs(float32 deltatime)
{
    float32 speed = m_pCharacter->GetSpeed() * deltatime;

    sr::Vector3 playerDir = sr::Vector3{0.0f,0.0f,1.0f};
    sr::Vector3 playerRot = sr::Vector3{0.0f,0.0f,0.0f};
    sr::Vector3 cameraRot = m_cameraRotationOffset;

    if (sr::GetKeyDown(keybinds["pause"]))
    {
        run::PauseMenu* pauseMenu = APP.GetScene<run::PauseMenu>();
        pauseMenu->Show();
        pauseMenu->Resume();
        APP.GetScene<run::Game>()->Pause();
        return;
    }
    // Get inputs and make character do things
    if (sr::GetKey(keybinds["up"]))
    {   
        playerDir += sr::Vector3{0.0f,1.0f,0.0f};
        playerRot += sr::Vector3{-15.0f,0.0f,0.0f};
        cameraRot += sr::Vector3{-15.0f,0.0f,0.0f};
    }
    if (sr::GetKey(keybinds["down"]))
    {   
        playerDir += sr::Vector3{0.0f,-1.0f,0.0f};
        playerRot += sr::Vector3{15.0f,0.0f,0.0f};
        cameraRot += sr::Vector3{15.0f,0.0f,0.0f};
    }
    if (sr::GetKey(keybinds["left"]))
    {   
        playerDir += sr::Vector3{-1.0f,0.0f,0.0f};
        playerRot += sr::Vector3{0.0f,0.0f,15.0f};
        cameraRot += sr::Vector3{0.0f,0.0f,15.0f};
    }
    if (sr::GetKey(keybinds["right"]))
    {   
        playerDir += sr::Vector3{1.0f,0.0f,0.0f};
        playerRot += sr::Vector3{0.0f,0.0f,-15.0f};
        cameraRot += sr::Vector3{0.0f,0.0f,-15.0f};
    }

    //Move the character depending on the input
    // sr::Vector3 characterPos = m_pCharacter->GetPosition();
    // characterPos += playerDir.SelfNormalize() * speed;
    // sr::Vector3 newPos = {std::clamp(characterPos.x, -m_boundary, m_boundary), std::clamp(characterPos.y, -m_boundary, m_boundary), characterPos.z, };
    m_pCharacter->Move(playerDir, deltatime, m_boundary);

    // sr::Vector3 playerGoal = Lerp( m_pCharacter->GetRotation() * RAD2DEG , playerRot, min(deltatime, 1.0f));
    // m_pCharacter->SetRotation(playerGoal);
    m_pCharacter->Rotate(playerRot, deltatime);
    
    // Make sure the camera follow the character
    run::Camera* camera = APP.GetCamera();
    camera->SetPosition(Lerp(camera->GetPosition(), m_pCharacter->GetPosition() + m_cameraPositionOffset, deltatime * 2.0f));

    // Rotate the camera depending on the direction of the player
    sr::Vector3 cameraGoal = Lerp( camera->GetRotation() * RAD2DEG , cameraRot, min(deltatime, 1.0f));
    camera->SetRotation(cameraGoal);
}