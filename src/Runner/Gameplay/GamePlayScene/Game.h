#ifndef GAME_RUNNER_H
#define GAME_RUNNER_H

#include "Entity.h"
#include "GCE/Core/Maths/Vector3.h"
#include "../../Scene.h"

namespace sr
{
    class Text;
    class Window;
}


namespace run
{
    class Character;
    class GameController;
    class LevelGenerator;
    class Background;
    class BoundaryCage;
    
    class Game : public run::Scene
    {
    public :
        Game();
        
        void OnInit() override;
        void OnUpdate(float32 deltatime) override;
        void OnFixedUpdate(float32 deltatime) override;
        void OnDisplay(sr::Window* window) override;

        void Restart();

        ~Game() override = default ;
    private :
        
        static inline sr::Vector3 cameraPositionOffset = {0.0f,5.0f,-20.0f};
        static inline sr::Vector3 cameraRotationOffset = {15.0f,0.0f,0.0f};
        
        int32 m_score = 0;
        sr::Text* m_scoreText;
        
        Character* m_pCharacter;
        GameController* m_pController;

        LevelGenerator* m_pLevelGenerator;
        Background* m_pBackground;
        BoundaryCage* m_pBoundaryCage;
    };
}

#endif
