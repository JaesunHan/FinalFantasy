#pragma once
#include "gameNode.h"
#include "mapTool.h"
#include "BattleScene.h"
#include "playerManager.h"
#include "loadingScene.h"
#include "titleScene.h"
#include "saveLoadMenu.h"
#include "optionMenu.h"
#include "worldMapScene.h"
#include "townScene.h"
#include "newGame.h"
#include "loadGame.h"
#include "abilitiesMenu.h"
#include "configMenu.h"
#include "equipMenu.h"
#include "itemMenu.h"
#include "statusMenu.h"
#include "itemManager.h"
#include "gameOverScene.h"
#include "characterAbility.h"
#include "characterStatus.h"
#include "storeScene.h"
#include "openingMovie.h"
#include "menu.h"
#include "characterEquip.h"




class playGround : public gameNode
{
private:
	playerManager* _pm;
	itemManager* _item;
	BattleScene* _bts;

	menu* _menu;


	//bool _isBattle;
public:
	virtual HRESULT init(void);		//초기화 함수
	virtual void release(void);		//메모리 관련 해제
	virtual void update(void);		//업데이트(연산)
	virtual void render(void);		//그려주는 함수


	playGround();
	~playGround();
};

