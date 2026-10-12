#ifndef RUNNER_GAME_OVER_MENU_CONTROLLER_H
#define RUNNER_GAME_OVER_MENU_CONTROLLER_H

#include "../../Controller.h"

namespace run
{
    class Character;
    
    class GameOverMenuController : public run::Controller
    {
    public :
        GameOverMenuController() = default;
        
        void Init();
        void CheckInputs(float32 deltatime) override;
    };
}
    
#endif
