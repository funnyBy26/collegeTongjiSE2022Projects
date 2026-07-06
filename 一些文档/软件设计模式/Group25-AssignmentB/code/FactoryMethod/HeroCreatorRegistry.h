//Refactored with Factory Method
//In this file, the HeroCreatorRegistry class is implemented.
//The HeroCreatorRegistry class is a factory class that creates heroes.
//The HeroCreatorRegistry class has a method called getCreator to get the creator of the hero.
#pragma once
#include "Creators/ConcreteCreators.h"

// Factory registry
class HeroCreatorRegistry {
public:
    static HeroCreator* getCreator(int heroTag) {
        switch (heroTag) {
            case 1: return new TaricCreator();
            case 2: return new AliCreator();
            case 3: return new AnnyCreator();
            case 4: return new AliceCreator();
            case 5: return new NamiCreator();
            case 6: return new ErliusCreator();
            case 7: return new KasiaCreator();
            case 8: return new LiliaCreator();
            case 9: return new KuqiCreator();
            case 10: return new KennenCreator();
            case 11: return new ChuishiCreator();
            case 12: return new SertiCreator();
            case 13: return new KaterinaCreator();
            case 14: return new EvelynnCreator();
            // ... other hero creators
            default: return nullptr;
        }
    }
}; 