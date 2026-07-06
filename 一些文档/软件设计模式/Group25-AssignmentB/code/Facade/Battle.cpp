#include "Battle.h"
//Mainly refactored with Lazy Loading Pattern
//In this file, the Battle class is refactored to use the Lazy Loading pattern.
//We use the Lazy Loading pattern to load the heroes only when they are needed.
//This is to improve the performance of the game.
//We also edit some variable and function names to make it more readable and maintainable.
bool Battle::init() {
	if (!Layer::init())
		return false;
	
	// Initialize hero arrays
	for (int i = 0; i < MaxHero; i++) {
		self[i] = Hero::create();
		this->addChild(self[i], 2);
		self[i]->HPInit();
		
		enemy[i] = Hero::create();
		this->addChild(enemy[i], 1);
		enemy[i]->HPInit();
	}
	return true;
}
Battle* Battle::createLayer() {
	return Battle::create();
}

void Battle::setPlayers(Player* my, Player* en) {
	myPlayer = my;
	enPlayer = en;
}
bool Battle::startBattle() {
	if (!myPlayer || !enPlayer) return false;
	
	if (!this->isGameOver()) {
		this->setVisible(1);
		this->setAttackTargets(self, enemy, myHeroNum, enHeroNum);
		this->setAttackTargets(enemy, self, enHeroNum, myHeroNum);
		this->scheduleUpdate();
	}
	return true;
}
void Battle::setupHeroes() {
	myHeroNum = myPlayer->GetHeroNum();
	enHeroNum = enPlayer->GetHeroNum();
	
	// Load player's heroes with lazy loading
	for (int i = 0; i < myHeroNum; i++) {
		if(!self[i]){//Lazy loading if the hero hasn't been created yet
			self[i] = Hero::create();
			this->addChild(self[i], 2);
			self[i]->HPInit();
			self[i]->SetHeroDataByTag(myPlayer->GetWarHero()[i].getTag(), 
								 myPlayer->GetWarHero()[i].GetHeroPos());
			self[i]->setLevel(myPlayer->GetWarHero()[i].getLevel());
			self[i]->updateInfo();
			self[i]->SetDead(0);
			self[i]->setVisible(1);
			self[i]->SetHeroOn();
			self[i]->setScale(0.45);
			self[i]->retain();//Retain to prevent memory issues
		}
	}
	
	// Load enemy heroes with lazy loading
	for (int i = 0; i < enHeroNum; i++) {
		if(!enemy[i]){//Lazy loading if the hero hasn't been created yet
			enemy[i] = Hero::create();
			this->addChild(enemy[i], 1);
			enemy[i]->HPInit();
			enemy[i]->SetBaseInfo(enPlayer->GetWarHero()[i].GetBaseInfo(),
								enPlayer->GetWarHero()[i].GetName(),
								enPlayer->GetWarHero()[i].GetHeroPos());
			enemy[i]->setLevel(enPlayer->GetWarHero()[i].getLevel());
			enemy[i]->updateInfo();
			enemy[i]->SetDead(0);
			enemy[i]->setVisible(1);
			enemy[i]->SetHeroOn();
			enemy[i]->setScale(0.45);
			enemy[i]->retain();//Retain to prevent memory issues
		}
	}
}

void Battle::endBattle() {
	this->unscheduleUpdate();
	if (isGameOver() == 1) {  // My side wins
		int hurt = myLive * 2 + 8;
		enPlayer->changeplayerBlood(hurt);
		enPlayer->addGold(50);
		myPlayer->addGold(100);
	} else if (isGameOver() == 2) {  // Enemy side wins
		int hurt = enLive * 2 + 8;
		myPlayer->changeplayerBlood(hurt);
		myPlayer->addGold(50);
		enPlayer->addGold(100);
	}
	
	MoveBy* stop = MoveBy::create(2, Vec2(0, 0));
	this->runAction(stop);
	this->Destory();
	this->setVisible(false);
	isNext = true;
}

void Battle::update(float dt) {
	if (!isInProgress()) return;
	
	updateHeroStates();
	checkBattleEnd();
}

//Refactored with LazyLoading Pattern
void Battle::setAttackTargets(Hero** attackers, Hero** targets, int attackerCount, int targetCount) {
	double minDistance = MaxDis;
	Hero* atkTarget = nullptr;

	for (int i = 0; i < attackerCount; i++) {
		if (attackers[i] && !attackers[i]->IsDead()) {
			for (int j = 0; j < targetCount; j++) {
				if (targets[j] && !targets[j]->IsDead()) {
					double temp = countDistance(attackers[i]->getPosition(), targets[j]->getPosition());
					if (temp <= minDistance) {
						minDistance = temp;
						atkTarget = targets[j];
					}
				}
			}
			if (atkTarget) {
				attackers[i]->StartBattle(atkTarget);//Attack Target On Demand
			}
		}
	}
}

