//Refactored with State Pattern
//In this file, the HeroState class is implemented.
//The HeroState class is a base class for all the states of the hero.
//The HeroState class has a method called enter to enter the state.
//The HeroState class has a method called update to update the state.
//The HeroState class has a method called exit to exit the state.

#include "Hero.h"
#include "HeroState.h"
#include "SimpleAudioEngine.h"

// -----------------Idle 状态-----------------
void IdleState::enter(Hero* hero) {
    CCLOG("Hero enters Idle state");
    hero->stopAllActions();
}

void IdleState::update(Hero* hero, float dt) {
    // 检查攻击目标是否存在且未死亡
    if (hero->atkTarget && !hero->atkTarget->IsDead()) {
        if (hero->CountDistance() > hero->baseInfo->atkrange) {
            // 目标超出攻击范围，切换到移动状态
            hero->changeState(new MoveState());
        } else {
            // 目标在攻击范围内，切换到攻击状态
            hero->changeState(new AttackState());
        }
    }
}

void IdleState::exit(Hero* hero) {
    CCLOG("Hero exits Idle state");
}

// -----------------Move 状态-----------------
void MoveState::enter(Hero* hero) {
    CCLOG("Hero enters Move state");
    
    // 计算移动时间
    float movetime = hero->baseInfo->movespeed / 100.0f;
    hero->movetimer = movetime;
    hero->curMoveTimer = 0;
    
    // 创建移动动作
    auto moveAction = MoveTo::create(movetime, hero->heroPos);
    hero->runAction(moveAction);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("move.mp3");
}

void MoveState::update(Hero* hero, float dt) {
    hero->curMoveTimer += dt;
    
    //是否到达目标位置
    if (hero->curMoveTimer >= hero->movetimer) {
        hero->changeState(new IdleState());
    }
}

void MoveState::exit(Hero* hero) {
    CCLOG("Hero exits Move state");
    hero->stopAllActions();
}

// -----------------Attack 状态-----------------
void AttackState::enter(Hero* hero) {
    CCLOG("Hero enters Attack state");
    
    //攻击计时器
    hero->atktimer = hero->baseInfo->atkspeed;
    hero->curAtkTimer = 0;

    //播放攻击动画
    Vector<SpriteFrame*> spriteFrameVec;
    for (int i = 1; i <= 2; i++) {
        char imageName[20];
        sprintf(imageName, "-action%d.png", i);
        SpriteFrame* spriteFrame = SpriteFrame::create(
            heroName + imageName, 
            Rect(0, 0, this->getContentSize().width, this->getContentSize().height)
        );
        spriteFrameVec.pushBack(spriteFrame);
    }
    Animation* ani = Animation::createWithSpriteFrames(spriteFrameVec, 0.5);
    auto atk = Animate::create(ani);
    MoveBy* stop = MoveBy::create(baseInfo->atkspeed - 1, Vec2(0, 0));
    Sequence* Atk = Sequence::create(atk, stop, nullptr);
    this->runAction(Atk);
    
    //攻击动作
    auto attackAction = Sequence::create(
        Animate::create(hero->attackAction),
        CallFunc::create([hero]() {
            // 创建攻击物
            if (hero->atkTarget && !hero->atkTarget->IsDead()) {
                hero->heroAttack = Attack::create(hero->heroName);
                if (hero->heroAttack) {
                    hero->heroAttack->SetTarget(hero->atkTarget);
                    hero->heroAttack->GetAttack(hero->baseInfo->attack);
                    hero->heroAttack->SetPosition(hero->getPosition(), hero->getContentSize());
                    hero->getParent()->addChild(hero->heroAttack);
                    hero->heroAttack->scheduleUpdate();
                }
            }
        }),
        nullptr
    );
    
    hero->runAction(attackAction);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("attack.mp3");
}

void AttackState::update(Hero* hero, float dt) {
    hero->curAtkTimer += dt;
    
    // 检查是否可以继续攻击
    if (hero->curAtkTimer >= hero->atktimer) {
        if (hero->atkTarget && !hero->atkTarget->IsDead()) {
            // 重置攻击计时器并继续攻击
            hero->curAtkTimer = 0;
            hero->changeState(new AttackState());
        } else {
            // 目标已死亡或不存在,切换到空闲状态
            hero->changeState(new IdleState());
        }
    }
}

void AttackState::exit(Hero* hero) {
    CCLOG("Hero exits Attack state");
    hero->stopAllActions();
}

// -----------------Recover 状态-----------------
void RecoverState::enter(Hero* hero) {
    CCLOG("Hero enters Recover state");
    
    // 开始恢复生命值
    float healAmount = hero->baseInfo->HP * 0.1f; // 每次恢复10%最大生命值
    hero->ChangeHP(-healAmount);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("heal.mp3");
}

void RecoverState::update(Hero* hero, float dt) {
    hero->changeState(new IdleState());
}

void RecoverState::exit(Hero* hero) {
    CCLOG("Hero exits Recover state");
}

// -----------------Dead 状态-----------------
void DeadState::enter(Hero* hero) {
    CCLOG("Hero enters Dead state");
    hero->stopAllActions();
    
    // 死亡效果
    auto fadeOut = FadeOut::create(1.0f);
    hero->runAction(fadeOut);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("dead.mp3");
    
    hero->setVisible(false);
}

void DeadState::update(Hero* hero, float dt) {
    // 死亡状态下不需要更新
}

void DeadState::exit(Hero* hero) {
    CCLOG("Hero exits Dead state");
}
