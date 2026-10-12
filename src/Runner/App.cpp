#include "App.h"

#include "Window.h"
#include "Scene.h"
#include "Camera.h"
#include "Renderer.h"
#include "Texture.h"
#include "Gameplay/GamePlayScene/Game.h"
#include "Gameplay/GamePlayScene/GameOverMenu.h"
#include "Gameplay/GamePlayScene/PauseMenu.h"
#include "Gameplay/GamePlayScene/StartMenu.h"

run::App& run::App::GetInstance()
{
    if (m_instance == nullptr)
        m_instance = new App();

    return *m_instance;
}

void run::App::Run()
{
    Init();
    
    while (m_window->IsOpen())
    {
        for (std::unique_ptr<run::Scene>& scene : m_scenes)
            scene->UpdateStatus();
        
        deltatime = m_window->GetDeltaTime();
        time += deltatime;
        
        for (std::unique_ptr<run::Scene>& scene : m_scenes)
            scene->Update(deltatime);
        
        while (time > physicStep)
        {
            for (std::unique_ptr<run::Scene>& scene : m_scenes)
                scene->FixedUpdate(physicStep);

            time -= physicStep;
        }

        m_window->Begin(*m_camera);

        for (std::unique_ptr<run::Scene>& scene : m_scenes)
            scene->Display(m_window);

        m_window->End();
        
        m_window->Display();
    }
}

sr::Texture* run::App::GetTexture(String const& filepath)
{
    if ( m_textures.contains(filepath))
        return m_textures[filepath];

    sr::Texture* texture = new sr::Texture(filepath);
    m_textures[filepath] = texture;

    return texture;    
}

sr::Texture* run::App::GetTexture(String const&& filepath)
{
    return GetTexture(filepath);
}

run::Camera* run::App::GetCamera() const
{
    return m_camera;
}

void run::App::Init()
{
    m_window = new sr::Window(m_config.windowName, m_config.width, m_config.height);
    m_camera = new run::Camera(m_config.cameraType);

    AddScene<run::Game>();
    AddScene<run::StartMenu>();
    AddScene<run::PauseMenu>();
    AddScene<run::GameOverMenu>();
    
    GetScene<run::Game>()->Show();
    GetScene<run::StartMenu>()->Show();
    GetScene<run::StartMenu>()->Resume();
    
}
