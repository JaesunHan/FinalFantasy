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

	IMAGEMANAGER->addImage("tinaFace00", ".\\image\\playerImg\\tina\\tina_face.bmp", 56, 38, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("lockeFace00", ".\\image\\playerImg\\locke\\locke_face.bmp", 56, 38, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("celesFace00", ".\\image\\playerImg\\celes\\celes_face.bmp", 56, 38, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("shadowFace00", ".\\image\\playerImg\\shadow\\shadow_face.bmp", 56, 38, true, RGB(255, 0, 255));

	SOUNDMANAGER->addSound("battleBGM", ".\\sound\\battleSound\\05 - Battle Theme.mp3", false, false);
	SOUNDMANAGER->play("battleBGM", CH_BGM, 1.0f);

	tagBattleCharacters temp;
	//�÷��̾� ���� �Ҵ� �� ���Ϳ� ���
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

	for (int j = 1; j < 4; ++j)
	{
		for (int i = j; i < 4; ++i)
		{
			if (_battleCharacters[i].player->getPartyIdx() == j - 1)
			{
				swap(_battleCharacters[j - 1], _battleCharacters[i]);
				break;
			}
		}
	}

	_maxMonster = RND->getInt(3) + 1;		//�ִ� ���� ���� ����
	//���ʹ� �����Ҵ� �� ���Ϳ� ���
	for (int i = 0; i < _maxMonster; ++i)
	{
		int monsterType = RND->getInt(3);
		temp.characterType = i + 4;
		temp.ATBcounter = 0;
		temp.enemy = new Bear;
		//switch (monsterType)
		//{
		//case(0):
		//	temp.enemy = new Bear;
		//	break;
		//case(1):
		//	temp.enemy = new DarkWind;
		//	break;
		//case(2):
		//	temp.enemy = new VectorPup;
		//	break;
		//}
		_battleCharacters.push_back(temp);
	}
	//���ʹ� Ŭ���� init �� �÷��̾� �ּ� ��巹�� ��ũ
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
	
	updateWhenCharacterTurn();

	//�÷��̾� �ִϸ��̼� ������ ������Ʈ
	for (int i = 0; i < 4; ++i)
	{
		_battleCharacters[i].player->animationFrameUpdate();
	}
}

void BattleScene::render() 
{
	//��Ʋ ��׶��� ����
	IMAGEMANAGER->findImage("battleBG")->render(getMemDC());

	characterDraw();
	drawUI();

	EFFECTMANAGER->render();
}
//��Ʋ Ÿ�̸� ������ �Լ�
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
		//Ÿ�̸Ӱ� ���� ���ʹ̸� ť�� �־�д�
		for (int i = 4; i < _battleCharacters.size(); ++i)
		{
			if (_battleCharacters[i].ATBcounter > 65535 && _battleCharacters[i].turnStart == false)
			{
				_battleTurn.push(_battleCharacters[i].characterType);
				_battleCharacters[i].turnStart = true;
				_battleCharacters[i].enemy->setTurnEnd(false);
			}
		}
	}
}

void BattleScene::updateWhenCharacterTurn()
{
	//ť���� �÷��̾ ���ʹ��� ���� ���ƿ��� ������Ʈ ����
	if (_battleTurn.size() > 0)
	{
		if (_battleTurn.front() <= 3)
		{
			_battleCharacters[_battleTurn.front()].player->update();
			if (_battleCharacters[_battleTurn.front()].player->getTurnEnd() == true)
			{
				_battleCharacters[_battleTurn.front()].ATBcounter = 0;
				_battleCharacters[_battleTurn.front()].turnStart = false;
				_battleTurn.pop();
			}
		}
		else
		{
			_battleCharacters[_battleTurn.front()].enemy->update();
			if (_battleCharacters[_battleTurn.front()].enemy->getTurnEnd() == true)
			{
				_battleCharacters[_battleTurn.front()].ATBcounter = 0;
				_battleCharacters[_battleTurn.front()].turnStart = false;
				_battleTurn.pop();
			}
		}
	}
}

void BattleScene::playerMenuSelect()
{
	for (int i = 0; i < 4; ++i)
	{
		if (_battleCharacters[i].ATBcounter > 65535 && _playerTurn == false)
		{
			_playerTurn = true;
			_currentTurn = i;
			_battleCharacters[i].player->setTurnEnd(false);
		}
	}
	if (_playerTurn == true)
	{
		switch (_battleCharacters[_currentTurn].characterType)
		{
		case(TINA):
			
			break;
		case(LOCKE):

			break;
		case(CELES):

			break;
		case(SHADOW):

			break;
		}
	}
}

void BattleScene::characterDraw()
{
	//�÷��̾� �� ���ʹ� ����
	for (int i = 0; i < _battleCharacters.size(); ++i)
	{
		if (_battleCharacters[i].characterType <= 3)
		{
			if (_battleCharacters[i].player->getCurHP() < 0) continue;
			_battleCharacters[i].player->render();
		}
		if (_battleCharacters[i].characterType > 3)
		{
			if (_battleCharacters[i].enemy->getCurHP() < 0) continue;
			_battleCharacters[i].enemy->render();
		}
	}
}

void BattleScene::drawUI()
{
	//UI ����
	for (int i = 0; i < 4; ++i)
	{
		IMAGEMANAGER->findImage("battleUI")->enlargeRender(getMemDC(), WINSIZEX - 250, 160 * i, 250, 160);
		RECT nameRC = { WINSIZEX - 150, 160 * i + 20, WINSIZEX - 15, 160 * i + 40 };
		//_battleCharacters[i].player->getFaceImg()->render(getMemDC(), WINSIZEX - 240, 160 * i + 10);
		switch (_battleCharacters[i].characterType)
		{
		case(TINA):
			IMAGEMANAGER->findImage("tinaFace00")->enlargeRender(getMemDC(), WINSIZEX - 235, 160 * i + 20, 84, 57);
			DrawText(getMemDC(), "Tina", -1, &nameRC, DT_LEFT | DT_WORDBREAK);
			break;
		case(LOCKE):
			IMAGEMANAGER->findImage("lockeFace00")->enlargeRender(getMemDC(), WINSIZEX - 235, 160 * i + 20, 84, 57);
			break;
		case(CELES):
			IMAGEMANAGER->findImage("celesFace00")->enlargeRender(getMemDC(), WINSIZEX - 235, 160 * i + 20, 84, 57);
			break;
		case(SHADOW):
			IMAGEMANAGER->findImage("shadowFace00")->enlargeRender(getMemDC(), WINSIZEX - 235, 160 * i + 20, 84, 57);
			break;
		}
		if (_battleCharacters[i].ATBcounter > 65535)
		{
			IMAGEMANAGER->findImage("progressBarComplete")->enlargeRender(getMemDC(), WINSIZEX - 197, 160 * i + 121, 144, 17);
		}
		else
		{
			IMAGEMANAGER->findImage("progressBarBottom")->enlargeRender(getMemDC(), WINSIZEX - 197, 160 * i + 121, 144 * _battleCharacters[i].ATBcounter / 65536, 17);
		}
		IMAGEMANAGER->findImage("progressBarTop")->render(getMemDC(), WINSIZEX - 210, 160 * i + 120);
		if (_playerTurn == true && i == _currentTurn)
		{
			switch (_battleCharacters[_currentTurn].characterType)
			{
			case(TINA):

				break;
			case(LOCKE):

				break;
			case(CELES):

				break;
			case(SHADOW):

				break;
			}
		}
	}
}