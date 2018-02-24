#include "stdafx.h"
#include "worldMapScene.h"
#include "itemManager.h"
#include "optionMenu.h"

worldMapScene::worldMapScene()
{
}


worldMapScene::~worldMapScene()
{
}

HRESULT worldMapScene::init()
{
	//==============�������� ������ Ÿ���� �Դ´�!============
	_gameStartTime = TIMEMANAGER->getWorldTime();
	//==============�������� ������ Ÿ���� �Դ´�!============

	SOUNDMANAGER->addSound("worldMapBGM", ".//sound//worldMapSound//01. Tina.mp3", true, true);
	SOUNDMANAGER->addSound("encounterSound", ".//sound//worldMapSound//encounter.wav", false, false);
	SOUNDMANAGER->play("worldMapBGM", CH_BGM, 1.0f);
	CAMERAMANAGER->init(getMemDC());
	CAMERAMANAGER->createDC(PointMake(TILE_SIZEX, TILE_SIZEY), PointMake(30, 20));

	_openBox = IMAGEMANAGER->addImage("���¹ڽ�", ".//image//enemyImg//treasureBoxOpen.bmp", 31, 29, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("messageBox_small", ".//image//userInterface//messageBox_small.bmp", 400, 93, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("���̵��̹���", ".//image//userInterface//sideImage3.bmp", 240, 640, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���̵��̹���1", ".//image//userInterface//sideImage4.bmp", 240, 640, true, RGB(255, 0, 255));
	_sideImgChange = RND->getFromFloatTo(1, 2);
	_worldMap = new generalMap;
	_worldMap->init(".//50X50.map");

	_worldMapPlayer = new worldMapPlayer;
	_worldMapPlayer->init(200, 150);
	_worldMapPlayer->setCurMapAddressLink(_worldMap);

	//_npcManager = new npcManager;
	//_npcManager->init();

	_wMEM = new worldMapEnemyManager;
	_wMEM->init();

	_encountNum = 0;

	_isEscape = false;
	_isCollision = false;
	_isEncounter = false;
	_isOpenBox = false;
	_isNotEnemyVector = false;
	_isGetGongChi = false;
	_isDoBattleEncount = false;
	_getIsBoss = false;
	_isEnemyEncount = false;
	_enemyNum = -1;

	_focus = FOCUS_PLAYER;

	AddFontResourceEx(
		"SDMiSaeng.ttf", 	// font file name
		FR_PRIVATE,         // font characteristics
		NULL            	// reserved
	);


	//���ʹ� �����ŭ ��� �÷��� �ž��ش�.
	for (int i = 0; i < _wMEM->getVWME().size(); ++i)
	{
		_wMEM->getVWME()[i]->setEnemyAddressLinkWithWM(_worldMap);
		_wMEM->getVWME()[i]->setEnemyAddressLinkWihtPlayer(_worldMapPlayer);
	}

	return S_OK;
}

void worldMapScene::release()
{
	SAFE_DELETE(_worldMap);
	SAFE_DELETE(_worldMapPlayer);

	SOUNDMANAGER->releaseAllSound();
}

void worldMapScene::update()
{
	if (!SOUNDMANAGER->isPlaySound(CH_BGM))
	{
		SOUNDMANAGER->addSound("worldMapBGM", ".//sound//worldMapSound//01. Tina.mp3", true, true);
		SOUNDMANAGER->addSound("encounterSound", ".//sound//worldMapSound//encounter.wav", false, false);
		SOUNDMANAGER->play("worldMapBGM", CH_BGM, 1.0f);
		
	}

	if (_focus == FOCUS_PLAYER)
	{
		_worldMap->update();
		_worldMapPlayer->update();
		//_npcManager->update();
		_wMEM->update();

		//Z������
		//�÷��̾� ���� ��ǥ�� �޾Ƽ� ��� npc�Ŵ��������� �־��ش�.
		//_npcManager->setPlayerPos(_worldMapPlayer->getWorldMapPlayerPoint());


		if (_isEscape)
		{
			if (_isNotEnemyVector)
			{
				_worldMapPlayer->successEscape();
				_enemyNum = -1;
				_isEscape = false;
			}
			else successEscape();
		}
		else
		{
			for (int i = 0; i < _wMEM->getVWME().size(); ++i)
			{
				//���࿡ ���ʹ̶� �ε��ƴµ� arry�ѹ� i�� �ӽ������ enemyNum�� ����, �������ڰ� �ƴѰ�쿡�� 
				if (i == _enemyNum && !_wMEM->getVWME()[i]->getIsBox())
				{
					//���Ϳ��� ���ʹ̸� ���������.
					_wMEM->worldEmenyDelete(i);
					_enemyNum = -1;
				}
			}
		}

		enterTownMap();
		getCollision();
		battleEncount();
		doBattleEncount();
		savePoint();
	}
	else if (_focus == FOCUS_MESSAGEBOX)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			_focus = FOCUS_PLAYER;
		}
	}
	else if (_focus == FOCUS_ENEMYENCOUNT)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			_focus = FOCUS_PLAYER;
		}
	}
	else if (_focus == FOCUS_BATTLEENCOUNT)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			_focus = FOCUS_PLAYER;
			_isDoBattleEncount = true;
		}
	}


	

}

