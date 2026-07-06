//Refactored with Bridge Pattern
//In this file, the Attack class is defined.  
//The Attack class is a class that represents the attack.
//The Attack class has a method called createBehaviorForHero to create the behavior of the attack. 
#pragma once

#include "cocos2d.h"
#include "Hero.h"
#include "IAttackBehavior.h"

USING_NS_CC;

// Attack class - Bridge Pattern's Abstraction
class Attack : public cocos2d::Sprite {
public:
    // Factory method to create attack behavior based on hero type
    static std::unique_ptr<IAttackBehavior> createBehaviorForHero(
        const std::string& heroName, float range) {
        
        // Create special behaviors for specific heroes
        if (heroName == "Taric") {
            return std::make_unique<TaricBehavior>();
        }
        // other hero-specific behaviors...
        
        // Default behavior based on attack range
        if (range > 200) {
            return std::make_unique<ProjectileBehavior>();
        } else {
            return std::make_unique<MeleeBehavior>();
        }
    }
    
    // Create attack instance
    static Attack* create(const std::string& filename, IAttackBehavior* behavior);
    virtual bool init() override;
    
    // Set initial position of attack
    void SetPosition(Vec2 pos, Size heroSize);

    // Set attack target
    void SetTarget(Hero* target);

    // Set attack power
    void GetAttack(double atk);

    // Timer for updating attack
    void timer(float delta);

    // Update per frame
    void update(float dt) override;

    // Destroy attack object
    void destroy();
    
protected:
    Attack(IAttackBehavior* behavior) : behavior(behavior) {}
    void GetDistance();  // Calculate distance to target
    
private:
    IAttackBehavior* behavior;  // Attack behavior implementation
    Hero* target = nullptr;     // Target hero to attack
    Vec2 targetPos;            // Target position
    Vec2 direction;           // Attack direction
    double attack = 100;      // Attack power
    double distance = 0;      // Distance to target
    bool isHit = false;       // Hit status
    std::string name;         // Attack name/identifier
};