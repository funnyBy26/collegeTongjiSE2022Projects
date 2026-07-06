//Refactored with Factory Method   
//In this file, the ConcreteHero class is defined.
//The ConcreteHero class is a class that represents the concrete hero.
//The ConcreteHero class has a method called create to create a hero.
#pragma once
#include "Hero.h"

// Concrete Hero(product)
class TaricHero : public Hero {
public:
    static TaricHero* create() {
        // get data from Information class
        std::string imagePath = Information::getHeroPathByTag(1);
        TaricHero* hero = new TaricHero();
        
        if (hero && hero->Hero::create(imagePath)) {
            hero->autorelease();
            
            heroInformation* info = Information::GetHeroBaseInfo(1);
            if (!info) {
                CC_SAFE_DELETE(hero);
                return nullptr;
            }

            hero->setId(1);
            hero->SetBaseInfo(info, Information::getNameByTag(1), Vec2::ZERO);
            hero->HPInit();
            
            return hero;
        }
        CC_SAFE_DELETE(hero);
        return nullptr;
    }
};

class AliHero : public Hero {
public:
    static AliHero* create() {
        // get data from Information class
        std::string imagePath = Information::getHeroPathByTag(2);
        TaricHero* hero = new TaricHero();
        
        if (hero && hero->Hero::create(imagePath)) {
            hero->autorelease();
            
            heroInformation* info = Information::GetHeroBaseInfo(2);
            if (!info) {
                CC_SAFE_DELETE(hero);
                return nullptr;
            }

            hero->setId(2);
            hero->SetBaseInfo(info, Information::getNameByTag(2), Vec2::ZERO);
            hero->HPInit();
            
            return hero;
        }
        CC_SAFE_DELETE(hero);
        return nullptr;
    }
};

class AnnyHero : public Hero {
public:
    static AnnyHero* create() {
        // get data from Information class
        std::string imagePath = Information::getHeroPathByTag(3);
        AnnyHero* hero = new AnnyHero();
        
        if (hero && hero->Hero::create(imagePath)) {
            hero->autorelease();
            
            heroInformation* info = Information::GetHeroBaseInfo(3);
            if (!info) {
                CC_SAFE_DELETE(hero);
                return nullptr;
            }

            hero->setId(3);
            hero->SetBaseInfo(info, Information::getNameByTag(3), Vec2::ZERO);
            hero->HPInit();
            
            return hero;
        }
        CC_SAFE_DELETE(hero);
        return nullptr;
    }
};

class AliceHero : public Hero {
public:
    static AliceHero* create() {
        // get data from Information class
        std::string imagePath = Information::getHeroPathByTag(4);
        AliceHero* hero = new AliceHero();
        
        if (hero && hero->Hero::create(imagePath)) {
            hero->autorelease();
            
            heroInformation* info = Information::GetHeroBaseInfo(4);
            if (!info) {
                CC_SAFE_DELETE(hero);
                return nullptr;
            }

            hero->setId(4);
            hero->SetBaseInfo(info, Information::getNameByTag(4), Vec2::ZERO);
            hero->HPInit();
            
            return hero;
        }
        CC_SAFE_DELETE(hero);
        return nullptr;
    }
};

class NamicHero : public Hero {
public:
    static NamiHero* create() {
        // get data from Information class
        std::string imagePath = Information::getHeroPathByTag(5);
        NamiHero* hero = new NamiHero();
        
        if (hero && hero->Hero::create(imagePath)) {
            hero->autorelease();
            
            heroInformation* info = Information::GetHeroBaseInfo(5);
            if (!info) {
                CC_SAFE_DELETE(hero);
                return nullptr;
            }

            hero->setId(5);
            hero->SetBaseInfo(info, Information::getNameByTag(5), Vec2::ZERO);
            hero->HPInit();
            
            return hero;
        }
        CC_SAFE_DELETE(hero);
        return nullptr;
    }
};

class ErliusHero : public Hero {
public:
    static ErliusHero* create() {
        // get data from Information class
        std::string imagePath = Information::getHeroPathByTag(6);
        ErliusHero* hero = new ErliusHero();
        
        if (hero && hero->Hero::create(imagePath)) {
            hero->autorelease();
            
            heroInformation* info = Information::GetHeroBaseInfo(6);
            if (!info) {
                CC_SAFE_DELETE(hero);
                return nullptr;
            }

            hero->setId(6);
            hero->SetBaseInfo(info, Information::getNameByTag(6), Vec2::ZERO);
            hero->HPInit();
            
            return hero;
        }
        CC_SAFE_DELETE(hero);
        return nullptr;
    }
};

class KasiaHero : public Hero {
public:
    static KasiaHero* create() {
        // get data from Information class
        std::string imagePath = Information::getHeroPathByTag(7);
        KasiaHero* hero = new KasiaHero();
        
        if (hero && hero->Hero::create(imagePath)) {
            hero->autorelease();
            
            heroInformation* info = Information::GetHeroBaseInfo(7);
            if (!info) {
                CC_SAFE_DELETE(hero);
                return nullptr;
            }

            hero->setId(7);
            hero->SetBaseInfo(info, Information::getNameByTag(7), Vec2::ZERO);
            hero->HPInit();
            
            return hero;
        }
        CC_SAFE_DELETE(hero);
        return nullptr;
    }
};

