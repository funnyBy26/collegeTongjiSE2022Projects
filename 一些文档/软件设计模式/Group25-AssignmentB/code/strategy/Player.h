/*
* Refactor this code to use the strategy pattern.
* The Player class implements the strategy pattern to manage the player's behavior
* by dynamically setting different strategies. The different management logic of the
* player's gold, health, experience, hero and level are implemented through the strategy
* object to achieve flexible switching in different scenarios.
*/
#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "cocos2d.h"
#include <vector>
#include "NetMessage.h"
#include "Hero.h"
#include "SmallHero.h"
#include "PlayerStrategy.h"
#define MaxLine 8
#define mintag 1
#define maxtag 14
#define MaxHero 9
USING_NS_CC;

constexpr int initplayerBlood = 100;
constexpr int addExperience = 4;
constexpr int addMaxExperience = 4;

struct site {
    int x;
    int y;
};

struct NetHeroInfo;

class Player :public Sprite
{
public:
    friend class StandardHeroStrategy;
    friend class StandardSmallHeroStrategy;

    CREATE_FUNC(Player);
    static Player* createSprite();
    virtual bool init();
    ~Player();

    // Set different policies
    void setGoldStrategy(std::shared_ptr<GoldStrategy> strategy);
    void setBloodStrategy(std::shared_ptr<BloodStrategy> strategy);
    void setExperienceStrategy(std::shared_ptr<ExperienceStrategy> strategy);
    void setHeroStrategy(std::shared_ptr<HeroStrategy> strategy);
    void setLevelStrategy(std::shared_ptr<LevelStrategy> strategy);

    // Policy override function
    void CreateHero();
    void SetHero(Hero* hero);
    void GetNetHero(NetHeroInfo* NetInfo);
    bool addHeroToWar(Hero& hero);
    //
    bool hasEnoughGold(int amount);
    void spendGold(int amount);
    int  getGold();
    void addGold(int data);
    //
    void changeplayerBlood(int hurt);
    int GetPlayerBlood();
    //
    int GetplayerExperience();
    void SetplayerExperience(int x);
    int GetplayerNeedExperience();
    void SetplayerNeedExperience(int x);
    //
    int GetplayerLevel();
    void SetplayerLevel(int x);
    // Other functions
    void SetHeroNum(int data);
    Hero* GetWarHero();
    int GetHeroNum();
    void SetSmallHero(Vec2 pos, bool enabled);
    bool IsDead();
    SmallHero* getSmallHero();
    void Restart();
    void clearWarPlayer();
protected:
    bool playerIsDead;
    SmallHero* smallHero;
    Hero chessWarPlayer[MaxHero];
    int heroNum = 0;
    Vec2 frontPos[MaxLine];
    Vec2 backPos[MaxLine * 2];
private:
    // Strategy objects managed via smart pointers
    std::shared_ptr<GoldStrategy> goldStrategy;
    std::shared_ptr<BloodStrategy> bloodStrategy;
    std::shared_ptr<ExperienceStrategy> experienceStrategy;
    std::shared_ptr<HeroStrategy> heroStrategy;
    std::shared_ptr<LevelStrategy> levelStrategy;
};
#endif