#pragma once
#include "../Tile.h"

namespace sr
{
    class Sphere;
}

namespace run
{
    class TileSpiral : public Tile
    {
    public:
        TileSpiral(const gce::Vector3f32& position);
        ~TileSpiral();

        void Update(float32 dt, const run::Character& player) override;
        void GenerateGeoms(run::LevelGenerator* pLevelGenerator) override;

    private:
        struct MovingSphere
        {
            sr::Sphere* geom;
            float32 angle;
            float32 progress;
            bool forward;
        };

        std::vector<MovingSphere> m_spheres;
        float32 m_radius;
        float32 m_speed;
    };
}
