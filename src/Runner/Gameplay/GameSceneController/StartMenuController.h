#ifndef RUNNER_START_MENU_CONTROLLER_H
#define RUNNER_START_MENU_CONTROLLER_H

#include "../../Controller.h"

namespace run
{
    class Character;
    
    class StartMenuController : public run::Controller
    {
    public :
        StartMenuController() = default;
        
        void Init();
        void CheckInputs(float32 deltatime) override;
    };
}
    
#endif
