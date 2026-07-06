/*
* Refactor this code to use the strategy pattern.
* The Player class implements the strategy pattern to manage the player's behavior
* by dynamically setting different strategies. The different management logic of the
* player's gold, health, experience, hero and level are implemented through the strategy
* object to achieve flexible switching in different scenarios.
*/
#include "Player.h"

void Player::setGoldStrategy(std::shared_ptr<GoldStrategy> strategy) {
	goldStrategy = strategy;
}

void Player::setBloodStrategy(std::shared_ptr<BloodStrategy> strategy) {
	bloodStrategy = strategy;
}

void Player::setExperienceStrategy(std::shared_ptr<ExperienceStrategy> strategy) {
	experienceStrategy = strategy;
}

void Player::setHeroStrategy(std::shared_ptr<HeroStrategy> strategy) {
	heroStrategy = strategy;
}

void Player::setLevelStrategy(std::shared_ptr<LevelStrategy> strategy) {
	levelStrategy = strategy;
}

Player* Player::createSprite(){
	Player* sprite = new (std::nothrow) Player();
	if (sprite && sprite->init()){
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool Player::init() {
	if (!Sprite::init()){
		return false;
	}

	setGoldStrategy(std::make_shared<StandardGoldStrategy>());
	setBloodStrategy(std::make_shared<StandardBloodStrategy>());
	setExperienceStrategy(std::make_shared<StandardExperienceStrategy>());
	setLevelStrategy(std::make_shared<StandardLevelStrategy>());
	
	playerIsDead = 0;
	return true;
}


void Player::SetSmallHero(Vec2 pos,bool enabled) {
	smallHero = SmallHero::create();
	smallHero->SetBaseInfo("SmallHero.png", pos, enabled);
	this->getParent()->addChild(smallHero, 2);
}

Player::~Player() {
}

void Player::CreateHero() {
	if (heroStrategy) {
		heroStrategy->createHeroes(this);
	}
}

void Player::SetHero(Hero* hero) {
	if (heroStrategy) {
		heroStrategy->setHero(this, hero);
	}
	else {
		CCLOG("Hero strategy is not set!");
	}
}

bool Player::addHeroToWar(Hero& hero) {
	if (heroStrategy) {
		return heroStrategy->addHeroToWar(this, hero);
	}
	return false;
}

void Player::GetNetHero(NetHeroInfo* NetInfo) {
	if (heroStrategy) {
		heroStrategy->GetNetHero(this, NetInfo);
	}
}

bool Player:: hasEnoughGold(int amount) {
	return goldStrategy->hasEnoughGold(amount);
}

void Player::spendGold(int amount) {
	goldStrategy->spendGold(amount);
}

int Player::getGold(){
	return goldStrategy->getGold();
}

void Player::addGold(int data) {
	goldStrategy->addGold(data);
}

int Player::GetHeroNum(){
	return heroNum;
}

void Player::changeplayerBlood(int hurt)
{
	bloodStrategy->changeBlood(hurt);
}

int Player::GetPlayerBlood() {
	return bloodStrategy->getBlood();
}

int Player::GetplayerExperience(){
	return experienceStrategy->getExperience();
}

void Player::SetplayerExperience(int x){
	experienceStrategy->setExperience(x);
}

int Player::GetplayerNeedExperience(){
	return experienceStrategy->getNeedExperience();
}

void Player::SetplayerNeedExperience(int x){
	experienceStrategy->setNeedExperience(x);
}

int Player::GetplayerLevel(){
	return levelStrategy->getPlayerLevel();
}

void Player::SetplayerLevel(int x){
	levelStrategy->setPlayerLevel(x);
}

SmallHero* Player::getSmallHero(){
	return smallHero;
}

class Hero* Player::GetWarHero() {
	return chessWarPlayer;
}


void Player::Restart() {
	heroNum = 0;
}

void Player::SetHeroNum(int data) {
	heroNum = data;
}

bool Player::IsDead() {
	return playerIsDead;
}

void Player::clearWarPlayer() {
	for (auto& hero : chessWarPlayer) {
		Hero* hero1 = Hero::create();
		hero = *hero1;
	}
}