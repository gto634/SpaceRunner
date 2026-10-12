#ifndef RUNNER_GAME_OVER_MENU_H
#define RUNNER_GAME_OVER_MENU_H

#include "../../Scene.h"

namespace sr
{
    class Text;
}

namespace run
{
    class GameOverMenuController;
    
    class GameOverMenu : public run::Scene
    {
    public :
        GameOverMenu()= default;
        
        void OnInit() override;
        void OnUpdate(float32 deltatime) override;
        void OnDisplay(sr::Window* window) override;

        ~GameOverMenu() override = default ;
    private :
        run::GameOverMenuController* m_pController;

        std::vector<sr::Text*> m_pUI;
    };
}


#endif