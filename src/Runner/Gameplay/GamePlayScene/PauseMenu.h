#ifndef RUNNER_PAUSE_MENU_H
#define RUNNER_PAUSE_MENU_H

#include "../../Scene.h"

namespace sr
{
    class Text;
}

namespace run
{
    class PauseMenuController;
    
    class PauseMenu : public run::Scene
    {
    public :
        PauseMenu()= default;
        
        void OnInit() override;
        void OnUpdate(float32 deltatime) override;
        void OnDisplay(sr::Window* window) override;

        ~PauseMenu() override = default ;
    private :
        run::PauseMenuController* m_pController;

        std::vector<sr::Text*> m_pUI;
    };
}

#endif