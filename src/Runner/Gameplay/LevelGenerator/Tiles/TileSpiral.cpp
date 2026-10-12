#include "TileSpiral.h"
#include <Geometries/Geometries.h>
#include <cmath>

namespace run
{
    TileSpiral::TileSpiral(const gce::Vector3f32& position)
        : Tile(position, 50, 150),
        m_radius(60.f),
        m_speed(0.2f)
    {
    }

    TileSpiral::~TileSpiral()
    {
    }

    void TileSpiral::Update(float32 dt, const run::Character& player)
    {
        for (auto& s : m_spheres)
        {
            s.progress += (s.forward ? 1 : -1) * dt * m_speed;

            if (s.progress > 1.f)
            {
                s.progress = 1.f;
                s.forward = false;
            }
            else if (s.progress < 0.f)
            {
                s.progress = 0.f;
                s.forward = true;
            }

            float oppositeAngle = s.angle + 3.14159f;
            float x1 = m_position.x + std::cos(s.angle) * m_radius;
            float y1 = m_position.y + std::sin(s.angle) * m_radius;
            float x2 = m_position.x + std::cos(oppositeAngle) * m_radius;
            float y2 = m_position.y + std::sin(oppositeAngle) * m_radius;

            float x = x1 + (x2 - x1) * s.progress;
            float y = y1 + (y2 - y1) * s.progress;

            gce::Vector3f32 pos = s.geom->GetPosition();
            s.geom->SetPosition({ x, y, pos.z });
        }
    }

    void TileSpiral::GenerateGeoms(run::LevelGenerator* pLevelGenerator)
    {
        const int count = 12;
        const float heightStep = 10.f;

        for (int i = 0; i < count; ++i)
        {
            float32 angle = i * (2 * 3.14159f / count);
            float32 x = m_position.x + std::cos(angle) * m_radius;
            float32 y = m_position.y + std::sin(angle) * m_radius;
            float32 z = m_position.z + i * heightStep;

            sr::Sphere* sphere = pLevelGenerator->GetSphere();
            sphere->SetPosition({ x, y, z });
            sphere->SetScale({ 15.f, 15.f, 15.f });
            //sphere->SetColor({ 0.8f, 0.2f + i * 0.05f, 1.f - i * 0.05f });

            m_geoms.push_back(sphere);
            m_spheres.push_back({ sphere, angle, 0.f, true });
        }
    }
}
