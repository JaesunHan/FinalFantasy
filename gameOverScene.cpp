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
	SOUNDMANAGER->addSound("gameOverBGM", ".\\sound\\gameOverSound\\gameOver.mp3", false, false);
	return S_OK;
}

void gameOverScene::release()
{

}

void gameOverScene::update() 
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		SOUNDMANAGER->addSound("gameOverBGM", ".\\sound\\gameOverSound\\gameOver.mp3", false, false);
		SOUNDMANAGER->play("gameOverBGM", CH_BGM, 1.0f);
		//SOUNDMANAGER->releaseSingleSound("gameOverBGM");
		//SCENEMANAGER->changeScene("·Îµù");
	}
}

void gameOverScene::render() 
{
	IMAGEMANAGER->findImage("gameOver")->enlargeRender(getMemDC(), 0, 0, WINSIZEX, WINSIZEY);
}
