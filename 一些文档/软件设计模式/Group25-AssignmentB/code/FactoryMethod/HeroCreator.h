//Refactored with Factory Method
//In this file, the HeroCreator class is defined.
//The HeroCreator class is a factory class that creates heroes.
//The HeroCreator class has a method called createHero to create a hero.
#pragma once
#include "Hero.h"
#include "Information.h"

// Hero Creater(factory) 
class HeroCreator {
public:
    virtual ~HeroCreator() = default;
    
    virtual IHero* createHero(Vec2 pos) = 0;
}; 