#ifndef RUNNER_ENTITY_H
#define RUNNER_ENTITY_H

#include "define.h"
#include "Geometries/Geometry.h"

namespace run
{
    using Geometry = sr::Geometry;
    
    class Entity : public Geometry
    {
    public :
        Entity(gce::Geometry* geometry);

#ifdef GIZMOS
        sr::Geometry* GetGizmo();

    protected :
        sr::Geometry* m_pGizmo;
#endif
    };
}
#endif