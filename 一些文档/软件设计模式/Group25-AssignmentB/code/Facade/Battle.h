#pragma once
//Refactored with Facade Pattern
//In this file, the Battle class is refactored to use the Facade pattern.
//The Battle class is now a friend class of the BattleSystemFacade class,
//and the BattleSystemFacade class is responsible for controlling the battle flow.
//However, we still refactory some other parts of the code to make it more readable and maintainable.
//For example, we use the singleton pattern to ensure that there is only one instance of the BattleSystemFacade class.
//and we edit some variable and function names to make it more readable.

#ifndef __BATTLE_H__
#define __BATTLE_H__

#include "cocos2d.h"
#include "Hero.h"
#include "Player.h"
#include "MapScene.h"
#define MaxRow 3
#define MaxCol 6
#define MaxHero 9
#define MaxDis 1000000

USING_NS_CC;

struct site;
class Player;
//Refactored with Facade Pattern

class BattleSystemFacade;  // forward declaration

class Battle : public Layer {
    friend class BattleSystemFacade;  // add: friend declaration

public:
    CREATE_FUNC(Battle);
    virtual bool init();
    static Battle* createLayer();
    bool startBattle();
    void setPlayers(Player* my, Player* en);
    void setupHeroes();
    bool isGameOver();
    bool isNextRound();
    bool isInProgress() const;

protected:
    // battle system internal methods
    void setAttackTargets(Hero** atk, Hero** tar, int atkNum, int tarNum);
    void updateTargets(Hero** atk, Hero** tar, int atkNum, int tarNum);
    void resetHeroes();
    void endBattle();
    void recoverHeroes(Hero** hero, int num, double data);
    double countDistance(Vec2 pos1, Vec2 pos2);
    virtual void update(float dt);
    void updateHeroStates();
    void checkBattleEnd();
    void Destory();
    
    // status query
    Player* getFirstPlayer() const;
    Player* getSecondPlayer() const;

private:
    Hero* self[MaxHero];
    Hero* enemy[MaxHero];
    site* myPos;
    site* enPos;
    Player* myPlayer;
    Player* enPlayer;
    int myHeroNum;
    int enHeroNum;
    int myLive;
    int enLive;
    bool isNext = false;
};

#endif