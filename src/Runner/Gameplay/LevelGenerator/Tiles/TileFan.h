#pragma once
#include "../Tile.h"

namespace sr
{
    class Sphere;
}

namespace run
{
    class TileFan : public Tile
    {
    public:
        TileFan(const gce::Vector3f32& position);
        ~TileFan();

        void Update(float32 dt, const run::Character& player) override;
        void GenerateGeoms(run::LevelGenerator* pLevelGenerator) override;

    private:
        float m_theta;
        float m_speed;
        float m_radius;
        float m_rowSpacing;
        int m_nb_sphere;
        int m_rowCount;
    };
}
