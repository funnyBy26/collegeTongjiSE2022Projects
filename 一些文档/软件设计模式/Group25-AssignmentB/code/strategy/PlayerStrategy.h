/*
* Refactor this code to use the strategy pattern.
* The Player class implements the strategy pattern to manage the player's behavior
* by dynamically setting different strategies. The different management logic of the
* player's gold, health, experience, hero and level are implemented through the strategy
* object to achieve flexible switching in different scenarios.
*/
#pragma once
#include "cocos2d.h"
#include <vector>
#include "NetMessage.h"
#include "Hero.h"
#include "SmallHero.h"
#define MaxLine 8
#define mintag 1
#define maxtag 14
#define MaxHero 9

class HeroStrategy {
public:
    virtual void createHeroes(Player* player) = 0;
    virtual void setHero(Player* player, Hero* hero) = 0;
    virtual bool addHeroToWar(Player* player, Hero& hero) = 0;
    virtual void GetNetHero(Player* player, NetHeroInfo* NetInfo) = 0;
    virtual ~HeroStrategy() = default;
};

class StandardHeroStrategy : public HeroStrategy {
public:
    void createHeroes(Player* player) override;
    void setHero(Player* player, Hero* hero) override;
    bool addHeroToWar(Player* player, Hero& hero) override;
    void GetNetHero(Player* player, NetHeroInfo* NetInfo) override;
};

class GoldStrategy {
public:
    virtual bool hasEnoughGold(int amount) = 0;
    virtual void spendGold(int amount) = 0;
    virtual void addGold(int data) = 0;
    virtual int getGold() = 0;
    virtual ~GoldStrategy() = default;
};

class StandardGoldStrategy : public GoldStrategy {
public:
    bool hasEnoughGold(int amount) override;
    void spendGold(int amount) override;
    void addGold(int data) override;
    int getGold() override;
private:
    int gold = 100;
};


class BloodStrategy {
public:
    virtual void changeBlood(int hurt) = 0;
    virtual int getBlood() = 0;
    virtual ~BloodStrategy() = default;
};

class StandardBloodStrategy : public BloodStrategy {
public:
    void changeBlood(int hurt) override;
    int getBlood() override;
private:
    int playerBlood = 30;
};

class ExperienceStrategy {
public:
    virtual int getExperience() = 0;
    virtual int getNeedExperience() = 0;
    virtual void setNeedExperience(int amount) = 0;
    virtual int setExperience(int amount) = 0;
    virtual ~ExperienceStrategy() = default;
};

class StandardExperienceStrategy : public ExperienceStrategy {
public:
    int getExperience() override;
    int getNeedExperience() override;
    void setNeedExperience(int amount) override;
    int setExperience(int amount) override;
private:
    int playerExperience = 0;
    int playerNeedExperience = 4;
};

class LevelStrategy {
public:
    virtual int getPlayerLevel() = 0;
    virtual void setPlayerLevel(int amount) = 0;
    virtual ~LevelStrategy() = default;
};

class StandardLevelStrategy : public LevelStrategy {
public:
    int getPlayerLevel() override;
    void setPlayerLevel(int amount) override;
private:
    int playerLevel = 1;
};

