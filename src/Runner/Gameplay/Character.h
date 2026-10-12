#ifndef RUNNER_CHARACTER_H
#define RUNNER_CHARACTER_H

#include "../Entity.h"
#include "Geometries/Geometries.h"

namespace run
{
    class Character : public Entity
    {
    public :
        Character() : Entity(gce::GeometryFactory::LoadGeometry(RES_PATH"res/Obj/Spaceships/SpaceShip.obj")) {}

        void SetSpeed(float32 speed) {m_speed = speed;}
        float32 GetSpeed() const { return m_speed; }

        void Move(sr::Vector3& direction, float32 deltatime, float32 boundary);
        void Rotate(sr::Vector3& direction, float32 deltatime);
        
        bool IsColliding(sr::Vector3 const& position, float32 radius);
    private :
        float32 m_speed = 15.f;
        float32 m_radius = 1.f;
    };
}

#endif
