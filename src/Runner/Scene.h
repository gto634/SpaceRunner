#ifndef RUNNER_SCENE_H
#define RUNNER_SCENE_H

#include <GCE/Core/define.h>

namespace sr
{
    class Window;
}

namespace run
{
    class Entity;
    class Camera;

    class Scene
    {
    public :
        Scene() = default;
        
        void Resume();
        void Pause();

        void Show();
        void Hide();

        virtual ~Scene() = default;
    
    private :
        void Init();
        void Update(float32 deltatime);
        void FixedUpdate(float32 deltatime);
        void Display(sr::Window* window);

        virtual void OnInit() {};
        virtual void OnUpdate(float32 deltatime) {};
        virtual void OnFixedUpdate(float32 deltatime) {};
        virtual void OnDisplay(sr::Window* window) {};

        void UpdateStatus();

        bool m_running = false;
        bool m_visible = false;

        bool m_shouldBeRunning = false;
        bool m_shouldBeVisible = false;

        friend class App;
    };
}


#endif
