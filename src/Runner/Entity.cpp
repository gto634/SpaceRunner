#include "Entity.h"

#include "define.h"
#include "Geometries/Geometries.h"

run::Entity::Entity(gce::Geometry* geometry) : Geometry(geometry) 
{
#ifdef GIZMOS
    m_pGizmo = new sr::Sphere();
    m_pGizmo->SetColor({0.0f,1.0f,0.0f});
}

sr::Geometry* run::Entity::GetGizmo()
{
    m_pGizmo->SetPosition(GetPosition());
    m_pGizmo->SetRotation(GetRotation());
    return m_pGizmo;
#endif
}
