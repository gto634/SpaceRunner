#ifndef RUNNER_TILE_H
#define RUNNER_TILE_H

#include "GCE/Core/Maths/Vector3.h"
#include <vector>

#include "LevelGenerator.h"

namespace sr
{
    class Window;
    class Geometry;
}

namespace run
{
    class Game;
    
    class Tile
    {
    public:
        Tile(const gce::Vector3f32& position, float width = 10.f, float depth = 10.f);
        virtual ~Tile();

        void SetPosition(const gce::Vector3f32& pos) { m_position = pos; }
        const gce::Vector3f32& GetPosition() const { return m_position; }
        
        virtual void Update(float32 dt, const run::Character& playerPos) = 0;
        virtual void GenerateGeoms(run::LevelGenerator* pLevelGenerator) = 0;
        void DeleteGeoms(sr::Sphere* geom, run::LevelGenerator* pLevelGenerator);
        void Draw(sr::Window* p_Window);

		int GetWidth() const { return static_cast<int>(m_width); }
		int GetDepth() const { return static_cast<int>(m_depth); }

		void SetWidth(float width) { m_width = width; }
		void SetDepth(float depth) { m_depth = depth; }

        // Système de pondération
        int GetWeightCounter() const { return m_weightCounter; }
        void ResetWeightCounter() { m_weightCounter = 0; }
        void IncreaseWeightCounter() { m_weightCounter++; }

    protected:
        sr::Vector3 m_position;
        float32 m_width;
        float32 m_depth;
        std::vector<sr::Sphere*> m_geoms;
        run::LevelGenerator* m_pLevelGenerator;

        int m_weightCounter = 0;

        friend class run::Game;
        friend class run::LevelGenerator;
    };
}

#endif
