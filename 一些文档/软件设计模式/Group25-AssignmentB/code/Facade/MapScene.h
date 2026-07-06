//Refactored with Facade Pattern
//In this file, the MapScene class uses BattleSystemFacade to control the battle flow.
#pragma once
#include "cocos2d.h"
#include"Hero.h"
#include "Battle.h"
#include "ShopLayer.h"
#include "Server.h"
#include "Client.h"
#include"Command.h"
#include "NetMessage.h"
#include "SimpleAudioEngine.h"
#include "BattleSystemFacade.h"
USING_NS_CC;
class BattleSystemFacade;
class MapScene :public Scene
{
protected:
	cocos2d::Vec2 lastHeroPosition;  // 记录最后一个英雄的位置

	Player* player; // 存储对 Player 实例的引用或指针
	ShopLayer* shopLayer;
	BattleSystemFacade* battleSystemFacade;
	TeamManager* teamManager;
	Player* enPlayer;//敌方玩家
	bool isStartBattle;
	Label* roundLabel;
	int round;//回合数
	bool isadd;
	Layer* borderLayer;
public:
	//地图
	TMXTiledMap* background;

	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MapScene);//用于创建Cocos2d-x游戏引擎中的节点对象或自定义类的实例

	//创建商店层实例
	void createShopLayer(Player* player, TMXTiledMap* background);

	cocos2d::Vec2 getStartPosition();  // 新方法来获取起始位置

	void addHeroToMap(Hero* hero);

	void Playerinit();

	Player* getCurrentPlayer();

	void addBorder(TMXTiledMap* background);

	void CreateBattle(float t);

	virtual	void update(float dt);

	void gamePauseCallback(Ref* pSender);

	void musicTimer(float t);
};
