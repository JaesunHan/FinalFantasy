#include "stdafx.h"
#include "BattleScene.h"


BattleScene::BattleScene()
{
}


BattleScene::~BattleScene()
{

}

HRESULT BattleScene::init()
{
	IMAGEMANAGER->addImage("battleBG", ".\\image\\battlebackground\\Plains.bmp", 1136, 640, true, RGB(255, 0, 255));
	
	
	tagBattleCharacters temp;
	temp.characterType = MONSTER1;
	temp.ABTcounter = 0;
	temp.enemy = new Bear;
	_battleCharacters.push_back(temp);

	return S_OK;
}

void BattleScene::release()
{

}

void BattleScene::update() 
{

}

void BattleScene::render() 
{
	IMAGEMANAGER->findImage("battleBG")->render(getMemDC());
}
