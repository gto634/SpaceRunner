#include "Character.h"

#include <algorithm>

#include "MathsUtils.hpp"

void run::Character::Move(sr::Vector3& direction,float32 deltatime, float32 boundary)
{
    sr::Vector3 characterPos = GetPosition();
    characterPos += direction.SelfNormalize() * m_speed * deltatime;
    sr::Vector3 newPos = {std::clamp(characterPos.x, -boundary, boundary), std::clamp(characterPos.y, -boundary, boundary), characterPos.z, };
    SetPosition(newPos);
}

void run::Character::Rotate(sr::Vector3& direction, float32 deltatime)
{
    sr::Vector3 playerGoal = Lerp( GetRotation() * RAD2DEG , direction, min(deltatime, 1.0f));
    SetRotation(playerGoal);
}

bool run::Character::IsColliding(sr::Vector3 const& position, float32 radius)
{
    sr::Vector3 playerDir = GetPosition();
    sr::Vector3 distance = position - playerDir;
    float32 norm = distance.x * distance.x + distance.y * distance.y + distance.z * distance.z;
    
    return norm <= (m_radius * m_radius + radius * radius);
}
