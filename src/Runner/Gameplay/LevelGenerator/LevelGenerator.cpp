#include "LevelGenerator.h"

#include "Geometries/Geometries.h"
#include "Tiles/TileFan.h"

#include "Tiles/TileWind.h"
#include "Tiles/TileRandom.h"
#include "Tiles/TileSpiral.h"
#include "Tiles/TileSlalom.h"
#include "Tiles/TileCorner.h"
#include "../../App.h"

#include <random>
#include <Window.h>


#define POS_TILL_DESPAWN 10.f

namespace run
{
    LevelGenerator::LevelGenerator()
    {
    }

    LevelGenerator::~LevelGenerator()
    {
        for (Tile* tile : m_tiles)
            delete tile;
    }

    void LevelGenerator::Init()
    {
        // Enregistrer tous les types de tiles
        RegisterTiles();

        // Générer la première tile
        GenerateNextTile();
        GenerateNextTile();
    }

    void LevelGenerator::RegisterTiles()
    {
        m_tileFactories.push_back({ [](const gce::Vector3f32& pos) -> Tile* { return new TileFan(pos); }, 1 });
        m_tileFactories.push_back({ [](const gce::Vector3f32& pos) -> Tile* { return new TileSpiral(pos); }, 1 });
        m_tileFactories.push_back({ [](const sr::Vector3& pos) -> Tile* { return new TileWind(pos); }, 1 });
        m_tileFactories.push_back({ [](const gce::Vector3f32& pos) -> Tile* { return new TileSlalom(pos); }, 1 });
        m_tileFactories.push_back({ [](const gce::Vector3f32& pos) -> Tile* { return new TileCorner(pos); }, 1 });
        m_tileFactories.push_back({ [](const gce::Vector3f32& pos) -> Tile* { return new TileRandom(pos); }, 1 });

    }


    void LevelGenerator::GenerateNextTile()
    {
        if (m_tileFactories.empty())
            return;

        // Calcul du total des poids
        int totalWeight = 0;
        for (auto& f : m_tileFactories)
            totalWeight += f.weight;

        // Tirage aléatoire pondéré
        static std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> dist(1, totalWeight);
        int rnd = dist(rng);

        int cumulative = 0;
        TileFactory* chosenFactory = nullptr;
        for (auto& f : m_tileFactories)
        {
            cumulative += f.weight;
            if (rnd <= cumulative)
            {
                chosenFactory = &f;
                break;
            }
        }

        if (!chosenFactory)
            chosenFactory = &m_tileFactories.back(); // fallback

        // Créer la tile
        Tile* tile = chosenFactory->createFunc({ 0.f, 0.f, m_lastTileZ });
        m_lastTileZ += tile->GetDepth();
        m_tiles.push_back(tile);
        tile->GenerateGeoms(this);

        // --- Mise à jour des poids
        for (auto& f : m_tileFactories)
        {
            if (&f == chosenFactory)
                f.weight = 1; // réinitialiser le compteur de la tile choisie
            else
                f.weight++;   // incrémenter les autres
        }
    }


    void LevelGenerator::Update(float32 deltaTime, const run::Character& player)
    {
        for (Tile* tile : m_tiles)
        {
            tile->Update(deltaTime, player);
        }

        if (m_tiles.empty() == false)
        {
            Tile* firstTile = *m_tiles.begin();
            if (player.GetPosition().z - POS_TILL_DESPAWN > firstTile->GetPosition().z + firstTile->GetDepth())
            {
                for (sr::Sphere* geom : firstTile->m_geoms)
                {
                    m_waitingList.push_back(geom);
                }
                m_tiles.erase(m_tiles.begin());
                delete firstTile;
                GenerateNextTile();
            }
        }

        m_lastPlayerPos = player.GetPosition();
    }

    void LevelGenerator::Restart()
    {
        m_lastPlayerPos = sr::Vector3(0.0f, 0.0f, 0.0f);
        m_lastTileZ = 0.0f;
        for (auto it = m_tiles.begin(); it != m_tiles.end();)
        {
            for (sr::Sphere* geom : (*it)->m_geoms)
            {
                m_waitingList.push_back(geom);
            }
            delete (*it);
            it = m_tiles.erase(m_tiles.begin());
        }
        GenerateNextTile();
        GenerateNextTile();
    }

    void LevelGenerator::Draw(sr::Window* p_Window)
    {
        for (auto* tile : m_tiles)
            tile->Draw(p_Window);
    }

    sr::Sphere* LevelGenerator::GetSphere()
    {
        sr::Sphere* sphere;
        if (m_waitingList.size() == NULL)
        {
            sphere = new sr::Sphere();
            sphere->SetTexture(*APP.GetTexture("res/Textures/Planets/" + std::to_string(rand() % 15 + 1) + ".jpg" ));
        }
        else
        {
            sphere = m_waitingList.back();
            m_waitingList.pop_back();
        }
        return sphere;
    }
}
