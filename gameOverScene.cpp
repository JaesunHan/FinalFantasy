#include "stdafx.h"
#include "gameOverScene.h"


gameOverScene::gameOverScene()
{
}


gameOverScene::~gameOverScene()
{

}

HRESULT gameOverScene::init()
{
	IMAGEMANAGER->addImage("gameOver", ".\\image\\gameOver\\gameOver.bmp", 400,	240, true, RGB(255, 0, 255));
	SOUNDMANAGER->addSound("gameOverBGM", ".\\sound\\gameOverSound\\gameOver.mp3", true, false);
	SOUNDMANAGER->play("gameOverBGM", CH_BGM, 1.0f);
	return S_OK;
}

void gameOverScene::release()
{
	IMAGEMANAGER->deleteImage("gameOver");
	SOUNDMANAGER->releaseAllSound();
}

void gameOverScene::update() 
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		SCENEMANAGER->changeSceneType0("·Îµù");
	}
}

void gameOverScene::render() 
{
	IMAGEMANAGER->findImage("gameOver")->enlargeRender(getMemDC(), 0, 0, WINSIZEX, WINSIZEY);
}