void worldMapScene::render()
{
	switch(_sideImgChange)
	{
	case 1:
		IMAGEMANAGER->findImage("���̵��̹���")->render(getMemDC(), 960, 0);
		break;

	case 2:
		IMAGEMANAGER->findImage("���̵��̹���1")->render(getMemDC(), 960, 0);
	break;
	}
	
	_worldMap->render(CAMERAMANAGER->getCameraDC());

	_wMEM->beforeRender(CAMERAMANAGER->getCameraDC(), CAMERAMANAGER->getMovePt());
	//������Ʈ���� ���� �÷��̾��� �ǽð� ��ǥ�� NPC�� ���Ͽ� 
	//�÷��̾�� ���� �׷��ִ� �̹��� -> �÷��̾� �̹��� -> �÷��̾�� ������ �׷��ִ� �̹��� ������ ������ �Ѵ�.
	//_npcManager->beforeRender(CAMERAMANAGER->getCameraDC(), CAMERAMANAGER->getMovePt());
	
	//_npcManager->afterRender(CAMERAMANAGER->getCameraDC(), CAMERAMANAGER->getMovePt());
	/*if (_isOpenBox)
	{
		IMAGEMANAGER->findImage("���¹ڽ�")->render(CAMERAMANAGER->getCameraDC(), CAMERAMANAGER->getMovePt().x- tempPoint.x, CAMERAMANAGER->getMovePt().y-tempPoint.y);
	}*/
	_worldMapPlayer->render(CAMERAMANAGER->getCameraDC(), CAMERAMANAGER->getMovePt());
	_wMEM->afterRender(CAMERAMANAGER->getCameraDC(), CAMERAMANAGER->getMovePt());

	

	CAMERAMANAGER->render(getMemDC());

	if (_focus == FOCUS_MESSAGEBOX)
	{
		IMAGEMANAGER->render("messageBox_small", getMemDC(), 300, 250);
					//������, ���ڳ���, ���ڱ���, ���ڹ���, ���� 		
		HFONT newFont = CreateFont(30, 0, 0, 0, 600, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("Sandoll �̻�"));
		HFONT oldFont = (HFONT)SelectObject(getMemDC(), newFont);

		SetTextColor(getMemDC(), RGB(40, 5, 0));
		sprintf(str, "������ ���� : ��ġ��(��) ���ߴ�!");
		TextOut(getMemDC(), 350, 285, str, strlen(str));

		DeleteObject(newFont);
		newFont = CreateFont(20, 0, 0, 0, 1000, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("Sandoll �̻�"));
		SelectObject(getMemDC(), newFont);
		SetTextColor(getMemDC(), RGB(255, 255, 255));

		SelectObject(getMemDC(), oldFont);
		DeleteObject(oldFont);
		DeleteObject(newFont);
	}
	
	if (_focus == FOCUS_ENEMYENCOUNT)
	{
		IMAGEMANAGER->render("messageBox_small", getMemDC(), 300, 250);
		//������, ���ڳ���, ���ڱ���, ���ڹ���, ���� 		
		HFONT newFont = CreateFont(30, 0, 0, 0, 600, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("Sandoll �̻�"));
		HFONT oldFont = (HFONT)SelectObject(getMemDC(), newFont);

		SetTextColor(getMemDC(), RGB(40, 5, 0));
		sprintf(str, "�浹�� ���Ͱ� ���ϰ� ���Ǹ� �巯����!");
		TextOut(getMemDC(), 350, 285, str, strlen(str));

		DeleteObject(newFont);
		newFont = CreateFont(20, 0, 0, 0, 1000, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("Sandoll �̻�"));
		SelectObject(getMemDC(), newFont);
		SetTextColor(getMemDC(), RGB(255, 255, 255));

		SelectObject(getMemDC(), oldFont);
		DeleteObject(oldFont);
		DeleteObject(newFont);
	}

	if (_focus == FOCUS_BATTLEENCOUNT)
	{
		if (_encountNum == 1) battleEncountRender1();
		if (_encountNum == 2) battleEncountRender2();
		if (_encountNum == 3) battleEncountRender3();
	}

	//_worldMap->render(getMemDC());
	//
	//_wMEM->render(getMemDC());
	////������Ʈ���� ���� �÷��̾��� �ǽð� ��ǥ�� NPC�� ���Ͽ� 
	////�÷��̾�� ���� �׷��ִ� �̹��� -> �÷��̾� �̹��� -> �÷��̾�� ������ �׷��ִ� �̹��� ������ ������ �Ѵ�.
	//_npcManager->beforeRender(getMemDC());
	//_worldMapPlayer->render(getMemDC());
	//_npcManager->afterRender(getMemDC());
}

