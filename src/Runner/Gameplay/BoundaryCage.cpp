#include "BoundaryCage.h"

#include <Geometries/Geometries.h>
#include <Window.h>

namespace run
{
    BoundaryCage::BoundaryCage()
    {
        const int totalVertical = (CYLINDERS_PER_SIDE + 1) * 2;
        const int totalHorizontal = (CYLINDERS_PER_SIDE + 1) * 2;
        const int totalFrontBack = CYLINDERS_PER_SIDE * 4;

        m_leftRightPool.reserve(totalVertical);
        m_topBottomPool.reserve(totalHorizontal);
        m_frontBackPool.reserve(totalFrontBack);

        // Création simple des cylindres (pas encore de position ou couleur)
        for (int i = 0; i < totalVertical; ++i)
            m_leftRightPool.push_back(new sr::Cylinder());

        for (int i = 0; i < totalHorizontal; ++i)
            m_topBottomPool.push_back(new sr::Cylinder());

        for (int i = 0; i < totalFrontBack; ++i)
            m_frontBackPool.push_back(new sr::Cylinder());

        InitializeCylinders();
    }

    BoundaryCage::~BoundaryCage()
    {
        for (auto* cyl : m_topBottomPool) delete cyl;
        for (auto* cyl : m_frontBackPool) delete cyl;
        for (auto* cyl : m_leftRightPool) delete cyl;
    }

    void BoundaryCage::InitializeCylinders()
    {
        const sr::Vector3 greenColor = { 0.f, 1.f, 0.f };
        const float32 spacing = SEGMENT_SPACING;
        const float32 bound = WORLD_BOUND;

        // --- Gauche / Droite ---
        for (int16 i = 0; i < CYLINDERS_PER_SIDE + 1; i++)
        {
            float32 zPos = i * spacing;
            int idx = i * 2;

            auto* left = m_leftRightPool[idx];
            left->SetColor(greenColor);
            left->SetScale({ CAGE_RADIUS, bound * 2, CAGE_RADIUS });
            left->SetPosition({ -bound, 0.f, zPos });

            auto* right = m_leftRightPool[idx + 1];
            right->SetColor(greenColor);
            right->SetScale({ CAGE_RADIUS, bound * 2, CAGE_RADIUS });
            right->SetPosition({ bound, 0.f, zPos });
        }

        // --- Haut / Bas ---
        for (int16 i = 0; i < CYLINDERS_PER_SIDE + 1; i++)
        {
            float32 zPos = i * spacing;
            int idx = i * 2;

            auto* top = m_topBottomPool[idx];
            top->SetColor(greenColor);
            top->SetScale({ bound * 2, CAGE_RADIUS, CAGE_RADIUS });
            top->SetPosition({ 0.f, bound, zPos });

            auto* bottom = m_topBottomPool[idx + 1];
            bottom->SetColor(greenColor);
            bottom->SetScale({ bound * 2, CAGE_RADIUS, CAGE_RADIUS });
            bottom->SetPosition({ 0.f, -bound, zPos });
        }

        // --- Front / Back ---
        int j = 0;
        for (int16 i = -CYLINDERS_PER_SIDE / 2; i < CYLINDERS_PER_SIDE / 2; i++)
        {
            float32 delta = i * spacing;

            auto* right = m_frontBackPool[j++];
            right->SetColor(greenColor);
            right->SetScale({ CAGE_RADIUS, WORLD_BOUND * 2, CAGE_RADIUS });
            right->SetRotation({ 90.f, 0.f, 0.f });
            right->SetPosition({ bound, delta, spacing * CYLINDERS_PER_SIDE / 2 });

            auto* left = m_frontBackPool[j++];
            left->SetColor(greenColor);
            left->SetScale({ CAGE_RADIUS, WORLD_BOUND * 2, CAGE_RADIUS });
            left->SetRotation({ 90.f, 0.f, 0.f });
            left->SetPosition({ -bound, delta, spacing * CYLINDERS_PER_SIDE / 2 });

            auto* up = m_frontBackPool[j++];
            up->SetColor(greenColor);
            up->SetScale({ CAGE_RADIUS, WORLD_BOUND * 2, CAGE_RADIUS });
            up->SetRotation({ 90.f, 0.f, 0.f });
            up->SetPosition({ delta, bound, spacing * CYLINDERS_PER_SIDE / 2 });

            auto* down = m_frontBackPool[j++];
            down->SetColor(greenColor);
            down->SetScale({ CAGE_RADIUS, WORLD_BOUND * 2, CAGE_RADIUS });
            down->SetRotation({ 90.f, 0.f, 0.f });
            down->SetPosition({ delta, -bound, spacing * CYLINDERS_PER_SIDE / 2 });
        }

        m_lastPlayerPos = { 0.f, 0.f, 0.f };
    }


    void BoundaryCage::Update(const gce::Vector3f32& playerPos)
    {
        const float32 spacing = SEGMENT_SPACING;
        const float32 tunnelLength = (CYLINDERS_PER_SIDE + 1) * spacing;

        // Cylindres verticaux (Gauche/Droite)
        for (auto* cyl : m_leftRightPool)
        {
            // Si le cylindre est derrière le joueur de plus d'une "case"
            if (cyl->GetPosition().z < playerPos.z - spacing)
            {
                sr::Vector3 pos = cyl->GetPosition();
                pos.z += tunnelLength;  // le remettre devant
                cyl->SetPosition(pos);
            }
        }

        // Cylindres horizontaux X (Haut/Bas)
        for (auto* cyl : m_topBottomPool)
        {
            if (cyl->GetPosition().z < playerPos.z - spacing)
            {
                sr::Vector3 pos = cyl->GetPosition();
                pos.z += tunnelLength;  // le remettre devant
                cyl->SetPosition(pos);
            }
        }

        sr::Vector3 movement = { 0.f, 0.f, playerPos.z - m_lastPlayerPos.z };

        for (auto* cyl : m_frontBackPool)
        {
            cyl->Translate(movement);
		}

        m_lastPlayerPos = playerPos;
    }

    void BoundaryCage::Draw(sr::Window* p_Window)
    {
        for (auto* cyl : m_topBottomPool) p_Window->Draw(*cyl);
        for (auto* cyl : m_frontBackPool) p_Window->Draw(*cyl);
        for (auto* cyl : m_leftRightPool) p_Window->Draw(*cyl);
    }
}