//Refactored with LazyLoading Pattern
void Battle::updateTargets(Hero** attackers, Hero** targets, int attackerCount, int targetCount) {
	Hero* atkTarget = nullptr;
	for (int i = 0; i < attackerCount; i++) {
		if (attackers[i] && !attackers[i]->IsDead()) {
			if (attackers[i]->ShowTarget()->IsDead()) {
				double minDistance = MaxDis;
				for (int j = 0; j < targetCount; j++) {
					if (targets[j] && targets[j]->IsOn() && targets[j]->IsDead() == 0) {
						double temp = countDistance(attackers[i]->getPosition(), targets[j]->getPosition());
						if (temp <= minDistance) {
							minDistance = temp;
							atkTarget = targets[j];
						}
					}
				}
				if (atkTarget) {
					attackers[i]->StartBattle(atkTarget);//Attack Target On Demand
				}
			}
		}
	}
}
//Refactored with LazyLoading Pattern
void Battle::resetHeroes() {
	isNext = false;
	for (int i = 0; i < myHeroNum; i++) {//If the hero dies, then lazy load
		if(self[i]){
			self[i]->SetDead(0);
			self[i]->SetOn(1);
		}
	}
	for (int i = 0; i < enHeroNum; i++) {//If the hero dies, then lazy load
		if(enemy[i]){
			enemy[i]->SetDead(0);
			enemy[i]->SetOn(1);
		}
	}
}

void Battle::recoverHeroes(Hero** heroes, int count, double amount) {
	for (int i = 0; i < count; i++) {
		if (heroes[i]->IsOn() && !heroes[i]->IsDead()) {
			heroes[i]->ChangeHP(-amount);
		}
	}
}

int Battle::isGameOver() {
	int myon = 0, enon = 0;
	for (int i = 0; i < myHeroNum; i++) {
		if (self[i]->IsOn() && !self[i]->IsDead()) myon++;
	}
	for (int i = 0; i < enHeroNum; i++) {
		if (enemy[i]->IsOn() && !enemy[i]->IsDead()) enon++;
	}
	
	myLive = myon;
	enLive = enon;
	
	if (myon && !enon) return 1;      // 我方胜利
	if (!myon && enon) return 2;      // 敌方胜利
	return 0;                         // 战斗继续
}

bool Battle::isNextRound() {
	return isNext;
}

double Battle::countDistance(Vec2 pos1, Vec2 pos2) {
	return sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2));
}

void Battle::Destory() {
	for (int i = 0; i < myHeroNum; i++) {
		self[i]->setVisible(false);
		self[i]->Destory();
	}
	for (int i = 0; i < enHeroNum; i++) {
		enemy[i]->setVisible(false);
		enemy[i]->Destory();
	}
}

void Battle::executeAttack(Hero* attacker, Hero* target) {
	if (!attacker || !target) return;
	
	attacker->StartBattle(target);
	// 处理攻击逻辑
}

void Battle::updatePositions() {
	// 更新英雄位置
}

void Battle::updateHeroStates() {
	// 处理英雄恢复效果
	for (int i = 0; i < myHeroNum; i++) {
		if (self[i]->IsOn() && !self[i]->IsDead()) {
			if (self[i]->IsRecover()) {
				recoverHeroes(self, myHeroNum, 100);
				self[i]->SetRecover();
			}
		}
	}
	
	for (int i = 0; i < enHeroNum; i++) {
		if (enemy[i]->IsOn() && !enemy[i]->IsDead()) {
			if (enemy[i]->IsRecover()) {
				recoverHeroes(enemy, enHeroNum, 100);
				enemy[i]->SetRecover();
			}
		}
	}
	
	// 更新攻击目标
	updateTargets(self, enemy, myHeroNum, enHeroNum);
	updateTargets(enemy, self, enHeroNum, myHeroNum);
}

void Battle::checkBattleEnd() {
	if (isGameOver()) {
		endBattle();
	}
}

bool Battle::isInProgress() const {
	return !isGameOver();
}

Player* Battle::getFirstPlayer() const {
	return myPlayer;
}

Player* Battle::getSecondPlayer() const {
	return enPlayer;
}