void worldMapScene::getCollision()
{
	for (int i = 0; i < _wMEM->getVWME().size(); ++i)
	{
		if (_wMEM->getVWME()[i]->getIsCollision())
		{
			//50%Ȯ���� �����Ǿ��� �������ڸ�
			if (_wMEM->getVWME()[i]->getIsBox())
			{
				//�������ڿ� ���� ���ٰ���
				if (((worldMapTreasureBox*)_wMEM->getVWME()[i])->getIsOpen()) break;
				
				//�浹�� �༮�� �ε����� ������ �����Ѵ�.
				_enemyNum = i;
				//tempPoint = _wMEM->getVWME()[i]->getWorldMapEnemyPoint();
				getGongChi();
				_focus = FOCUS_MESSAGEBOX;
				
				//���� ���� �̹��� ���� 
				//���� ������ ȹ�� �̹��� ���� 
				//���ڸ� ���Ϳ��� �����ְ�. <- ���Ϳ��� �����ִ°� ������ �ƴϸ� �׳� ���� �̹��� �״�� �ִ°� �������� �����غ�����.
				//_isOpenBox = true;
				//_wMEM->worldEmenyDelete(i);
				break;
			}
			else
			{
				//�浹�� �༮�� �ε����� ������ �����Ѵ�.
				_enemyNum = i;
				_getIsBoss = _wMEM->getVWME()[i]->getIsBoss();
				//SOUNDMANAGER->stop(CH_BGM)
				if (!_isEncounter)
				{
					_isEncounter = true;
					SOUNDMANAGER->play("encounterSound", CH_ENCOUNTER, 1.0f);
				}
				SCENEMANAGER->changeSceneType1("��Ʋ��");
				_wMEM->getVWME()[i]->setIsCollision(false);
				break;
			}
		}
	}

}

void worldMapScene::successEscape()
{
	_wMEM->getVWME()[_enemyNum]->setIsCollision(false);
	_worldMapPlayer->successEscape();
	_enemyNum = -1;
	_isEscape = false;
}

void worldMapScene::enterTownMap()
{
	if (_worldMapPlayer->getIsEnter())
	{
		_curCameraPos = CAMERAMANAGER->getMovePt();

		SOUNDMANAGER->releaseAllSound();
		SCENEMANAGER->changeSceneType1("Ÿ��ʾ�");
		INIDATA->addData("gameData", "stage", "TOWN");
		INIDATA->iniSave("skgFile");
		//SOUNDMANAGER->stop(CH_BGM);
		//_worldMapPlayer->setWorldMapPlayerTempPoint(_worldMapPlayer->getWorldMapPlayerPoint());
		_worldMapPlayer->setWorldMapPlayerPoint(PointMake(_worldMapPlayer->getWorldMapPlayerPoint().x - 100, _worldMapPlayer->getWorldMapPlayerPoint().y));

		_curPlayerPos = _worldMapPlayer->getWorldMapPlayerPoint();
	}
	_worldMapPlayer->setIsEnter(false);

}

