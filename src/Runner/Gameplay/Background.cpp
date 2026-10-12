#include "Background.h"

#include <Geometries/Geometries.h>
#include <Light.h>
#include <Texture.h>
#include <Window.h>

namespace run
{
    Background::Background()
    {
        m_texture = new sr::Texture("res/Textures/sky3.png");

        const float32 halfLength = LENGTH_BACKGROUND / 2.f;

        // Création des faces
        for (int16 i = 0; i < FACE_COUNT; ++i)
        {
            m_faces[i] = new sr::Cube();
            m_faces[i]->SetTexture(*m_texture);
            m_faces[i]->SetScale({ LENGTH_BACKGROUND, LENGTH_BACKGROUND, 1.f });
            m_faces[i]->SetRotation({ 0.f, 0.f, 0.f });
        }

        // Avant (-Z)
        m_faces[0]->SetPosition({ 0.f, 0.f, -halfLength });
        m_faces[0]->SetScale({ LENGTH_BACKGROUND, LENGTH_BACKGROUND, -1.f });

        // Arrière (+Z)
        m_faces[1]->SetPosition({ 0.f, 0.f, halfLength });
        m_faces[1]->SetScale({ -LENGTH_BACKGROUND, LENGTH_BACKGROUND, -1.f });

        // Gauche (-X)
        m_faces[2]->SetPosition({ -halfLength, 0.f, 0.f });
        m_faces[2]->SetScale({ -1, LENGTH_BACKGROUND, LENGTH_BACKGROUND });

        // Droite (+X)
        m_faces[3]->SetPosition({ halfLength, 0.f, 0.f });
        m_faces[3]->SetScale({ -1, -LENGTH_BACKGROUND, LENGTH_BACKGROUND });

        // Haut (+Y)
        m_faces[4]->SetPosition({ 0.f, halfLength, 0.f });
        m_faces[4]->SetScale({ LENGTH_BACKGROUND, -1.f, LENGTH_BACKGROUND });

        // Bas (-Y)
        m_faces[5]->SetPosition({ 0.f, -halfLength, 0.f });
        m_faces[5]->SetScale({ LENGTH_BACKGROUND, -1.f, -LENGTH_BACKGROUND });

        // Lumières directionnelles
        const sr::Vector3 directions[6] = {
            {  0.f,  0.f,  1.f },
            {  0.f,  0.f, -1.f },
            {  1.f,  0.f,  0.f },
            { -1.f,  0.f,  0.f },
            {  0.f, -1.f,  0.f },
            {  0.f,  1.f,  0.f }
        };

        const sr::Vector4 colors[6] = {
            { 1.0f, 0.9f, 0.8f, 1.0f },
            { 0.8f, 0.9f, 1.0f, 1.0f },
            { 0.9f, 0.9f, 1.0f, 1.0f },
            { 0.9f, 0.9f, 1.0f, 1.0f },
            { 1.0f, 1.0f, 0.95f, 1.0f },
            { 0.6f, 0.6f, 0.7f, 1.0f }
        };

        for (int16 i = 0; i < FACE_COUNT; ++i)
        {
            m_directionalLights[i] = new sr::Light(sr::Light::CreateDirectionalLight(
                directions[i], colors[i], 1.5f, 1.0f
            ));
            sr::Light::AddLight(*m_directionalLights[i]);
        }
    }

    Background::~Background()
    {
        for (int i = 0; i < FACE_COUNT; ++i)
        {
            delete m_faces[i];
            delete m_directionalLights[i];
        }

        delete m_texture;
    }

    void Background::Update(float32 deltaTime, const sr::Vector3& posCharacter)
    {
        // Centre la skybox sur le joueur
        for (int i = 0; i < FACE_COUNT; ++i)
        {
            sr::Vector3 localOffset = m_faces[i]->GetPosition() - m_lastCharacterPos;
            m_faces[i]->SetPosition(posCharacter + localOffset);
        }

        m_lastCharacterPos = posCharacter;
    }

    void Background::Draw(sr::Window* p_Window)
    {
        for (int16 i = 0; i < FACE_COUNT; ++i)
            p_Window->Draw(*m_faces[i]);
    }
}
