#include "TileRandom.h"
#include <Geometries/Geometries.h>
#include <cstdlib>
#include <cmath>

namespace run
{
    static float RandomFloat(float min, float max)
    {
        return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
    }

    TileRandom::TileRandom(const gce::Vector3f32& position)
        : Tile(position, 50, 300)
    {
        m_sphereCount = 30;
    }

    TileRandom::~TileRandom()
    {
    }

    void TileRandom::Update(float32 dt, const run::Character& player)
    {
        for (auto& s : m_spheres)
        {
            // Mouvement
            gce::Vector3f32 delta = {
                s.direction.x * s.speed * dt,
                s.direction.y * s.speed * dt,
                s.direction.z * s.speed * dt
            };

            s.geom->Translate(delta);

            // Récupère position actuelle
            gce::Vector3f32 pos = s.geom->GetPosition();

            // Rebond simple sur les limites de la tile
            if (pos.x < m_position.x - m_width || pos.x > m_position.x + m_width)
                s.direction.x *= -1.f;
            if (pos.y < m_position.y - m_width || pos.y > m_position.y + m_width)
                s.direction.y *= -1.f;
            if (pos.z < m_position.z || pos.z > m_position.z + m_depth)
                s.direction.z *= -1.f;
        }
    }

    void TileRandom::GenerateGeoms(run::LevelGenerator* pLevelGenerator)
    {
        for (int i = 0; i < m_sphereCount; ++i)
        {
            // Position aléatoire dans un cube autour de la tile
            float x = m_position.x + RandomFloat(-m_width, m_width);
            float y = m_position.y + RandomFloat(-m_width, m_width);
            float z = m_position.z + RandomFloat(0, m_depth);

            // Taille aléatoire
            float size = RandomFloat(5.f, 30.f);

            // Couleur aléatoire
            float r = RandomFloat(0.2f, 1.0f);
            float g = RandomFloat(0.2f, 1.0f);
            float b = RandomFloat(0.2f, 1.0f);

            sr::Sphere* sphere = pLevelGenerator->GetSphere();
            sphere->SetPosition({ x, y, z });
            sphere->SetScale({ size, size, size });
            //sphere->SetColor({ r, g, b });

            // Direction de déplacement aléatoire normalisée
            gce::Vector3f32 dir = {
                RandomFloat(-1.f, 1.f),
                RandomFloat(-1.f, 1.f),
                RandomFloat(-0.3f, 0.3f)
            };

            float len = std::sqrt(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
            dir.x /= len;
            dir.y /= len;
            dir.z /= len;

            float speed = RandomFloat(0.f, 10.f);

            m_spheres.push_back({ sphere, dir, speed });
            m_geoms.push_back(sphere);
        }
    }
}
