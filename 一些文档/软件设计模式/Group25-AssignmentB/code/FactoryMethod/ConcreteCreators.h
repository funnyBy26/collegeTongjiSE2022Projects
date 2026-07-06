//Refactored with Factory Method
//In this file, the ConcreteCreators class is defined.
//The ConcreteCreators class is a class that represents the concrete creators.
//The ConcreteCreators class has a method called createHero to create a hero.
#pragma once
#include "../HeroCreator.h"
#include "../ConcreteHero.h"

// Concrete hero creator(factory)
class TaricCreator : public HeroCreator {
public:
    IHero* createHero(Vec2 pos) override {
        TaricHero* hero = TaricHero::create();
        if (!hero) return nullptr;
        
        hero->setPosition(pos);
        return hero;
    }
};

class AliCreator : public HeroCreator {
public:
    IHero* createHero(Vec2 pos) override {
        AliHero* hero = AliHero::create();
        if (!hero) return nullptr;
        
        hero->setPosition(pos);
        return hero;
    }
};

class AnnyCreator : public HeroCreator {
public:
    IHero* createHero(Vec2 pos) override {
        AnnyHero* hero = AnnyHero::create();
        if (!hero) return nullptr;
        
        hero->setPosition(pos);
        return hero;
    }
};

class AliceCreator : public HeroCreator {
public:
    IHero* createHero(Vec2 pos) override {
        AliceHero* hero = AliceHero::create();
        if (!hero) return nullptr;
        
        hero->setPosition(pos);
        return hero;
    }
};

class NamiCreator : public HeroCreator {
public:
    IHero* createHero(Vec2 pos) override {
        NamiHero* hero = NamiHero::create();
        if (!hero) return nullptr;
        
        hero->setPosition(pos);
        return hero;
    }
};

class ErliusCreator : public HeroCreator {
public:
    IHero* createHero(Vec2 pos) override {
        ErliusHero* hero = ErliusHero::create();
        if (!hero) return nullptr;
        
        hero->setPosition(pos);
        return hero;
    }
};

class KasiaCreator : public HeroCreator {
public:
    IHero* createHero(Vec2 pos) override {
        KasiaHero* hero = KasiaHero::create();
        if (!hero) return nullptr;
        
        hero->setPosition(pos);
        return hero;
    }
};

class LiliaCreator : public HeroCreator {
public:
    IHero* createHero(Vec2 pos) override {
        LiliaHero* hero = LiliaHero::create();
        if (!hero) return nullptr;
        
        hero->setPosition(pos);
        return hero;
    }
};

class KuqiCreator : public HeroCreator {
public:
    IHero* createHero(Vec2 pos) override {
        KuqiHero* hero = KuqiHero::create();
        if (!hero) return nullptr;
        
        hero->setPosition(pos);
        return hero;
    }
};

class KennenCreator : public HeroCreator {
public:
    IHero* createHero(Vec2 pos) override {
        KennenHero* hero = KennenHero::create();
        if (!hero) return nullptr;
        
        hero->setPosition(pos);
        return hero;
    }
};

class ChuishiCreator : public HeroCreator {
public:
    IHero* createHero(Vec2 pos) override {
        ChuishiHero* hero = ChuishiHero::create();
        if (!hero) return nullptr;
        
        hero->setPosition(pos);
        return hero;
    }
};

class SertiCreator : public HeroCreator {
public:
    IHero* createHero(Vec2 pos) override {
        SertiHero* hero = SertiHero::create();
        if (!hero) return nullptr;
        
        hero->setPosition(pos);
        return hero;
    }
};

class KaterinaCreator : public HeroCreator {
public:
    IHero* createHero(Vec2 pos) override {
        KaterinaHero* hero = KaterinaHero::create();
        if (!hero) return nullptr;
        
        hero->setPosition(pos);
        return hero;
    }
};

class EvelynnCreator : public HeroCreator {
public:
    IHero* createHero(Vec2 pos) override {
        EvelynnHero* hero = EvelynnHero::create();
        if (!hero) return nullptr;
        
        hero->setPosition(pos);
        return hero;
    }
};
