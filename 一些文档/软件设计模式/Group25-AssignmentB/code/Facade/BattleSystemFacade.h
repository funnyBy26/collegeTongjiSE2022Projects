//Refactored with Facade Pattern
//a new file created
//In this file, the BattleSystemFacade class is refactored to use the Facade pattern.
//The BattleSystemFacade class is responsible for controlling the battle flow without exposing the internal details of the battle.
//it is a singleton class, and the instance is created by the getInstance() function.

#ifndef __BATTLE_SYSTEM_FACADE_H__
#define __BATTLE_SYSTEM_FACADE_H__

#include "Battle.h"
#include "cocos2d.h"
#include "Player.h"
#include "Hero.h"

USING_NS_CC;

class BattleSystemFacade {
public:
    static BattleSystemFacade* getInstance() {
        static BattleSystemFacade instance;
        return &instance;
    }
    
    // core battle flow control
    bool startNewBattle(Player* player1, Player* player2, Scene* scene);
    void endCurrentBattle();
    bool isBattleInProgress() const;
    bool isReadyForNextRound() const;
    
    // battle operations
    void executeAttack(Hero** attackers, Hero** targets, int attackerCount, int targetCount);
    void updateBattleTargets(Hero** attackers, Hero** targets, int attackerCount, int targetCount);
    void resetBattleField();
    void healHeroes(Hero** heroes, int count, double amount);
    
    // status query
    Player* getFirstPlayer() const;
    //the getSecondPlayer() function is used to get the second player.
    Player* getSecondPlayer() const;
    
    //the updateBattle() function is used to update the battle. 
    void updateBattle(float dt);

private:
    Battle* currentBattle{nullptr};//the currentBattle variable is used to store the current battle.
    
    BattleSystemFacade() = default;
    BattleSystemFacade(const BattleSystemFacade&) = delete;
    BattleSystemFacade& operator=(const BattleSystemFacade&) = delete;
};

#endif 