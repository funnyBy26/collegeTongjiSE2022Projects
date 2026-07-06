/*
* Refactor this code to use the strategy pattern.
* The Player class implements the strategy pattern to manage the player's behavior
* by dynamically setting different strategies. The different management logic of the
* player's gold, health, experience, hero and level are implemented through the strategy
* object to achieve flexible switching in different scenarios.
*/
#include "PlayerStrategy.h"

void StandardHeroStrategy::createHeroes(Player* player) {
    Vec2 pos1 = Vec2(600, 550);
    for (int i = 1; i <= MaxLine; i++) {
        player->frontPos[i] = pos1;
        pos1.x += 100;
    }
    Vec2 pos2 = Vec2(600, 650);
    for (int i = 1; i <= MaxLine; i++) {
        player->backPos[i] = pos2;
        pos2.x += 100;
    }

    pos2.x = 600, pos2.y += 100;
    for (int i = MaxLine + 1; i <= 2 * MaxLine; i++) {
        player->backPos[i] = pos2;
        pos2.x += 100;
    }

    if (player->heroNum >= player->GetplayerLevel()) {
        return;
    }

    srand((unsigned int)time(NULL));
    Vec2 pos;
    std::unordered_map<int, Vec2> existBackPos;
    std::unordered_map<int, Vec2> existFrontPos;
    for (int i = player->heroNum; i < player->GetplayerLevel(); i++) {
        int tag = mintag + rand() % (maxtag - mintag + 1);
        if (tag >= 1 && tag <= 8) {
            while (1) {
                int x = rand() % (2 * MaxLine) + 1;
                if (existBackPos.count(x) == 0) {
                    pos = player->backPos[x];
                    existBackPos[x] = pos;
                    break;
                }
            }
        }
        else {
            while (1) {
                int x = rand() % (MaxLine)+1;
                if (existFrontPos.count(x) == 0) {
                    pos = player->frontPos[x];
                    existFrontPos[x] = pos;
                    break;
                }
            }
        }
        Hero* AIhero = Hero::create();
        AIhero->SetHeroDataByTag(tag, pos);
        AIhero->ChangeHeroName("En-");
        player->SetHero(AIhero);
    }
}

bool StandardHeroStrategy::addHeroToWar(Player* player, Hero& hero){
    if (player->GetHeroNum() >= MaxHero) {
        CCLOG("Cannot add more heroes. Maximum hero limit reached.");
        return false;
    }

    player->chessWarPlayer[player->GetHeroNum()].SetHeroDataByTag(hero.getTag(), hero.GetHeroPos());
    player->chessWarPlayer[player->GetHeroNum()].setLevel(hero.getLevel());
    player->chessWarPlayer[player->GetHeroNum()].SetOn(1);
    player->SetHeroNum(player->GetHeroNum() + 1);
    return true;
}

void StandardHeroStrategy::setHero(Player* player, Hero* hero){
    player->chessWarPlayer[player->heroNum].SetBaseInfo(hero->GetBaseInfo(), hero->GetName(), hero->GetHeroPos());
    player->chessWarPlayer[player->heroNum].SetOn(1);
    player->heroNum++;
}

void StandardHeroStrategy::GetNetHero(Player* player, NetHeroInfo* NetInfo) {
    for (int i = 0; i < player->GetHeroNum(); i++) {
        Hero* netHero = Hero::create();
        netHero->SetHeroDataByTag(NetInfo[i].tag, Vec2(NetInfo[i].posX, NetInfo[i].posY));
        netHero->ChangeHeroName("En-");

        player->chessWarPlayer[i].SetBaseInfo(netHero->GetBaseInfo(), netHero->GetName(), netHero->GetHeroPos());
        player->chessWarPlayer[i].setLevel(NetInfo[i].level);
        player->chessWarPlayer[i].SetOn(1);
    }
}

bool StandardGoldStrategy::hasEnoughGold(int amount) {
    return gold >= amount;
}

void StandardGoldStrategy::spendGold(int amount) {
    gold -= amount;
}

void StandardGoldStrategy::addGold(int data){
    gold += data;
}

int StandardGoldStrategy::getGold(){
    return gold;
}

void StandardBloodStrategy::changeBlood(int hurt){
    playerBlood -= hurt;
}

int StandardBloodStrategy::getBlood(){
    return playerBlood;
}

int StandardExperienceStrategy::getExperience() {
    return playerExperience;
}

int StandardExperienceStrategy::getNeedExperience(){
    return playerNeedExperience;
}

void StandardExperienceStrategy::setNeedExperience(int amount) {
    playerNeedExperience = amount;
}

int StandardExperienceStrategy::setExperience(int amount){
    playerExperience = amount;
}

int StandardLevelStrategy::getPlayerLevel() {
    return playerLevel;
}

void StandardLevelStrategy::setPlayerLevel(int amount) {
    playerLevel = amount;
    if (amount > 9)
        playerLevel = 9;
}