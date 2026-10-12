#ifndef RUNNER_GAME_CONTROLLER_H
#define RUNNER_GAME_CONTROLLER_H

#include "../BoundaryCage.h"
#include "../../Controller.h"

namespace run
{
    class Character;
    
    class GameController : public run::Controller
    {
    public :
        GameController() = default;
        
        void Init(Character* character, sr::Vector3 cameraPositionOffset, sr::Vector3 cameraRotationOffset);
        void CheckInputs(float32 deltatime) override;
    private :
        sr::Vector3 m_cameraPositionOffset;
        sr::Vector3 m_cameraRotationOffset;
        run::Character* m_pCharacter;

        float32 m_boundary = BoundaryCage::WORLD_BOUND;
    };
}
    
#endif
