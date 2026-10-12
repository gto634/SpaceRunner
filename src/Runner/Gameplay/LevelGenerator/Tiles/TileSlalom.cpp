#include "TileSlalom.h"
#include <Geometries/Geometries.h>
#include <cstdlib>

namespace run
{
    TileSlalom::TileSlalom(const gce::Vector3f32& position)
        : Tile(position, 50, 500)
    {
        m_speed = 40.f;
        m_rowCount = 3;
        m_rowSpacing = 150.f;
        m_radius = 80.f;
        m_lastRowZ = position.z;
        m_nb_spheres = 3;
        m_stage_index = 0;
        m_side = 1;
    }

    TileSlalom::~TileSlalom()
    {
    }

    std::vector<sr::Sphere*> TileSlalom::GenerateRow(float zOffset, int side)
    {
        float factor = (side == 1 ? 0.33f : side == 0 ? 0.5f : 0.66f);
        float lateralOffset = m_width * 2 * factor - m_width;
        lateralOffset -= (side != 0 ? 16.5f : 0) * side;

        float totalWidth = m_width * 2;
        float sphereSize = 33.f;
        float radius = sphereSize / 2.f;

        std::vector<sr::Sphere*> row;
        float step = (totalWidth - 2 * radius) / (m_nb_spheres - 1);

        for (int i = 0; i < m_nb_spheres; i++)
        {
            float yPos = radius + i * step - 50;

            sr::Sphere* sphere = m_pLevelGenerator->GetSphere();
            sphere->SetPosition({ m_position.x + lateralOffset, m_position.y + yPos, zOffset });
            sphere->SetScale({ sphereSize, sphereSize, sphereSize });
            //sphere->SetColor({ 1, 0, 0 });

            row.push_back(sphere);
            m_geoms.push_back(sphere);
        }
        return row;
    }

    void TileSlalom::Update(float32 dt, const run::Character& player)
    {
        float localPlayerZ = player.GetPosition().z - m_position.z;

        if (localPlayerZ > m_rowSpacing * m_stage_index + 75.f)
        {
            int side = (rand() % 2 == 0) ? -1 : 1;

            float newRowZ = m_position.z + m_rowSpacing * (m_stage_index + 2) + 75.f;

            m_movingRows.push_back(GenerateRow(newRowZ, side));
            m_stage_index++;
        }

        for (std::vector<sr::Sphere*>& rows : m_movingRows)
        {
            for (sr::Sphere* sphere : rows)
            {
                sphere->Translate({ 0, 0, -m_speed * dt });
            }
        }
    }


    void TileSlalom::GenerateGeoms(run::LevelGenerator* pLevelGenerator)
    {
        m_pLevelGenerator = pLevelGenerator;
        
        for (int row = 1; row <= m_rowCount; ++row)
        {
            float zOffset = m_position.z + row * m_rowSpacing + 50.f;
            GenerateRow(zOffset, 0);
        }
    }
}
