#pragma once
#include "gameNode.h"
#include "worldMap.h"
#include "worldMapPlayer.h"
#include "npcManager.h"
#include "worldMapEnemyManager.h"

//======월드맵 씬	 =======//
//		제작자 : 한재환		//
//		2월 12일				//
//==========================//



class worldMapScene : public gameNode
{
public:
	//충돌한 녀석 인덱스 보관용
	int _enemyNum;

	//충돌했는지 검출
	bool _isCollision;

	//도망갔늬
	bool _isEscape;

	worldMap * _worldMap;
	worldMapPlayer* _worldMapPlayer;

	//NPC등장용
	npcManager* _npcManager;

	//에너미 등장용
	worldMapEnemyManager* _wMEM;

	worldMapScene();
	~worldMapScene();


	HRESULT init();
	void release();
	void update();
	void render();

	//콜리전을 가져온 후 배틀씬으로 체인지
	void getCollision();

	void successEscape();

	//배틀씬과의 통신을 위한 불값 겟터세터
	bool getIsEscape() { return _isEscape; }
	void setIsEscape(bool isEscape) { _isEscape = isEscape; }


};
