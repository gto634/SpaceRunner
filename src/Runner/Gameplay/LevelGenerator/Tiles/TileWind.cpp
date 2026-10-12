#include "TileWind.h"

#include "../../../IntervalClock.h"

#include <Geometries/Geometries.h>
#include <cstdlib>
#include <cmath>

namespace run
{
    static float RandomFloat(float min, float max)
    {
        return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
    }

    TileWind::TileWind(const gce::Vector3f32& position)
        : Tile(position, 50, 200)
    {
        m_spawnRadius = 100.f;
        m_speed = 40.f;

        m_spawnClock = new IntervalClock(0.1f);

        m_windDirection = { RandomFloat(-1.f, 1.f), RandomFloat(-1.f, 1.f), -0.5f };
        float len = std::sqrt(m_windDirection.x * m_windDirection.x +
            m_windDirection.y * m_windDirection.y +
            m_windDirection.z * m_windDirection.z);
        m_windDirection.x /= len;
        m_windDirection.y /= len;
        m_windDirection.z /= len;
    }


    TileWind::~TileWind()
    {
        delete m_spawnClock;
        m_spawnClock = nullptr;
    }


    void TileWind::GenerateGeoms(run::LevelGenerator* pLevelGenerator)
    {
        m_pLevelGenerator = pLevelGenerator;
    }

    void TileWind::SpawnSphere()
    {
        const float spawnOffset = m_spawnRadius * 2.f; 
        gce::Vector3f32 planeCenter = {
            m_position.x - m_windDirection.x * spawnOffset,
            m_position.y - m_windDirection.y * spawnOffset,
            m_position.z - m_windDirection.z * spawnOffset
        };

        gce::Vector3f32 u, v;

        if (std::fabs(m_windDirection.x) < 0.9f)
            u = { 0, -m_windDirection.z, m_windDirection.y };
        else
            u = { -m_windDirection.y, m_windDirection.x, 0 };

        float lenU = std::sqrt(u.x * u.x + u.y * u.y + u.z * u.z);
        u.x /= lenU; u.y /= lenU; u.z /= lenU;

        v = {
            m_windDirection.y * u.z - m_windDirection.z * u.y,
            m_windDirection.z * u.x - m_windDirection.x * u.z,
            m_windDirection.x * u.y - m_windDirection.y * u.x
        };

        float radius = RandomFloat(-m_spawnRadius, m_spawnRadius);
        float angle = RandomFloat(0.f, 2.f * 3.14159f);
        float offsetU = radius * std::cos(angle);
        float offsetV = radius * std::sin(angle);

        gce::Vector3f32 pos = {
            planeCenter.x + offsetU * u.x + offsetV * v.x,
            planeCenter.y + offsetU * u.y + offsetV * v.y,
            planeCenter.z + offsetU * u.z + offsetV * v.z
        };

        float size = RandomFloat(6.f, 12.f);
        float r = RandomFloat(0.5f, 1.0f);
        float g = RandomFloat(0.5f, 1.0f);
        float b = RandomFloat(0.8f, 1.0f);

        sr::Sphere* sphere = m_pLevelGenerator->GetSphere();
        sphere->SetPosition({ pos.x, pos.y, pos.z });
        sphere->SetScale({ size, size, size });
        //sphere->SetColor({ r, g, b });

        m_geoms.push_back(sphere);
    }




    void TileWind::Update(float dt, const run::Character& player)
    {
        std::vector<sr::Sphere*> toDelete;

        // Mise à jour du spawn
        if (m_spawnClock->Update(dt))
        {
            SpawnSphere();
            m_spawnClock->Restart();
        }

        // Déplacement et suppression des sphères trop loin
        for (auto& geom : m_geoms)
        {
            gce::Vector3f32 delta = {
                m_windDirection.x * m_speed * dt,
                m_windDirection.y * m_speed * dt,
                m_windDirection.z * m_speed * dt
            };
            geom->Translate(delta);

            gce::Vector3f32 pos = geom->GetPosition();
            if (pos.z > m_position.z + m_depth + 100.f ||
                pos.x < m_position.x - m_spawnRadius * 2.f ||
                pos.x > m_position.x + m_spawnRadius * 2.f ||
                pos.y < m_position.y - m_spawnRadius * 2.f ||
                pos.y > m_position.y + m_spawnRadius * 2.f)
            {
                toDelete.push_back(geom);
            }
        }

        // Supprimer les sphères sorties
        for (auto* geom : toDelete) {
            DeleteGeoms(geom, m_pLevelGenerator);
        }
    }

}
