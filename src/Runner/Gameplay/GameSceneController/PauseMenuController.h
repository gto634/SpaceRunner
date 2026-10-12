#ifndef RUNNER_PAUSE_MENU_CONTROLLER_H
#define RUNNER_PAUSE_MENU_CONTROLLER_H

#include "../../Controller.h"

namespace run
{
    class Character;
    
    class PauseMenuController : public run::Controller
    {
    public :
        PauseMenuController() = default;
        
        void Init();
        void CheckInputs(float32 deltatime) override;
    };
}
    
#endif
