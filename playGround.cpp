#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{

}

HRESULT playGround::init()
{
	gameNode::init(true);

	_pm = new playerManager;
	_pm->init();
	_item = new itemManager;
	_item->init();
	_bts = new BattleScene;
	_bts->setPlayerManagerMemoryAddressLink(_pm);
	_bts->setItemManagerMemoryAddressLink(_item);
	_pm->setItemManagerAddressLink(_item);


	SCENEMANAGER->addScene("mapToolScene", new mapTool);
	SCENEMANAGER->addScene("배틀씬", _bts);
	SCENEMANAGER->addScene("월드맵씬", new worldMapScene);
	SCENEMANAGER->addScene("타운맵씬", new townScene);
	SCENEMANAGER->addScene("storeScene", new storeScene);
	SCENEMANAGER->addScene("게임오버", new gameOverScene);
	
	((storeScene*)(SCENEMANAGER->findScene("storeScene")))->setItemManagerAddressLink(_item);

	//SCENEMANAGER->changeScene("mapToolScene");
	
	((mapTool*)SCENEMANAGER->findScene("mapToolScene"))->createDefaultMap(PointMake(20, 20));

	//=========================== 메뉴씬 =========================== by won
	SCENEMANAGER->addScene("로딩", new loadingScene);
	SCENEMANAGER->addScene("타이틀", new titleScene);
    SCENEMANAGER->addScene("세이브로드", new saveLoadMenu);
	((saveLoadMenu*)SCENEMANAGER->findScene("세이브로드"))->setItemManagerAddressLink(_item);
	((saveLoadMenu*)SCENEMANAGER->findScene("세이브로드"))->setPlayerManagerAddressLink(_pm);
	SCENEMANAGER->addScene("옵션", new optionMenu);
	SCENEMANAGER->addScene("뉴게임", new newGame);
	((newGame*)SCENEMANAGER->findScene("뉴게임"))->setItemManagerAddressLink(_item);
	((newGame*)SCENEMANAGER->findScene("뉴게임"))->setPlayerManagerAddressLink(_pm);
	SCENEMANAGER->addScene("로드게임", new loadGame);
	((loadGame*)SCENEMANAGER->findScene("로드게임"))->setItemManagerAddressLink(_item);
	((loadGame*)SCENEMANAGER->findScene("로드게임"))->setPlayerManagerAddressLink(_pm);
	SCENEMANAGER->addScene("능력치", new abilitiesMenu);
	SCENEMANAGER->addScene("사운드", new configMenu);
	SCENEMANAGER->addScene("장비", new equipMenu);
	SCENEMANAGER->addScene("아이템", new itemMenu);
	SCENEMANAGER->addScene("상태", new statusMenu);
	SCENEMANAGER->addScene("캐릭터능력", new characterAbility);
	SCENEMANAGER->addScene("캐릭터상태", new characterStatus);
	//=========================== 메뉴씬 ===========================



	
	SCENEMANAGER->changeScene("로딩");

	return S_OK;
}

//메모리 관련 삭제
void playGround::release(void)
{
	gameNode::release();

}

//연산
void playGround::update(void)
{
	gameNode::update();

	//if (_isBattle)
	//{
	//	_pm->setPlayerInfoToBattlePlayer();
	//	_isBattle = false;
	//}

	//================================ 메뉴씬 ================================ by won
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		SOUNDMANAGER->stop(CH_BGM);
		SCENEMANAGER->changeScene("로딩");
	}
	//옵션메뉴
	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE) && SCENEMANAGER->getCurrentSceneName() == "월드맵씬")
	{
		SCENEMANAGER->changeSceneType1("옵션");
	}
	//================================ 메뉴씬 ================================

	//================================ 맵툴씬 ================================
	if (KEYMANAGER->isOnceKeyDown('M'))
	{
		SOUNDMANAGER->stop(CH_BGM);
		SCENEMANAGER->changeScene("mapToolScene");
	}
	//================================ 맵툴씬 ================================

	//================================ 배틀씬 ================================
	if (KEYMANAGER->isOnceKeyDown('B'))
	{
		SOUNDMANAGER->stop(CH_BGM);
		SCENEMANAGER->changeSceneType0("배틀씬");			//_isBattle = true;
	}
	//================================ 배틀씬 ================================

	//================================ 디버그 ================================
	if (KEYMANAGER->isOnceKeyDown(VK_F1)) _isDebug = !_isDebug;
	//================================ 디버그 ================================

	//==============================월드맵씬===================================
	if (KEYMANAGER->isOnceKeyDown('P'))
	{
		SCENEMANAGER->changeScene("월드맵씬");
	}
	//========================================================================

	//=============================타운씬======================================
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		SCENEMANAGER->changeSceneType0("타운맵씬");
	}
	//=========================================================================

	//=============================타운씬======================================
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		((storeScene*)SCENEMANAGER->findScene("storeScene"))->setStoreKey("weaponStore");
		SCENEMANAGER->changeSceneType0("storeScene");
	}
	//=========================================================================
	_pm->update();

	SCENEMANAGER->update();
}

//그리는거.......
void playGround::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================== 이 위는 손대지 마시오 =========================

	SetBkMode(getMemDC(), TRANSPARENT);
	SCENEMANAGER->render();
	TIMEMANAGER->render(getMemDC());
	
	//================== 이 아래는 손대지 마시오 ========================
	this->getBackBuffer()->render(getHDC(), 0, 0);//hdc영역에 그려준다 
}


