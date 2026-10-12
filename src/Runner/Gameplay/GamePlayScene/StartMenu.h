#ifndef RUNNER_START_MENU_H
#define RUNNER_START_MENU_H

#include "../../Scene.h"

namespace sr
{
    class Text;
}

namespace run
{
    class StartMenuController;
    
    class StartMenu : public run::Scene
    {
    public :
        StartMenu()= default;
        
        void OnInit() override;
        void OnUpdate(float32 deltatime) override;
        void OnDisplay(sr::Window* window) override;

        ~StartMenu() override = default ;
    private :
        run::StartMenuController* m_pController;

        std::vector<sr::Text*> m_pUI;
    };
}

#endif