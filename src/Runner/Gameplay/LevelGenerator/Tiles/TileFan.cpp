#include "TileFan.h"
#include <Geometries/Geometries.h>
#include <cmath>

namespace run
{
    TileFan::TileFan(const gce::Vector3f32& position)
        : Tile(position, 50, 300)
    {
        m_theta = 0.f;
        m_speed = 1.f;
        m_rowCount = 3;
        m_rowSpacing = 50.f;
        m_radius = 80.f;
        m_nb_sphere = 16;
    }

    TileFan::~TileFan()
    {
    }

    void TileFan::Update(float32 dt, const run::Character& player)
    {
        m_theta += dt * m_speed;

        int i = 0;
        for (int row = 0; row < m_rowCount; ++row)
        {
            float zOffset = m_position.z + (row + 1) * m_rowSpacing + 50;

            for (int radius = -m_radius; radius <= m_radius; radius += m_radius * 2 / m_nb_sphere)
            {
                float posX = sin((row % 2 == 0 ? m_theta : -m_theta) + row * 3);
                float posY = cos((row % 2 == 0 ? m_theta : -m_theta) + row * 3);
                m_geoms[i]->SetPosition({ posX * radius, posY * radius, zOffset });
                i++;
            }
        }
    }

    void TileFan::GenerateGeoms(run::LevelGenerator* pLevelGenerator)
    {
        for (int row = 1; row <= m_rowCount; ++row)
        {
            float zOffset = m_position.z + row * m_rowSpacing + 50;

            for (int i = -m_radius; i <= m_radius; i += m_radius * 2 / m_nb_sphere)
            {
                sr::Sphere* sphere = pLevelGenerator->GetSphere();
                sphere->SetPosition({ m_position.x + i, m_position.y, zOffset });
                sphere->SetScale({ 15.f, 15.f, 15.f });
                // sphere->SetColor({
                //     0.3f + 0.2f * row,
                //     0.8f - 0.2f * row,
                //     1.f
                //     });
                m_geoms.push_back(sphere);
            }
        }
    }
}
