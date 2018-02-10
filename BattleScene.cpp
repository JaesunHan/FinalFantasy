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
	IMAGEMANAGER->addImage("battleBG", ".\\image\\battlebackground\\Plains.bmp", 1200, 640, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("battleUI", ".\\image\\userInterface\\menuBackground.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("progressBarBottom", ".\\image\\userInterface\\progressBarBottom.bmp", 150, 17, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("progressBarTop", ".\\image\\userInterface\\progressBarTop.bmp", 170, 23, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("progressBarComplete", ".\\image\\userInterface\\progressBarComplete.bmp", 150, 17, true, RGB(255, 0, 255));

	SOUNDMANAGER->addSound("battleBGM", ".\\sound\\battleSound\\05 - Battle Theme.mp3", false, false);
	SOUNDMANAGER->play("battleBGM", CH_BGM, 1.0f);

	tagBattleCharacters temp;
	
	temp.characterType = TINA;
	temp.ATBcounter = 25000 + RND->getInt(10000);
	temp.player = new battleTina;
	_battleCharacters.push_back(temp);
	temp.characterType = LOCKE;
	temp.ATBcounter = 25000 + RND->getInt(10000);
	temp.player = new battleLocke;
	_battleCharacters.push_back(temp);
	temp.characterType = SHADOW;
	temp.ATBcounter = 25000 + RND->getInt(10000);
	temp.player = new battleShadow;
	_battleCharacters.push_back(temp);
	temp.characterType = CELES;
	temp.ATBcounter = 25000 + RND->getInt(10000);
	temp.player = new battleCeles;
	_battleCharacters.push_back(temp);

	_maxMonster = RND->getInt(3) + 1;
	
	for (int i = 0; i < _maxMonster; ++i)
	{
		int monsterType = RND->getInt(3);
		temp.characterType = i + 4;
		temp.ATBcounter = 0;
		//temp.enemy = new Bear;
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

	//_battleCharacters[4].enemy->init(100, 100);
	//_battleCharacters[5].enemy->init(300, 100);
	//_battleCharacters[6].enemy->init(100, 540);
	//_battleCharacters[7].enemy->init(300, 540);
	for (int i = 0; i < _maxMonster; ++i)
	{
		_battleCharacters[i + 4].enemy->init(250 + (240 / _maxMonster * (_maxMonster - 1)) * cosf(PI2 / _maxMonster * i + PI / 2), 300 - (240 / _maxMonster * (_maxMonster - 1)) * sinf(PI2 / _maxMonster * i + PI / 2));
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
	ATBGauzeTimer();
	for (int i = 0; i < _battleCharacters.size(); ++i)
	{

	}
	//if (KEYMANAGER->isOnceKeyDown('R'))
	//{
	//	//SOUNDMANAGER->releaseSound(0);
	//	//SOUNDMANAGER->releaseSound("battleBGM");
	//	SOUNDMANAGER->stop(CH_BGM);
	//}
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
	for (int i = 0; i < 4; ++i)
	{
		IMAGEMANAGER->findImage("battleUI")->enlargeRender(getMemDC(), WINSIZEX - 250, 160 * i, 250, 160);
		//_battleCharacters[i].player->getFaceImg()->render(getMemDC(), WINSIZEX - 240, 160 * i + 10);
		if (_battleCharacters[i].ATBcounter > 65535)
		{
			IMAGEMANAGER->findImage("progressBarComplete")->enlargeRender(getMemDC(), WINSIZEX - 197, 160 * i + 121, 144, 17);
		}
		else
		{
			IMAGEMANAGER->findImage("progressBarBottom")->enlargeRender(getMemDC(), WINSIZEX - 197, 160 * i + 121, 144 * _battleCharacters[i].ATBcounter / 65536, 17);
		}
		IMAGEMANAGER->findImage("progressBarTop")->render(getMemDC(), WINSIZEX - 210, 160 * i + 120);
	}
}

void BattleScene::ATBGauzeTimer()
{
	if (_counterRoll == true)
	{
		for (int i = 0; i < _battleCharacters.size(); ++i)
		{
			if (_battleCharacters[i].characterType <= 3)
			{
				if (_battleCharacters[i].player->getCurHP() < 0) continue;
				_battleCharacters[i].ATBcounter += 96 * (_battleCharacters[i].player->getSpeed() + 20) / 32;
			}
			if (_battleCharacters[i].characterType > 3)
			{
				if (_battleCharacters[i].enemy->getCurHP() < 0) continue;
				_battleCharacters[i].ATBcounter += 96 * (_battleCharacters[i].enemy->getSpeed() + 20) / 32;
			}
		}
		for (int i = 0; i < _battleCharacters.size(); ++i)
		{
			if (_battleCharacters[i].ATBcounter > 65535 && _battleCharacters[i].turnStart == false)
			{
				_battleTurn.push(_battleCharacters[i].characterType);
				_battleCharacters[i].turnStart = true;
			}
		}
	}
}