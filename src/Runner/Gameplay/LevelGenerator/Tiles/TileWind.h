#pragma once
#include "../Tile.h"
#include <vector>

class IntervalClock;

namespace sr
{
    class Sphere;
}

namespace run
{
    class TileWind : public Tile
    {
    public:
        TileWind(const gce::Vector3f32& position);
        ~TileWind() override;

        void Update(float dt, const run::Character& player) override;
        void GenerateGeoms(run::LevelGenerator* pLevelGenerator) override;
		void SpawnSphere();

    private:

		IntervalClock* m_spawnClock;
        gce::Vector3f32 m_windDirection;
        float m_spawnRadius;
        float m_speed;
    };
}
