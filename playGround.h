#pragma once
#include "gameNode.h"
#include "mapTool.h"
#include "BattleScene.h"
#include "playerManager.h"
#include "loadingScene.h"
#include "titleScene.h"
#include "saveLoadMenu.h"

class playGround : public gameNode
{
private:
	playerManager * _pm;
	BattleScene * _bts;
	bool _isBattle;
public:
	virtual HRESULT init(void);		//초기화 함수
	virtual void release(void);		//메모리 관련 해제
	virtual void update(void);		//업데이트(연산)
	virtual void render(void);		//그려주는 함수


	playGround();
	~playGround();
};

