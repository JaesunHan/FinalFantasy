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
	_bgImage = IMAGEMANAGER->findImage("Ÿ��Ʋ�޴�");
	cursorInit(CUSOR_RIGHT, 475, 402);

	return S_OK;
}

void titleScene::release()
{

}

void titleScene::update() 
{
	cursorUpdate();
	cursorKeyControlY(47, 3);

	//����
	switch (_cursor.currentYNum)
	{
		case 0:
			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				SCENEMANAGER->changeScene("������");
			}
		break;
		case 1:
			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				SCENEMANAGER->changeScene("�ε����");
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



