#include "Tile.h"

#include <Window.h>
#include <Geometries/Geometries.h>

namespace run
{
    Tile::Tile(const sr::Vector3& position, float32 width, float32 depth)
        : m_position(position), m_width(width), m_depth(depth)
    {
    }

    Tile::~Tile()
    {
        m_geoms.clear();
    }

    void Tile::DeleteGeoms(sr::Sphere* geom, run::LevelGenerator* pLevelGenerator)
    {
        pLevelGenerator->m_waitingList.push_back(geom);
        
        auto it = std::find(m_geoms.begin(), m_geoms.end(), geom);
        if (it != m_geoms.end()) {
            m_geoms.erase(it);
        }
    }

    void Tile::Draw(sr::Window* p_Window)
    {
        // Dessiner le tile à sa position
        for (auto geom : m_geoms)
        {
            p_Window->Draw(*geom);
		}
    }
}
