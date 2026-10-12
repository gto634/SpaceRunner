#pragma once
#include "../Tile.h"

namespace sr
{
    class Sphere;
}

namespace run
{
    class TileSlalom : public Tile
    {
    public:
        TileSlalom(const gce::Vector3f32& position);
        ~TileSlalom();

        void Update(float32 dt, const run::Character& playerPos) override;
        void GenerateGeoms(run::LevelGenerator* pLevelGenerator) override;

    private:
        std::vector<sr::Sphere*> GenerateRow(float zOffset, int side);

        float m_speed;
        float m_radius;
        float m_rowSpacing;
        int m_lastRowZ;
        int m_rowCount;
        int m_stage_index;
        int m_side;
        int m_nb_spheres;

        run::LevelGenerator* m_pLevelGenerator;
        
        std::vector<std::vector<sr::Sphere*>> m_movingRows;
    };
}
