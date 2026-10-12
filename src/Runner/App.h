#ifndef RUNNER_APP_H
#define RUNNER_APP_H

#include <GCE/Core/define.h>
#include <GCE/Core/Containers/Vector.hpp>
#include <type_traits>
#include <memory>

#include "Camera.h"

#define APP run::App::GetInstance()

namespace sr
{
    class Window;
    struct Texture;
}

namespace run
{
    class Scene;

    struct AppConfig
    {
        std::wstring windowName = L"Runner";
        int16 width = 1920;
        int16 height = 1080;
        int32 flags = 0;
        sr::CameraType cameraType = sr::CameraType::PERSPECTIVE;
        int32 fps = 60;
    };
    
    class App
    {
    public:
        static App& GetInstance();
    
        void Run();

        template <typename T>
        requires(std::is_base_of_v<run::Scene, T>)
        void AddScene();

        template <typename T>
        requires(std::is_base_of_v<run::Scene, T>)
        void RemoveScene();

        template <typename T>
        requires(std::is_base_of_v<run::Scene, T>)
        T* GetScene();

        Camera* GetCamera() const;

        float32 GetDeltatime() const { return deltatime; };

        sr::Texture* GetTexture(String const& filepath);
        sr::Texture* GetTexture(String const&& filepath);
        
    private :
        void Init();
        
        float32 deltatime = 0.0f;
        float32 time = 0.0f;
        float32 physicStep = 1.f / 60.f;
    
        sr::Window* m_window = nullptr;
        Camera* m_camera = nullptr;

        std::vector<std::unique_ptr<Scene>>  m_scenes;
        UnorderedMap<String, sr::Texture*> m_textures;
        
        static inline AppConfig m_config = AppConfig();

        static inline App* m_instance = nullptr;
    };
}

#include "App.inl"

#endif


