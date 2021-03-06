#include "stdafx.h"
#include "titleScene.h"


titleScene::titleScene()
 : _saveType(0)
{
}
titleScene::~titleScene()
{
}


HRESULT titleScene::init()
{
	_bgImage = IMAGEMANAGER->findImage("타이틀메뉴");
	cursorInit(CUSOR_RIGHT, 475, 402);

	//플레이어 세이브파일 로드를 위한 신호값: 초기화
	INIDATA->addData("gameData", "gameStart", "0");
	INIDATA->iniSave("gameData");

	return S_OK;
}

void titleScene::release()
{

}

void titleScene::update() 
{
	cursorUpdate();
	cursorKeyControlY(47, 3);

	//선택
	switch (_cursor.currentYNum)
	{
		case 0:
			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				SCENEMANAGER->changeScene("뉴게임");
			}
		break;
		case 1:
			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				SCENEMANAGER->changeScene("로드게임");
			}
		break;
		case 2:
			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				PostQuitMessage(0);
			}
		break;
	}
}



