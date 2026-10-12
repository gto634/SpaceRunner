#ifndef RUNNER_BACKGROUND_H
#define RUNNER_BACKGROUND_H

#include "Aliases.h"

namespace sr
{
    class Cube;
    class Window;
    class Light;
    struct Texture;
}

namespace run
{
    class Background
    {
    public:
        Background();
        ~Background();

        void Update(float32 deltaTime, const gce::Vector3f32& posCharacter);
        void Draw(sr::Window* p_Window);

    private:
        static constexpr int16 FACE_COUNT = 6;
        static constexpr float32 LENGTH_BACKGROUND = 900.f;

        sr::Vector3 m_lastCharacterPos = { 0.f, 0.f, 0.f };

        sr::Cube* m_faces[FACE_COUNT] = { nullptr };
        sr::Light* m_directionalLights[FACE_COUNT] = { nullptr };
        sr::Texture* m_texture = nullptr;
    };
}
#endif