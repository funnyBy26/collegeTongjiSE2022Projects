//Refactored with State Pattern
//a new class HeroState is created to represent the state of the hero
//the Hero class has a member variable of type HeroState
//the Hero class has a method called setState to set the state of the hero
//the Hero class has a method called update to update the state of the hero
#pragma once
#ifndef __HERO_H__
#define __HERO_H__

#include "cocos2d.h"
#include "showHPMP.h"
#include "Attack.h"
#include "Information.h"
using namespace cocos2d;

class showHPMP;
class Attack;
class Hero;

class HeroState {
public:
    virtual ~HeroState() = default;
    virtual void enter(Hero* hero) = 0;       // ½øÈë×´Ì¬Ê±µÄÂß¼­
    virtual void update(Hero* hero, float dt) = 0; // Ã¿Ö¡¸üÐÂ
    virtual void exit(Hero* hero) = 0;       // Àë¿ª×´Ì¬Ê±µÄÂß¼­
};

// Idle ×´Ì¬
class IdleState : public HeroState {
public:
    void enter(Hero* hero) override;
    void update(Hero* hero, float dt) override;
    void exit(Hero* hero) override;
};

// Move ×´Ì¬
class MoveState : public HeroState {
public:
    void enter(Hero* hero) override;
    void update(Hero* hero, float dt) override;
    void exit(Hero* hero) override;
};

// Attack ×´Ì¬
class AttackState : public HeroState {
public:
    void enter(Hero* hero) override;
    void update(Hero* hero, float dt) override;
    void exit(Hero* hero) override;
};

// Recover ×´Ì¬
class RecoverState : public HeroState {
public:
    void enter(Hero* hero) override;
    void update(Hero* hero, float dt) override;
    void exit(Hero* hero) override;
};

// Dead ×´Ì¬
class DeadState : public HeroState {
public:
    void enter(Hero* hero) override;
    void update(Hero* hero, float dt) override;
    void exit(Hero* hero) override;
};

