#pragma once
#include "gameNode.h"
#include "generalMap.h"
#include "worldMap.h"
#include "worldMapPlayer.h"
#include "npcManager.h"
#include "worldMapEnemyManager.h"




//======월드맵 씬	 =======//
//		제작자 : 한재환		//
//		2월 12일				//
//==========================//

//인벤토리 가져오기 위한 전방선언 월드맵에서 인벤토리를 건드립니다 흿흿!
class itemManager;
class optionMenu;

enum KEY_FOCUS
{
	FOCUS_PLAYER,
	FOCUS_MESSAGEBOX,
	FOCUS_BATTLEENCOUNT,
	FOCUS_ENEMYENCOUNT,
	FOCUS_NONE
};

class worldMapScene : public gameNode
{
private:
	//충돌한 녀석 인덱스 보관용
	int _enemyNum;



	//충돌했는지 검출
	bool _isCollision;
	bool _isEncounter;
	bool _isNotEnemyVector;
	bool _isGetGongChi;

	//도망갔늬
	bool _isEscape;

	generalMap* _worldMap;
	worldMapPlayer* _worldMapPlayer;

	//NPC등장용
	npcManager* _npcManager;

	//에너미 등장용
	worldMapEnemyManager* _wMEM;

	//인벤토리용
	itemManager* _im;

	//메뉴클래스 
	optionMenu* _optionMenu;

	POINT _curPlayerPos;
	POINT _curCameraPos;

	image* _openBox;
	image* _messageBox;
	bool _isOpenBox;
	bool _isMessageBox;
	bool _isDoBattleEncount;
	bool _isEnemyEncount;

	POINT tempPoint;

	bool _getIsBoss;

	int _focus;
	int _encountNum;

	char str[128];
	int _sideImgChange;
	image* _sideImg;

public:
	worldMapScene();
	~worldMapScene();


	HRESULT init();
	void release();
	void update();
	void render();

	//콜리전을 가져온 후 배틀씬으로 체인지
	void getCollision();

	void successEscape();


	//타운으로 들어가자.
	void enterTownMap();



	//배틀씬과의 통신을 위한 불값 겟터세터
	bool getIsEscape() { return _isEscape; }
	void setIsEscape(bool isEscape) { _isEscape = isEscape; }

	void setPlayerPos(void);
	void resetIsEncounter(void) { _isEncounter = false; SOUNDMANAGER->stop(CH_ENCOUNTER); }

	void getGongChi();

	void battleEncount();
	void doBattleEncount();

	void savePoint();

	void battleEncountRender1();
	void battleEncountRender2();
	void battleEncountRender3();


	//겟셋추가!!!!
	void setItemManagerAddressLink(itemManager* im) { _im = im; }
	void setMenuMemoryAddressLink(optionMenu* optionMenu) { _optionMenu = optionMenu; }
	
	//월드맵 플레이어 정보 가져온다.
	worldMapPlayer* getworldMapPlayer() { return _worldMapPlayer; }

	worldMapEnemyManager* getWorldEnemy() { return _wMEM; }

	bool getGetIsBoss() { return _getIsBoss; }


};
