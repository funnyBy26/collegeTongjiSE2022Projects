//Refactored with Factory Method and State Pattern

//The Hero class is a class that represents the hero.
//The Hero class has a member variable of type HeroState.
//The Hero class has a method called setState to set the state of the hero.
//The Hero class has a method called update to update the state of the hero.    
#pragma once
#ifndef HERO_H
#define HERO_H

#include "cocos2d.h"
#include "HeroState.h"
#include "showHPMP.h"
#include "Attack.h"
#include "Information.h"
#include "Hero/IHero.h"

using namespace cocos2d;

class HeroState;

class Hero : public Sprite,public IHero{
    friend class IdleState;
    friend class MoveState;
    friend class AttackState;
    friend class RecoverState;
    friend class DeadState;

public:
    Hero();
    virtual ~Hero();

    static Hero* create(const std::string& filename);
    CREATE_FUNC(Hero);

    void update(float dt) override; // 每帧更新
    void changeState(HeroState* newState); 

    // 基本属性操作
    void upgrade(); 
	void Hero::setLocation(int x) {location=x;}
    int Hero::getLocation() {return location;}
    void Hero::starVisible(int x) {star->setVisible(x);}
	void initAttributes() override {HPInit();setScale(0.45f);}
	void updateAttributes() override;
	int getId() const override { return id; }
	void setId(int id) override { this->id = id; }
	int getLevel() const override { return level; }
	void setLevel(int level) override;
	std::string getName() const override { return heroName; }
    heroInformation* getBaseInfo() {return baseInfo;}

    // 动画设置
    void SetAction();

    // 战斗相关
	void startBattle(IHero* target) override;  
    void ChangeHP(float data); // 修改血量
    void ChangeMP(); // 修改蓝量
    bool IsDead() const override;
	void initAttackBehavior();
	void performAttack() override{changeState(new AttackState());}
	void performMove() override{changeState(new MoveState());}
	void takeDamage(float damage) override { ChangeHP(-damage); }


    // UI相关
    void SetHeroDataByTag(int tag, Vec2 pos); // 初始化英雄
    void SetBaseInfo(heroInformation* info, std::string name, Vec2 pos);
    void HPInit(); 
    void setHeroOn(); // 上场设置
    void updateStarLevel(); // 更新星级
    void updateImage(); 

    // 位置信息
    Vec2 getTargetPosition() const; // 获取攻击目标位置
	double CountDistance();//计算英雄和攻击目标的距离

private:
    void cleanupCurrentState();

    // 英雄属性
    HeroState* currentState;
    heroInformation* baseInfo; 
    Hero* atkTarget; 
    Sprite* star; 
    showHPMP* heroHP; 
    showHPMP* heroMP; 
	std::unique_ptr<Attack> heroAttack;
	std::unique_ptr<IAttackBehavior> attackBehavior;

    int id; 
    int level; 
	int location;
    std::string heroName; 
    Vec2 heroPos; 
};

#endif 