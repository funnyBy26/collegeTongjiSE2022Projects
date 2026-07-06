/* Refactered with Bridge Pattern */
#pragma once
#include "cocos2d.h"
USING_NS_CC;

// Attack behavior interface - Bridge Pattern's Implementor
class IAttackBehavior {
public:
    virtual ~IAttackBehavior() = default;

    // Handle attack movement
    // @param currentPos Current position, will be updated
    // @param targetPos Target position to move towards
    virtual void move(Vec2& currentPos, const Vec2& targetPos) = 0;

    // Check if attack hits target
    // @param distance Current distance to target
    // @return true if hit, false otherwise
    virtual bool checkHit(float distance) = 0;

    // Get attack's hit range
    // @return Hit range in pixels
    virtual float getHitRange() const = 0;

    // Get movement speed
    // @return Movement speed in pixels/frame
    virtual float getMoveSpeed() const = 0;
}; 