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

	return S_OK;
}

void titleScene::release()
{

}

void titleScene::update() 
{
	cursorUpdate();
	cursorKeyControl(47, 3);

	//선택
	switch (_cursor.currentNum)
	{
		case 0:
			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				_saveType = SAVE_NEWGAME;
				SCENEMANAGER->changeScene("세이브로드");
			}
		break;
		case 1:
			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				_saveType  = SAVE_LOADGAME;
				SCENEMANAGER->changeScene("세이브로드");
			}
		break;
		case 2:
			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				PostQuitMessage(0);
			}
		break;
	}

	cout << _saveType << endl;
}