void worldMapScene::setPlayerPos(void)
{
	_worldMapPlayer->setWorldMapPlayerPoint(_curPlayerPos);
	_worldMap->setCamera();
	CAMERAMANAGER->setMovePt(_curCameraPos);
}

void worldMapScene::getGongChi()
{
	//�� �Լ��� �������ڸ� �������� �κ��丮�� ��ġ �������� �߰����ִ� �Լ�.
	if (!_isGetGongChi)
	{
		_im->changeWeaponNumber("KKongChi", 1);
	}
	_isGetGongChi = true;
}



void worldMapScene::battleEncount()
{
	if (_worldMapPlayer->getIsEncount())
	{
		_encountNum = RND->getFromFloatTo(1, 3);
		_focus = FOCUS_BATTLEENCOUNT;
	}	
	
}

void worldMapScene::doBattleEncount()
{
	/*if (_worldMapPlayer->getIsEncount())
	{*/
	if (_isDoBattleEncount)
	{
		_isNotEnemyVector = true;
		if (!_isEncounter)
		{
			_isEncounter = true;
			SOUNDMANAGER->play("encounterSound", CH_ENCOUNTER, 1.0f);
		}
		SCENEMANAGER->changeSceneType1("��Ʋ��");
	}
	/*}*/
	_worldMapPlayer->setIsEncount(false);
	_isDoBattleEncount = false;
}

void worldMapScene::savePoint()
{
	if (_worldMapPlayer->getIsSavePoint())
	{
		_optionMenu->setIsSavePoint(true);
		_worldMapPlayer->setIsSavePoint(false);
	}
	
}

void worldMapScene::battleEncountRender1()
{
	IMAGEMANAGER->render("messageBox_small", getMemDC(), 300, 250);
	//������, ���ڳ���, ���ڱ���, ���ڹ���, ���� 		
	HFONT newFont = CreateFont(30, 0, 0, 0, 600, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("Sandoll �̻�"));
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), newFont);

	SetTextColor(getMemDC(), RGB(40, 5, 0));
	sprintf(str, "���ƴ� ���Ͷ��!!!");
	TextOut(getMemDC(), 350, 285, str, strlen(str));

	DeleteObject(newFont);
	newFont = CreateFont(20, 0, 0, 0, 1000, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("Sandoll �̻�"));
	SelectObject(getMemDC(), newFont);
	SetTextColor(getMemDC(), RGB(255, 255, 255));

	SelectObject(getMemDC(), oldFont);
	DeleteObject(oldFont);
	DeleteObject(newFont);
}

void worldMapScene::battleEncountRender2()
{
	IMAGEMANAGER->render("messageBox_small", getMemDC(), 300, 250);
	//������, ���ڳ���, ���ڱ���, ���ڹ���, ���� 		
	HFONT newFont = CreateFont(30, 0, 0, 0, 600, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("Sandoll �̻�"));
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), newFont);

	SetTextColor(getMemDC(), RGB(40, 5, 0));
	sprintf(str, "�ҲǱ��� ���͸� ������!");
	TextOut(getMemDC(), 350, 285, str, strlen(str));

	DeleteObject(newFont);
	newFont = CreateFont(20, 0, 0, 0, 1000, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("Sandoll �̻�"));
	SelectObject(getMemDC(), newFont);
	SetTextColor(getMemDC(), RGB(255, 255, 255));

	SelectObject(getMemDC(), oldFont);
	DeleteObject(oldFont);
	DeleteObject(newFont);
}

void worldMapScene::battleEncountRender3()
{
	IMAGEMANAGER->render("messageBox_small", getMemDC(), 300, 250);
	//������, ���ڳ���, ���ڱ���, ���ڹ���, ���� 		
	HFONT newFont = CreateFont(30, 0, 0, 0, 600, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("Sandoll �̻�"));
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), newFont);

	SetTextColor(getMemDC(), RGB(40, 5, 0));
	sprintf(str, "�ҲǱ��� ���������� ������!");
	TextOut(getMemDC(), 350, 285, str, strlen(str));

	DeleteObject(newFont);
	newFont = CreateFont(20, 0, 0, 0, 1000, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("Sandoll �̻�"));
	SelectObject(getMemDC(), newFont);
	SetTextColor(getMemDC(), RGB(255, 255, 255));

	SelectObject(getMemDC(), oldFont);
	DeleteObject(oldFont);
	DeleteObject(newFont);
}
