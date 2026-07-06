//Refactored with Facade Pattern
//a new file created
//In this file, the BattleSystemFacade class is refactored to implement the Facade pattern.
#include "BattleSystemFacade.h"

//the startNewBattle() function is used to start a new battle.
//it first checks if there is a current battle, if there is, it ends the current battle.
//then it creates a new battle and sets the players.
//then it starts the battle.
//finally, it adds the battle to the scene.
bool BattleSystemFacade::startNewBattle(Player* player1, Player* player2, Scene* scene) {
    if (currentBattle) {
        endCurrentBattle();
    }
    
    currentBattle = Battle::create();
    if (!currentBattle) return false;
    
    currentBattle->setPlayers(player1, player2);
    currentBattle->setupHeroes();
    currentBattle->startBattle();
    
    if (scene) {
        scene->addChild(currentBattle);
    }
    
    return true;
}

//the endCurrentBattle() function is used to end the current battle.
//it first checks if there is a current battle, if there is, it ends the current battle.
//then it removes the battle from the scene.
void BattleSystemFacade::endCurrentBattle() {
    if (currentBattle) {
        currentBattle->endBattle();
        currentBattle->removeFromParent();
        currentBattle = nullptr;
    }
}

//the isBattleInProgress() function is used to check if the battle is in progress.
//it returns true if there is a current battle and the battle is not over.
bool BattleSystemFacade::isBattleInProgress() const {
    return currentBattle && !currentBattle->isGameOver();
}

//the executeAttack() function is used to execute the attack.
//it first checks if there is a current battle, if there is, it sets the attack targets.
void BattleSystemFacade::executeAttack(Hero** attackers, Hero** targets, int attackerCount, int targetCount) {
    if (currentBattle) {
        currentBattle->setAttackTargets(attackers, targets, attackerCount, targetCount);
    }
}

//the updateBattleTargets() function is used to update the battle targets.
//it first checks if there is a current battle, if there is, it updates the targets.
void BattleSystemFacade::updateBattleTargets(Hero** attackers, Hero** targets, int attackerCount, int targetCount) {
    if (currentBattle) {
        currentBattle->updateTargets(attackers, targets, attackerCount, targetCount);
    }
}

//the resetBattleField() function is used to reset the battle field.
//it first checks if there is a current battle, if there is, it resets the heroes.
void BattleSystemFacade::resetBattleField() {
    if (currentBattle) {
        currentBattle->resetHeroes();
    }
}

//the healHeroes() function is used to heal the heroes.
//it first checks if there is a current battle, if there is, it heals the heroes.   
void BattleSystemFacade::healHeroes(Hero** heroes, int count, double amount) {
    if (currentBattle) {
        currentBattle->recoverHeroes(heroes, count, amount);
    }
}

//the getFirstPlayer() function is used to get the first player.
//it returns the first player of the current battle.
Player* BattleSystemFacade::getFirstPlayer() const {
    return currentBattle ? currentBattle->getFirstPlayer() : nullptr;
}

//the getSecondPlayer() function is used to get the second player.
//it returns the second player of the current battle.
Player* BattleSystemFacade::getSecondPlayer() const {
    return currentBattle ? currentBattle->getSecondPlayer() : nullptr;
}

//the isReadyForNextRound() function is used to check if the battle is ready for the next round.
//it returns true if there is a current battle and the battle is ready for the next round.
bool BattleSystemFacade::isReadyForNextRound() const {
    return currentBattle ? currentBattle->isNextRound() : false;
}

//the updateBattle() function is used to update the battle.
//it first checks if there is a current battle, if there is, it updates the battle.
void BattleSystemFacade::updateBattle(float dt) {
    if (currentBattle) {
        currentBattle->update(dt);
    }
} 