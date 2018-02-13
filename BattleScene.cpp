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
	//��Ʈ �߰�
	AddFontResourceEx(
		"SDMiSaeng.ttf", 	// font file name
		FR_PRIVATE,         // font characteristics
		NULL            	// reserved
	);
	//UI�̹��� �߰�
	IMAGEMANAGER->addImage("battleBG", ".\\image\\battlebackground\\Plains.bmp", 1200, 640, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("battleUI", ".\\image\\userInterface\\menuBackground.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("progressBarBottom", ".\\image\\userInterface\\progressBarBottom.bmp", 150, 17, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("progressBarTop", ".\\image\\userInterface\\progressBarTop.bmp", 170, 23, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("progressBarComplete", ".\\image\\userInterface\\progressBarComplete.bmp", 150, 17, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("fingerArrowRt", ".\\image\\userInterface\\fingerArrowRt.bmp", 25, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("fingerArrowLt", ".\\image\\userInterface\\fingerArrowLt.bmp", 25, 25, true, RGB(255, 0, 255));
	//�÷��̾� �� �̹��� �߰�
	IMAGEMANAGER->addImage("tinaFace00", ".\\image\\playerImg\\tina\\tina_face.bmp", 56, 38, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("lockeFace00", ".\\image\\playerImg\\locke\\locke_face.bmp", 56, 38, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("celesFace00", ".\\image\\playerImg\\celes\\celes_face.bmp", 56, 38, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("shadowFace00", ".\\image\\playerImg\\shadow\\shadow_face.bmp", 56, 38, true, RGB(255, 0, 255));
	//���� �߰�
	SOUNDMANAGER->addSound("battleBGM", ".\\sound\\battleSound\\05 - Battle Theme.mp3", false, true);
	SOUNDMANAGER->addSound("battleMenuOpen", ".\\sound\\sfx\\battleMenuOpen.wav", false, false);
	SOUNDMANAGER->addSound("menuSelectLow", ".\\sound\\sfx\\menuSelectLow.wav", false, false);
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
	//�÷��̾� �ε��� ������ �°� ����
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
	//�ִ� ���� ���� ����
	_maxMonster = RND->getInt(3) + 1;		
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
	playerMenuSelect();
	updateWhenCharacterTurn();
	playerFrameUpdate();
	soundControl();
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
		//ATB ī���Ϳ� ĳ���� ���ǵ忡 ���� ���� ���� �����ش�.
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
				_battleTurn.push(&_battleCharacters[i]);
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
		if (_battleTurn.front()->characterType <= 3)
		{
			if (_battleTurn.front()->attackReady == false)
			{ 
				//�÷��̾ ������ ���ʹ� �ּ� �Ҵ�
				//�ش� ���ʹ̰� �׾��� ��쿣 ����ִ¾ַ� �Ҵ�
				if (_battleTurn.front()->enemy != NULL)
				{
					if (_battleTurn.front()->enemy->getCurHP() > 0)
					{
						_battleTurn.front()->player->setTargetEnemy(_battleTurn.front()->enemy);
					}
					else
					{
						for (int i = 0; i < _maxMonster; ++i)
						{
							if (_battleCharacters[i + 4].enemy->getCurHP() > 0)
							{
								_battleTurn.front()->player->setTargetEnemy(_battleCharacters[i + 4].enemy);
								break;
							}
						}
					}
				}
				//�÷��̾� ���¸� ��������
				if (_battleTurn.front()->player->getStatus() == BATTLE_PLAYER_ATTACK_STANDBY) _battleTurn.front()->player->setStatus(BATTLE_PLAYER_ATTACK);
				if (_battleTurn.front()->player->getStatus() == BATTLE_PLAYER_MAGIC_ATTACK_STANDBY) _battleTurn.front()->player->setStatus(BATTLE_PLAYER_MAGIC_ATTACK);
				//�÷��̾� ���� �غ� �Ϸ�
				_battleTurn.front()->attackReady = true;
			}
			_battleTurn.front()->player->update();
			if (_battleTurn.front()->player->getTurnEnd() == true)
			{
				_battleTurn.front()->ATBcounter = 0;
				_battleTurn.front()->turnStart = false;
				_battleTurn.front()->selectAction = false;
				_battleTurn.front()->attackReady = false;
				_battleTurn.pop();
			}
		}
		else
		{
			_battleTurn.front()->enemy->update();
			if (_battleTurn.front()->enemy->getTurnEnd() == true)
			{
				_battleTurn.front()->ATBcounter = 0;
				_battleTurn.front()->turnStart = false;
				_battleTurn.pop();
			}
		}
	}
}

void BattleScene::playerMenuSelect()
{
	//�÷��̾� ATB ī���Ͱ� ���� �÷��̾� �޴� ����
	for (int i = 0; i < 4; ++i)
	{
		if (_battleCharacters[i].selectAction == true) continue;
		if (_battleCharacters[i].selectAction == false && _battleCharacters[i].ATBcounter > 65535) _battleCharacters[i].ATBcounter = 65536;
		if (_battleCharacters[i].ATBcounter > 65535 && _playerTurn == false)
		{
			_sfx01 = false;
			_playerTurn = true;
			_currentTurn = i;
			_battleCharacters[i].player->setTurnEnd(false);
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		if (_enemySelect == true)
		{
			_enemyNum--;
			SOUNDMANAGER->play("menuSelectLow", CH_EFFECT02, 1.0f);
			if (_enemyNum < 4) _enemyNum = _maxMonster + 3;
		}
		else if (_playerTurn == true)
		{
			_menuNum--;
			SOUNDMANAGER->play("menuSelectLow", CH_EFFECT02, 1.0f);
			if (_menuNum < 0) _menuNum = 4;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		if (_enemySelect == true)
		{
			_enemyNum++;
			SOUNDMANAGER->play("menuSelectLow", CH_EFFECT02, 1.0f);
			if (_enemyNum > _maxMonster + 3) _enemyNum = 4;
		}
		else if (_playerTurn == true)
		{
			_menuNum++;
			SOUNDMANAGER->play("menuSelectLow", CH_EFFECT02, 1.0f);
			if (_menuNum > 4) _menuNum = 0;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		if (_enemySelect == true)
		{
			SOUNDMANAGER->play("menuSelectLow", CH_EFFECT02, 1.0f);
			_battleCharacters[_currentTurn].enemy = _battleCharacters[_enemyNum].enemy;
			switch (_menuNum)
			{
			case(BATTLE_ATTACK):
				_battleCharacters[_currentTurn].player->setStatus(BATTLE_PLAYER_ATTACK_STANDBY);
				_battleCharacters[_currentTurn].selectAction = true;
				_battleTurn.push(&_battleCharacters[_currentTurn]);
				_enemySelect = false;
				_playerTurn = false;
				break;
			case(BATTLE_MAGIC):
				break;
			case(BATTLE_SKILL):
				break;
			case(BATTLE_ITEM):
				break;
			case(BATTLE_ESCAPE):
				break;
			}
		}
		else if (_playerTurn == true)
		{
			SOUNDMANAGER->play("menuSelectLow", CH_EFFECT02, 1.0f);
			switch (_menuNum)
			{
			case(BATTLE_ATTACK):
				_enemySelect = true;
				break;
			case(BATTLE_MAGIC):
				break;
			case(BATTLE_SKILL):
				break;
			case(BATTLE_ITEM):
				break;
			case(BATTLE_ESCAPE):
				break;
			}
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		if (_enemySelect == true)
		{
			_enemyNum = 4;
			SOUNDMANAGER->play("menuSelectLow", CH_EFFECT02, 1.0f);
			_enemySelect = false;
		}
		else if (_playerTurn == true)
		{
			_menuNum = 0;
			_sfx01 = false;
			while (1)
			{
				_currentTurn++;
				if (_currentTurn > 3) _currentTurn = 0;
				if (_battleCharacters[_currentTurn].selectAction == true) continue;
				if (_battleCharacters[_currentTurn].ATBcounter < 65535) continue;
				else break;
			}
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_TAB))
	{
		if (_playerTurn == true)
		{
			_menuNum = 0;
			_sfx01 = false;
			while (1)
			{
				_currentTurn++;
				if (_currentTurn > 3) _currentTurn = 0;
				if (_battleCharacters[_currentTurn].selectAction == true) continue;
				if (_battleCharacters[_currentTurn].ATBcounter < 65535) continue;
				else break;
			}
		}
	}
	//if (KEYMANAGER->isOnceKeyDown('R'))
	//{
	//	SOUNDMANAGER->releaseSingleSound("menuSelectLow");
	//}
	//if (KEYMANAGER->isOnceKeyDown('T'))
	//{
	//	SOUNDMANAGER->addSound("menuSelectLow", ".\\sound\\sfx\\menuSelectLow.wav", false, false);
	//}
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
			char enemyHp[128];
			wsprintf(enemyHp, "%d", _battleCharacters[i].enemy->getCurHP());
			TextOut(getMemDC(), _battleCharacters[i].enemy->getX(), _battleCharacters[i].enemy->getY() + 35, enemyHp, strlen(enemyHp));
		}
	}
}

void BattleScene::drawUI()
{
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	//UI ����
	for (int i = 0; i < 4; ++i)
	{
		IMAGEMANAGER->findImage("battleUI")->enlargeRender(getMemDC(), WINSIZEX - 250, 160 * i, 250, 160);
		RECT nameRC = { WINSIZEX - 235, 160 * i + 35, WINSIZEX - 100, 160 * i + 65 };
		RECT hpRC = { WINSIZEX - 200, 160 * i + 80, WINSIZEX - 15, 160 * i + 100 };
		RECT mpRC = { WINSIZEX - 200, 160 * i + 100, WINSIZEX - 15, 160 * i + 120 };
		RECT attackMenuRC = { WINSIZEX - 200, 160 * i + 5, WINSIZEX - 115, 160 * i + 35 };
		RECT magicMenuRC = { WINSIZEX - 200, 160 * i + 35, WINSIZEX - 115, 160 * i + 65 };
		RECT skillMenuRC = { WINSIZEX - 200, 160 * i + 65, WINSIZEX - 115, 160 * i + 95 };
		RECT itemMenuRC = { WINSIZEX - 200, 160 * i + 95, WINSIZEX - 115, 160 * i + 125 };
		RECT escapeMenuRC = { WINSIZEX - 200, 160 * i + 125, WINSIZEX - 115, 160 * i + 155 };
		char hpStr[128];
		char mpStr[128];
		wsprintf(hpStr, "ü�� : %d / %d", _battleCharacters[i].player->getCurHP(), _battleCharacters[i].player->getMaxHP());
		wsprintf(mpStr, "���� : %d / %d", _battleCharacters[i].player->getCurMP(), _battleCharacters[i].player->getMaxMP());
		switch (_battleCharacters[i].characterType)
		{
		case(TINA):
			IMAGEMANAGER->findImage("tinaFace00")->enlargeRender(getMemDC(), WINSIZEX - 100, 160 * i + 20, 84, 57);
			newFont = CreateFont(30, 0, 0, 0, 1000, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("Sandoll �̻�"));
			oldFont = (HFONT)SelectObject(getMemDC(), newFont);
			DrawText(getMemDC(), "Ƽ��", -1, &nameRC, DT_CENTER | DT_WORDBREAK);
			SelectObject(getMemDC(), oldFont);
			DeleteObject(oldFont);
			DeleteObject(newFont);
			newFont = CreateFont(20, 0, 0, 0, 1000, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("Sandoll �̻�"));
			oldFont = (HFONT)SelectObject(getMemDC(), newFont);
			DrawText(getMemDC(), hpStr, -1, &hpRC, DT_LEFT | DT_WORDBREAK);
			DrawText(getMemDC(), mpStr, -1, &mpRC, DT_LEFT | DT_WORDBREAK);
			SelectObject(getMemDC(), oldFont);
			DeleteObject(oldFont);
			DeleteObject(newFont);
			break;
		case(LOCKE):
			IMAGEMANAGER->findImage("lockeFace00")->enlargeRender(getMemDC(), WINSIZEX - 100, 160 * i + 20, 84, 57);
			newFont = CreateFont(30, 0, 0, 0, 1000, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("Sandoll �̻�"));
			oldFont = (HFONT)SelectObject(getMemDC(), newFont);
			DrawText(getMemDC(), "��ũ", -1, &nameRC, DT_CENTER | DT_WORDBREAK);
			SelectObject(getMemDC(), oldFont);
			DeleteObject(oldFont);
			DeleteObject(newFont);
			newFont = CreateFont(20, 0, 0, 0, 1000, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("Sandoll �̻�"));
			oldFont = (HFONT)SelectObject(getMemDC(), newFont);
			DrawText(getMemDC(), hpStr, -1, &hpRC, DT_LEFT | DT_WORDBREAK);
			DrawText(getMemDC(), mpStr, -1, &mpRC, DT_LEFT | DT_WORDBREAK);
			SelectObject(getMemDC(), oldFont);
			DeleteObject(oldFont);
			DeleteObject(newFont);
			break;
		case(CELES):
			IMAGEMANAGER->findImage("celesFace00")->enlargeRender(getMemDC(), WINSIZEX - 100, 160 * i + 20, 84, 57);
			newFont = CreateFont(30, 0, 0, 0, 1000, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("Sandoll �̻�"));
			oldFont = (HFONT)SelectObject(getMemDC(), newFont);
			DrawText(getMemDC(), "������", -1, &nameRC, DT_CENTER | DT_WORDBREAK);
			SelectObject(getMemDC(), oldFont);
			DeleteObject(oldFont);
			DeleteObject(newFont);
			newFont = CreateFont(20, 0, 0, 0, 1000, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("Sandoll �̻�"));
			oldFont = (HFONT)SelectObject(getMemDC(), newFont);
			DrawText(getMemDC(), hpStr, -1, &hpRC, DT_LEFT | DT_WORDBREAK);
			DrawText(getMemDC(), mpStr, -1, &mpRC, DT_LEFT | DT_WORDBREAK);
			SelectObject(getMemDC(), oldFont);
			DeleteObject(oldFont);
			DeleteObject(newFont);
			break;
		case(SHADOW):
			IMAGEMANAGER->findImage("shadowFace00")->enlargeRender(getMemDC(), WINSIZEX - 100, 160 * i + 20, 84, 57);
			newFont = CreateFont(30, 0, 0, 0, 1000, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("Sandoll �̻�"));
			oldFont = (HFONT)SelectObject(getMemDC(), newFont);
			DrawText(getMemDC(), "������", -1, &nameRC, DT_CENTER | DT_WORDBREAK);
			SelectObject(getMemDC(), oldFont);
			DeleteObject(oldFont);
			DeleteObject(newFont);
			newFont = CreateFont(20, 0, 0, 0, 1000, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("Sandoll �̻�"));
			oldFont = (HFONT)SelectObject(getMemDC(), newFont);
			DrawText(getMemDC(), hpStr, -1, &hpRC, DT_LEFT | DT_WORDBREAK);
			DrawText(getMemDC(), mpStr, -1, &mpRC, DT_LEFT | DT_WORDBREAK);
			SelectObject(getMemDC(), oldFont);
			DeleteObject(oldFont);
			DeleteObject(newFont);
			break;
		}
		//���α׷��� �� ����
		if (_battleCharacters[i].ATBcounter > 65535)
		{
			IMAGEMANAGER->findImage("progressBarComplete")->enlargeRender(getMemDC(), WINSIZEX - 197, 160 * i + 121, 144, 17);
		}
		else
		{
			IMAGEMANAGER->findImage("progressBarBottom")->enlargeRender(getMemDC(), WINSIZEX - 197, 160 * i + 121, 144 * _battleCharacters[i].ATBcounter / 65536, 17);
		}
		IMAGEMANAGER->findImage("progressBarTop")->render(getMemDC(), WINSIZEX - 210, 160 * i + 120);
		//��Ʋ �޴� ����
		newFont = CreateFont(30, 0, 0, 0, 1000, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("Sandoll �̻�"));
		oldFont = (HFONT)SelectObject(getMemDC(), newFont);
		char attackMenu[] = "����";
		char magicMenu[] = "����";
		char itemMenu[] = "������";
		char escapeMenu[] = "����";
		char tinaMenu[] = "����";
		char lockeMenu[] = "��ġ��";
		char celesMenu[] = "�������";
		char shadowMenu[] = "������";
		if (_enemySelect == true)
		{
			IMAGEMANAGER->findImage("fingerArrowLt")->render(getMemDC(), _battleCharacters[_enemyNum].enemy->getX(), _battleCharacters[_enemyNum].enemy->getY());
		}
		else if (_playerTurn == true && i == _currentTurn)
		{
			switch (_battleCharacters[_currentTurn].characterType)
			{
			case(TINA):
				IMAGEMANAGER->findImage("battleUI")->enlargeRender(getMemDC(), WINSIZEX - 250, 160 * i, 150, 160);
				DrawText(getMemDC(), attackMenu, -1, &attackMenuRC, DT_LEFT | DT_WORDBREAK);
				DrawText(getMemDC(), magicMenu, -1, &magicMenuRC, DT_LEFT | DT_WORDBREAK);
				DrawText(getMemDC(), tinaMenu, -1, &skillMenuRC, DT_LEFT | DT_WORDBREAK);
				DrawText(getMemDC(), itemMenu, -1, &itemMenuRC, DT_LEFT | DT_WORDBREAK);
				DrawText(getMemDC(), escapeMenu, -1, &escapeMenuRC, DT_LEFT | DT_WORDBREAK);
				break;
			case(LOCKE):
				IMAGEMANAGER->findImage("battleUI")->enlargeRender(getMemDC(), WINSIZEX - 250, 160 * i, 150, 160);
				DrawText(getMemDC(), attackMenu, -1, &attackMenuRC, DT_LEFT | DT_WORDBREAK);
				DrawText(getMemDC(), magicMenu, -1, &magicMenuRC, DT_LEFT | DT_WORDBREAK);
				DrawText(getMemDC(), lockeMenu, -1, &skillMenuRC, DT_LEFT | DT_WORDBREAK);
				DrawText(getMemDC(), itemMenu, -1, &itemMenuRC, DT_LEFT | DT_WORDBREAK);
				DrawText(getMemDC(), escapeMenu, -1, &escapeMenuRC, DT_LEFT | DT_WORDBREAK);
				break;
			case(CELES):
				IMAGEMANAGER->findImage("battleUI")->enlargeRender(getMemDC(), WINSIZEX - 250, 160 * i, 150, 160);
				DrawText(getMemDC(), attackMenu, -1, &attackMenuRC, DT_LEFT | DT_WORDBREAK);
				DrawText(getMemDC(), magicMenu, -1, &magicMenuRC, DT_LEFT | DT_WORDBREAK);
				DrawText(getMemDC(), celesMenu, -1, &skillMenuRC, DT_LEFT | DT_WORDBREAK);
				DrawText(getMemDC(), itemMenu, -1, &itemMenuRC, DT_LEFT | DT_WORDBREAK);
				DrawText(getMemDC(), escapeMenu, -1, &escapeMenuRC, DT_LEFT | DT_WORDBREAK);
				break;
			case(SHADOW):
				IMAGEMANAGER->findImage("battleUI")->enlargeRender(getMemDC(), WINSIZEX - 250, 160 * i, 150, 160);
				DrawText(getMemDC(), attackMenu, -1, &attackMenuRC, DT_LEFT | DT_WORDBREAK);
				DrawText(getMemDC(), magicMenu, -1, &magicMenuRC, DT_LEFT | DT_WORDBREAK);
				DrawText(getMemDC(), shadowMenu, -1, &skillMenuRC, DT_LEFT | DT_WORDBREAK);
				DrawText(getMemDC(), itemMenu, -1, &itemMenuRC, DT_LEFT | DT_WORDBREAK);
				DrawText(getMemDC(), escapeMenu, -1, &escapeMenuRC, DT_LEFT | DT_WORDBREAK);
				break;
			}
			SelectObject(getMemDC(), oldFont);
			DeleteObject(oldFont);
			DeleteObject(newFont);
			IMAGEMANAGER->findImage("fingerArrowRt")->render(getMemDC(), WINSIZEX - 240, 160 * i + 5 + (_menuNum * 30));
		}
	}
}

void BattleScene::playerFrameUpdate()
{
	//�÷��̾� �ִϸ��̼� ������ ������Ʈ
	for (int i = 0; i < 4; ++i)
	{
		_battleCharacters[i].player->animationFrameUpdate();
	}
}

void BattleScene::soundControl()
{
	SOUNDMANAGER->getChannel(CH_BGM)->getPosition(&_position, FMOD_TIMEUNIT_MS);
	if (_position >= 56800)
	{
		SOUNDMANAGER->getChannel(CH_BGM)->setPosition(4000, FMOD_TIMEUNIT_MS);
	}
	if (_sfx01 == false)
	{
		SOUNDMANAGER->play("battleMenuOpen", CH_EFFECT01, 1.0f);
		_sfx01 = true;
	}
}