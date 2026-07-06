//Refactored with Factory Method and State Pattern
//In this file, the Hero class is implemented. 
#include "Hero.h"
#include "HeroState.h"

Hero::Hero()
    : currentState(nullptr),
      atkTarget(nullptr),
      baseInfo(nullptr),
      heroHP(nullptr),
      heroMP(nullptr),
      id(0),
      level(1) {}

Hero::~Hero() {
    cleanupCurrentState();
    CC_SAFE_DELETE(baseInfo);
    CC_SAFE_RELEASE(heroHP);
    CC_SAFE_RELEASE(heroMP);
}

Hero* Hero::create(const std::string& filename) {
    Hero* sprite = new (std::nothrow) Hero();
    if (sprite && sprite->initWithFile(filename)) {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

//重构为通过当前状态调用逻辑，而不是直接在 Hero 类中写逻辑
void Hero::update(float dt) {
    if (currentState) {
        currentState->update(this, dt);
    }
}

//新增函数，改变hero状态
void Hero::changeState(HeroState* newState) {
    if (currentState) {
        currentState->exit(this);
        cleanupCurrentState();
    }
    currentState = newState;
    if (currentState) {
        currentState->enter(this);
    }
}

//攻击逻辑由 AttackState 管理，Hero仅负责状态切换
void Hero::startBattle(IHero* target) {
    Hero* heroTarget = dynamic_cast<Hero*>(target);
    if (heroTarget) {
        atkTarget = target;
        if(currentState!= AttackState){
          performAttack();
        }
    }
}

void Hero::cleanupCurrentState() {
    CC_SAFE_DELETE(currentState);
}

void Hero::SetHeroDataByTag(int tag, Vec2 pos) {
    id = tag;
    Information InfoMap;
    InfoMap.SetHeroInfo();
    baseInfo = InfoMap.GetInfoByTag(id);
    heroName = InfoMap.getNameByTag(id);
    heroPos = pos;
    this->setTexture(heroName + "-action1.png");
    this->setVisible(false);
}

void Hero::SetBaseInfo(heroInformation* info, std::string name, Vec2 pos) {
    baseInfo = info;
    heroName = name;
    heroPos = pos;
    this->setTexture(heroName + "-action1.png");
    this->setVisible(false);
}

void Hero::HPInit() {
    heroHP = showHPMP::create();
    heroMP = showHPMP::create();
    this->getParent()->addChild(heroHP, 5);
    this->getParent()->addChild(heroMP, 5);
    heroHP->retain();
    heroMP->retain();
}

void Hero::setHeroOn() {
    this->setPosition(heroPos);
    this->setScale(0.55);

    // 初始化血条
    Vec2 posBlood(heroPos.x, heroPos.y + this->getContentSize().height / 2 - 55);
    heroHP->setPosition(posBlood);
    heroHP->setBackgroundTexture("Blood-back.png");
    heroHP->setForegroundTexture(heroName + "Blood-front.png");
    heroHP->setTotalProgress(baseInfo->HP);
    heroHP->setCurrentProgress(baseInfo->HP);
    heroHP->setScale(0.4);

    // 初始化蓝条
    Vec2 posMP(posBlood.x, posBlood.y - 10);
    heroMP->setPosition(posMP);
    heroMP->setBackgroundTexture("MP-back.png");
    heroMP->setForegroundTexture("MP-front.png");
    heroMP->setTotalProgress(baseInfo->MP);
    heroMP->setCurrentProgress(0.0f);
    heroMP->setScale(0.4);

    this->setVisible(true);
    heroHP->setVisible(true);
    heroMP->setVisible(true);

    SetAction();
    changeState(new IdleState());
}

void initAttackBehavior() {
	attackBehavior = Attack::createBehaviorForHero(
		heroName, 
        baseInfo->atkrange
	);
}

void Hero::SetAction() {
    // 设置攻击动作
    Vector<SpriteFrame*> spriteFrameVec;
    for (int i = 1; i <= 2; i++) {
        char imageName[20];
        sprintf(imageName, "-action%d.png", i);
        SpriteFrame* spriteFrame = SpriteFrame::create(heroName + imageName, Rect(0, 0, this->getContentSize().width, this->getContentSize().height));
        spriteFrameVec.pushBack(spriteFrame);
    }
    Animation* ani = Animation::createWithSpriteFrames(spriteFrameVec, 0.5);
    Animate* attackAction = Animate::create(ani);

    // 设置移动动作
    Vector<SpriteFrame*> spriteFrameVec2;
    for (int i = 1; i <= 2; i++) {
        char imageName[20];
        sprintf(imageName, "-move%d.png", i);
        SpriteFrame* spriteFrame = SpriteFrame::create(heroName + imageName, Rect(0, 0, this->getContentSize().width, this->getContentSize().height));
        spriteFrameVec2.pushBack(spriteFrame);
    }
    Animation* ani2 = Animation::createWithSpriteFrames(spriteFrameVec2, 0.5);
    Animate* moveAction = Animate::create(ani2);
}

//新增对状态切换的支持，当血量为 0 时切换到 DeadState
void Hero::ChangeHP(float data) {
    heroHP->setCurrentProgress(heroHP->getCurrentProgress() - data + baseInfo->defence);
    if (heroHP->getCurrentProgress() <= 0) {
        changeState(new DeadState());
    }
}

void Hero::ChangeMP() {
    heroMP->setCurrentProgress(heroMP->getCurrentProgress() + 10);
}

bool Hero::IsDead() const {
    return heroHP->getCurrentProgress() <= 0;
}

void Hero::updateStarLevel() {
std::string StarList[4] = { "star1.png","star2.png","star3.png","star4.png" };
    // 清除旧的星星精灵
    //this->removeAllChildren();
    std::string starFileName = StarList[this->level - 1];
    if (this->level == 1) {
        this->star = Sprite::create(starFileName);
        if (star) {
            float spacing = 15.0f;
            float CardWidth = this->getContentSize().width;
            float CardHeight = this->getContentSize().height;
            float posY = this->getPositionY() / 10;
            float posX = this->getPositionX() / 50;
            //大小
            if (level == 1)
                star->setScale(0.1, 0.1);
            else
                star->setScale(0.15, 0.15);
            //位置
            star->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
            Vec2 StarPosition = this->getPosition();
            star->setPosition(posX, posY);
            this->addChild(star, 0);
        }
    }
    else {
        star->setTexture(starFileName);
        if (star) {
            float spacing = 15.0f;
            float CardWidth = this->getContentSize().width;
            float CardHeight = this->getContentSize().height;
            float posY = this->getPositionY() / 10;
            float posX = this->getPositionX() / 50;
            //大小
            if (level == 1)
                star->setScale(0.1, 0.1);
            else
                star->setScale(0.15, 0.15);
            //位置
            star->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
            Vec2 StarPosition = this->getPosition();
            star->setPosition(posX, posY);
            //this->addChild(star, 0);
        }
    }
}

void Hero::updateImage() {
    int id = this->getId();
    //float itemWidth = 110.0f; // 假设每张背景图的宽度
    //float itemHeight = 110.0f; // 假设每张背景图的高度

    // 查找对应的图像路径
    auto it = Information::warimagePaths.find(id);
    if (it != Information::warimagePaths.end()) {
        // 如果找到了图像路径
        const std::string& warimagePath = it->second;
        // 更新精灵的纹理
        this->setTexture(warimagePath);

        // 可能需要调整精灵的大小以适应新的纹理
        //this->setContentSize(Size(itemWidth-10, itemHeight+10));
        this->setScale(0.45);
    }
    else {
        // 找不到对应的图像路径
        CCLOG("Image path for hero ID %d not found", id);
    }
}

void Hero::setLevel(int level) {
    this->level = level;
    updateStarLevel(); 
    updateAttributes();       
}

void Hero::upgrade() {
    if (level < 4) {
        level++;
        updateStarLevel();
    }
}

void Hero::updateAttributes() {
    if (level > 1) {
        baseInfo->HP += level * 80;
        baseInfo->attack += level * 60;
    }
}

Vec2 Hero::getTargetPosition() const {
    Vec2 enemyPos = atkTarget->getPosition();
    double distance = CountDistance();
    Vec2 direction = Vec2(enemyPos.x - this->getPosition().x, enemyPos.y - this->getPosition().y) / distance;
    Vec2 tarPos;
    if (distance - baseInfo->atkrange > 0)
        tarPos = direction * (distance - baseInfo->atkrange) + this->getPosition();
    else
        tarPos = (0, 0);
    return direction;
}

double Hero::CountDistance() {
    if (!atkTarget) return 0.0;
    return this->getPosition().distance(atkTarget->getPosition());
}

void Hero::SetHeroDataByTag(int tag,Vec2 pos) {
    id = tag;
    Information InfoMap;
    InfoMap.SetHeroInfo();
    baseInfo = InfoMap.GetInfoByTag(id);
    heroName = InfoMap.getNameByTag(id);
    heroPos = pos;
    this->setTexture(heroName + "-action1.png");
    this->setVisible(0);
}

