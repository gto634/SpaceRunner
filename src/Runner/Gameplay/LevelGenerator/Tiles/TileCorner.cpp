#include "TileCorner.h"
#include <Geometries/Geometries.h>
#include <cstdlib>

namespace run
{
    static float RandomFloat(float min, float max)
    {
        return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
    }

    TileCorner::TileCorner(const gce::Vector3f32& position)
        : Tile(position, 50.f, 200.f)
    {
    }

    TileCorner::~TileCorner()
    {
        m_geoms.clear();
    }

    void TileCorner::GenerateGeoms(run::LevelGenerator* pLevelGenerator)
    {
        m_pLevelGenerator = pLevelGenerator;

        // Définition des 4 coins autour du centre
        const std::vector<gce::Vector3f32> corners = {
            { -25.f, -25.f, m_position.z }, // bas gauche
            { -25.f,  25.f, m_position.z }, // haut gauche
            {  25.f,  25.f, m_position.z }, // haut droite
            {  25.f, -25.f, m_position.z }  // bas droite
        };

        // On choisit un coin libre aléatoire
        int freeCorner = rand() % 4;

        // On spawn des sphères sur les 3 autres coins
        for (int i = 0; i < 4; ++i)
        {
            if (i == freeCorner)
                continue;

            sr::Sphere* sphere = pLevelGenerator->GetSphere();

            gce::Vector3f32 pos = {
                m_position.x + corners[i].x,
                m_position.y + corners[i].y,
                m_position.z + 100.f
            };

            sphere->SetPosition(pos);
            sphere->SetScale({ 75.f, 75.f, 75.f });

            // Couleur rougeâtre pour bien signaler l’obstacle
            //sphere->SetColor({ RandomFloat(0.8f, 1.0f), RandomFloat(0.2f, 0.4f), RandomFloat(0.2f, 0.4f) });

            m_geoms.push_back(sphere);
        }
    }

    void TileCorner::Update(float dt, const run::Character& player)
    {
        // Pas d'update particulier pour cette tuile
    }
}
