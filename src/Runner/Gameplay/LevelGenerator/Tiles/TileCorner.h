#pragma once
#include "../Tile.h"
#include <vector>

namespace sr { class Sphere; }

namespace run
{
    class TileCorner : public Tile
    {
    public:
        TileCorner(const gce::Vector3f32& position);
        ~TileCorner() override;

        void GenerateGeoms(run::LevelGenerator* pLevelGenerator) override;
        void Update(float dt, const run::Character& player) override;
    };
}
