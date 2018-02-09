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
	
	temp.characterType = TINA;
	temp.ABTcounter = 30000;
	temp.player = new battleTina;
	_battleCharacters.push_back(temp);
	temp.characterType = LOCKE;
	temp.ABTcounter = 30000;
	temp.player = new battleLocke;
	_battleCharacters.push_back(temp);
	temp.characterType = SHADOW;
	temp.ABTcounter = 30000;
	temp.player = new battleShadow;
	_battleCharacters.push_back(temp);
	temp.characterType = CELES;
	temp.ABTcounter = 30000;
	temp.player = new battleCeles;
	_battleCharacters.push_back(temp);

	_maxMonster = 4; // RND->getInt(3) + 1;
	
	for (int i = 0; i < _maxMonster; ++i)
	{
		int monsterType = RND->getInt(3);
		temp.characterType = i + 4;
		temp.ABTcounter = 0;
		switch (monsterType)
		{
		case(0):
			temp.enemy = new Bear;
			break;
		case(1):
			temp.enemy = new DarkWind;
			break;
		case(2):
			temp.enemy = new VectorPup;
			break;
		}
		_battleCharacters.push_back(temp);
	}

	_battleCharacters[4].enemy->init(100, 100);
	_battleCharacters[5].enemy->init(300, 100);
	_battleCharacters[6].enemy->init(100, 540);
	_battleCharacters[7].enemy->init(300, 540);
	for (int i = 0; i < 4; ++i)
	{
		_battleCharacters[i + 4].enemy->setBattleTinaMemoryAddressLink(_battleCharacters[0].player);
		_battleCharacters[i + 4].enemy->setBattleLockeMemoryAddressLink(_battleCharacters[1].player);
		_battleCharacters[i + 4].enemy->setBattleShadowMemoryAddressLink(_battleCharacters[2].player);
		_battleCharacters[i + 4].enemy->setBattleCelesMemoryAddressLink(_battleCharacters[3].player);
	}

	return S_OK;
}

void BattleScene::release()
{

}

void BattleScene::update() 
{
	if (_turnStart == false)
	{
		for (int i = 0; i < _battleCharacters.size(); ++i)
		{
			if (_battleCharacters[i].characterType <= 3)
			{
				if (_battleCharacters[i].player->getCurHP() < 0) continue;
				_battleCharacters[i].ABTcounter += 96 * (_battleCharacters[i].player->getSpeed() + 20) / 32;
			}
			if (_battleCharacters[i].characterType > 3)
			{
				if (_battleCharacters[i].enemy->getCurHP() < 0) continue;
				_battleCharacters[i].ABTcounter += 96 * (_battleCharacters[i].enemy->getSpeed() + 20) * 207 / 32;
			}
		}
	}
	
}

void BattleScene::render() 
{
	IMAGEMANAGER->findImage("battleBG")->render(getMemDC());
	for (int i = 0; i < _battleCharacters.size(); ++i)
	{
		if (_battleCharacters[i].characterType <= 3)
		{
			if (_battleCharacters[i].player->getCurHP() < 0) continue;
		}
		if (_battleCharacters[i].characterType > 3)
		{
			if (_battleCharacters[i].enemy->getCurHP() < 0) continue;
			_battleCharacters[i].enemy->render();
		}
	}
}

void BattleScene::monsterAttack()
{

}