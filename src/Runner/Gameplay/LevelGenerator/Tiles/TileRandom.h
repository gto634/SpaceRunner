#pragma once
#include "../Tile.h"
#include <vector>

namespace sr
{
    class Sphere;
}

namespace run
{
    class TileRandom : public Tile
    {
    public:
        TileRandom(const gce::Vector3f32& position);
        ~TileRandom();

        void Update(float32 dt,const run::Character& player) override;
        void GenerateGeoms(run::LevelGenerator* pLevelGenerator) override;

    private:
        struct MovingSphere
        {
            sr::Sphere* geom;
            gce::Vector3f32 direction; // direction de déplacement
            float speed;               // vitesse individuelle
        };

        std::vector<MovingSphere> m_spheres;
        int m_sphereCount;    // nombre de sphères
    };
}
