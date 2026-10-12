#ifndef RUNNER_APP_INL
#define RUNNER_APP_INL

#include "App.h"
#include "Scene.h"

template <typename T>
requires(std::is_base_of_v<run::Scene, T>)
inline void run::App::AddScene()
{
    if (GetScene<T>() != nullptr)
        throw std::runtime_error("Scene already exists.");
    
    m_scenes.push_back(std::make_unique<T>());
    m_scenes.at(m_scenes.size()-1)->Init();
}

template<typename T>
requires(std::is_base_of_v<run::Scene, T>)
inline void run::App::RemoveScene()
{
    for (auto iterator = m_scenes.begin(); iterator != m_scenes.end(); ++iterator)
    {
        if (T* casted = dynamic_cast<T*>(*iterator))
        {
            m_scenes.erase(iterator);
            delete casted;
            return;
        }
    }
    throw std::runtime_error("No scene of the type found to remove.");
}

template <typename T>
requires(std::is_base_of_v<run::Scene, T>)
inline T* run::App::GetScene()
{
    for (const std::unique_ptr<run::Scene>& scene : m_scenes)
    {
        if (T* casted = dynamic_cast<T*>(scene.get()))
            return casted;
    }
    return nullptr;
}

#endif