class LiliaHero : public Hero {
public:
    static LiliaHero* create() {
        // get data from Information class
        std::string imagePath = Information::getHeroPathByTag(8);
        LiliaHero* hero = new LiliaHero();
        
        if (hero && hero->Hero::create(imagePath)) {
            hero->autorelease();
            
            heroInformation* info = Information::GetHeroBaseInfo(8);
            if (!info) {
                CC_SAFE_DELETE(hero);
                return nullptr;
            }

            hero->setId(8);
            hero->SetBaseInfo(info, Information::getNameByTag(8), Vec2::ZERO);
            hero->HPInit();
            
            return hero;
        }
        CC_SAFE_DELETE(hero);
        return nullptr;
    }
};

class KuqiHero : public Hero {
public:
    static KuqiHero* create() {
        // get data from Information class
        std::string imagePath = Information::getHeroPathByTag(9);
        KuqiHero* hero = new KuqiHero();
        
        if (hero && hero->Hero::create(imagePath)) {
            hero->autorelease();
            
            heroInformation* info = Information::GetHeroBaseInfo(9);
            if (!info) {
                CC_SAFE_DELETE(hero);
                return nullptr;
            }

            hero->setId(9);
            hero->SetBaseInfo(info, Information::getNameByTag(9), Vec2::ZERO);
            hero->HPInit();
            
            return hero;
        }
        CC_SAFE_DELETE(hero);
        return nullptr;
    }
};

class KennenHero : public Hero {
public:
    static KennenHero* create() {
        // get data from Information class
        std::string imagePath = Information::getHeroPathByTag(10);
        KennenHero* hero = new KennenHero();
        
        if (hero && hero->Hero::create(imagePath)) {
            hero->autorelease();
            
            heroInformation* info = Information::GetHeroBaseInfo(10);
            if (!info) {
                CC_SAFE_DELETE(hero);
                return nullptr;
            }

            hero->setId(10);
            hero->SetBaseInfo(info, Information::getNameByTag(10), Vec2::ZERO);
            hero->HPInit();
            
            return hero;
        }
        CC_SAFE_DELETE(hero);
        return nullptr;
    }
};

class ChuishiHero : public Hero {
public:
    static ChuishiHero* create() {
        // get data from Information class
        std::string imagePath = Information::getHeroPathByTag(11);
        ChuishiHero* hero = new ChuishiHero();
        
        if (hero && hero->Hero::create(imagePath)) {
            hero->autorelease();
            
            heroInformation* info = Information::GetHeroBaseInfo(11);
            if (!info) {
                CC_SAFE_DELETE(hero);
                return nullptr;
            }

            hero->setId(11);
            hero->SetBaseInfo(info, Information::getNameByTag(11), Vec2::ZERO);
            hero->HPInit();
            
            return hero;
        }
        CC_SAFE_DELETE(hero);
        return nullptr;
    }
};

class SertiHero : public Hero {
public:
    static SertiHero* create() {
        // get data from Information class
        std::string imagePath = Information::getHeroPathByTag(12);
        SertiHero* hero = new SertiHero();
        
        if (hero && hero->Hero::create(imagePath)) {
            hero->autorelease();
            
            heroInformation* info = Information::GetHeroBaseInfo(12);
            if (!info) {
                CC_SAFE_DELETE(hero);
                return nullptr;
            }

            hero->setId(12);
            hero->SetBaseInfo(info, Information::getNameByTag(12), Vec2::ZERO);
            hero->HPInit();
            
            return hero;
        }
        CC_SAFE_DELETE(hero);
        return nullptr;
    }
};

class KaterinaHero : public Hero {
public:
    static KaterinaHero* create() {
        // get data from Information class
        std::string imagePath = Information::getHeroPathByTag(13);
        KaterinaHero* hero = new KaterinaHero();
        
        if (hero && hero->Hero::create(imagePath)) {
            hero->autorelease();
            
            heroInformation* info = Information::GetHeroBaseInfo(133);
            if (!info) {
                CC_SAFE_DELETE(hero);
                return nullptr;
            }

            hero->setId(13);
            hero->SetBaseInfo(info, Information::getNameByTag(13), Vec2::ZERO);
            hero->HPInit();
            
            return hero;
        }
        CC_SAFE_DELETE(hero);
        return nullptr;
    }
};

class EvelynnHero : public Hero {
public:
    static EvelynnHero* create() {
        // get data from Information class
        std::string imagePath = Information::getHeroPathByTag(14);
        EvelynnHero* hero = new EvelynnHero();
        
        if (hero && hero->Hero::create(imagePath)) {
            hero->autorelease();
            
            heroInformation* info = Information::GetHeroBaseInfo(14);
            if (!info) {
                CC_SAFE_DELETE(hero);
                return nullptr;
            }

            hero->setId(14);
            hero->SetBaseInfo(info, Information::getNameByTag(14), Vec2::ZERO);
            hero->HPInit();
            
            return hero;
        }
        CC_SAFE_DELETE(hero);
        return nullptr;
    }
};

// ... other hero types