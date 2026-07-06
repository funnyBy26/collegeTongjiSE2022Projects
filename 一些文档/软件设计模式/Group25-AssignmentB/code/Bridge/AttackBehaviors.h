//Refactored with Bridge Pattern
//In this file, the AttackBehaviors class is defined.
//The AttackBehaviors class is a class that represents the attack behaviors.
//The AttackBehaviors class has a method called createBehaviorForHero to create the behavior of the attack. 
#pragma once
#include "IAttackBehavior.h"

// Base attack behavior - Bridge Pattern's Concrete Implementor
class BaseAttackBehavior : public IAttackBehavior {
protected:
    float hitRange;    // Range within which attack hits
    float moveSpeed;   // Movement speed of attack
    
public:
    BaseAttackBehavior(float range, float speed) 
        : hitRange(range), moveSpeed(speed) {}
    
    // Basic linear movement implementation
    virtual void move(Vec2& currentPos, const Vec2& targetPos) override {
        Vec2 direction = (targetPos - currentPos).getNormalized();
        currentPos += direction * moveSpeed;
    }
    
    // Basic hit check implementation
    virtual bool checkHit(float distance) override {
        return distance <= hitRange;
    }
    
    float getHitRange() const override { return hitRange; }
    float getMoveSpeed() const override { return moveSpeed; }
};


// Sub attack behavior - Bridge Pattern's Concrete Implementor

// Ranged projectile attack behavior
class ProjectileBehavior : public BaseAttackBehavior {
public:
    // Default ranged attack with longer range but slower speed
    ProjectileBehavior() : BaseAttackBehavior(70.0f, 1.0f/8) {}
};

// Melee attack behavior
class MeleeBehavior : public BaseAttackBehavior {
public:
    // Default melee attack with shorter range but faster speed
    MeleeBehavior() : BaseAttackBehavior(50.0f, 1.0f/4) {}
};

// Hero-specific attack behaviors
class TaricBehavior : public BaseAttackBehavior {
public:
    // Taric's unique attack properties
    TaricBehavior() : BaseAttackBehavior(80.0f, 1.0f/6) {}
    
    void move(Vec2& currentPos, const Vec2& targetPos) override {
        // Taric's special movement pattern
        BaseAttackBehavior::move(currentPos, targetPos);
        // Add special effects...
    }
}; 
// other heroes' attack behaviors...