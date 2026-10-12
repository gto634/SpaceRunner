#pragma once

#include "GCE/Core/Maths/Vector3.h"
#include <vector>

namespace sr
{
    class Cylinder;
    class Window;
}

namespace run
{
    class BoundaryCage
    {
    public:
        BoundaryCage();
        ~BoundaryCage();

        void Update(const gce::Vector3f32& playerPos);
        void Draw(sr::Window* p_Window);
        void InitializeCylinders();

        static constexpr int CYLINDERS_PER_SIDE = 8;     // nombre de cylindres par ligne
        static constexpr float WORLD_BOUND = 50.f;       // demi-largeur du tunnel
        static constexpr float SEGMENT_SPACING = WORLD_BOUND * 2 / CYLINDERS_PER_SIDE;   // distance entre cylindres
        static constexpr float CAGE_RADIUS = 0.15f;      // cylindre fin
        
    private:


        std::vector<sr::Cylinder*> m_topBottomPool;     // Haut/Bas horizontaux X
        std::vector<sr::Cylinder*> m_frontBackPool;     // Horizontaux Z (quadrillage)
        std::vector<sr::Cylinder*> m_leftRightPool;     // Gauche/Droite verticaux

        gce::Vector3f32 m_lastPlayerPos = { 0.f, 0.f, 0.f };
    };
}
