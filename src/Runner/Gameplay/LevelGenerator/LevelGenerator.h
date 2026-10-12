#ifndef RUNNER_LEVEL_GENERATOR_H
#define RUNNER_LEVEL_GENERATOR_H

#include <vector>
#include <functional>
#include "Aliases.h"
#include "Gameplay/Character.h"

namespace sr
{
    class Sphere;
    class Geometry;
    class Window;
}

namespace run
{
    class Game;
    class Tile;

    class LevelGenerator
    {
    public:
        LevelGenerator();
        ~LevelGenerator();

        void Draw(sr::Window* p_Window);

        sr::Sphere* GetSphere();

    private:
        void Init();
        void Update(float32 deltaTime, const run::Character& player);

        void Restart();
        
        // Ajouter tous les types de tiles disponibles
        void RegisterTiles();
        
        void GenerateNextTile();

        struct TileFactory
        {
            std::function<Tile* (const sr::Vector3&)> createFunc;
            int weight; // compteur pour la pondération
        };


        std::vector<Tile*> m_tiles; // tiles générées
        float32 m_lastTileZ = 0.f;
        sr::Vector3 m_lastPlayerPos = { 0.f, 0.f, 0.f };

        // Liste de fonctions permettant de créer des tiles différentes
        std::vector<TileFactory> m_tileFactories;
        
        std::vector<sr::Sphere*> m_waitingList;
        
        friend class run::Game;
        friend class Tile;
    };
}
#endif
