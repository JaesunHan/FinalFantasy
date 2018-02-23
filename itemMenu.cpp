#include "stdafx.h"
#include "itemMenu.h"
#include "itemManager.h"


itemMenu::itemMenu()
{
}


itemMenu::~itemMenu()
{
}

HRESULT itemMenu::init()
{
	_bgImage = IMAGEMANAGER->findImage("아이템메뉴");

	//tmp 파일 가져오기 (skgFile)
	fileLoad(0, -1, true);

	//플레이어 인원수
	int saveFileNum = INIDATA->loadDataInterger("gameData", "gameData", "fileNum");
	int playerNum = INIDATA->loadDataBodyNum(saveFileNum);  //플레이어 인원수

	//--------------------------------------- 버튼 ---------------------------------------
	//----------------------------------------------------------------- 아이템
	int buttonX, buttonY;
	buttonX = 150;
	buttonY = 10;
	_button = new fButton;
	for (int i = 0; i < 3; ++i)
	{
		if (i == 0) _button->buttonSet("아이콘아이템사용", buttonX + (i * 210), buttonY);
		if (i == 1) _button->buttonSet("아이콘아이템정리", buttonX + (i * 210), buttonY);
		if (i == 2) _button->buttonSet("아이콘아이템레어", buttonX + (i * 210), buttonY);
	}


	//---------------------- 커서 ----------------------
	_cursorI = new cursor;
	_cursorXNum = 3;
	_cursorI->init(CURSOR_RIGHT, buttonX - 50, buttonY + 20);
	//---------------------- 커서 ----------------------


	//----------------------------------------------------------------- 플레이어
	buttonX = 1000;
	buttonY = 100;
	for (int i = 0; i < playerNum; ++i)
	{
		//세이브파일 이름
		TCHAR fileName[32];
		ZeroMemory(&fileName, sizeof(fileName));
		wsprintf(fileName, "saveFile%d", saveFileNum);

		//캐릭터 넘버
		TCHAR playerNum[32];
		ZeroMemory(&playerNum, sizeof(playerNum));
		wsprintf(playerNum, "player%d", i);

		//해당 캐릭터 버튼생성
		if (!strcmp(INIDATA->loadDataString(fileName, playerNum, "name"), "TINA"))
		{
			//버튼
			_button->buttonSet("버튼네임", buttonX, buttonY + (i * 65), "TINA", 20, 1);

			//플레이어 버튼 이미지
			_mTina.img = IMAGEMANAGER->findImage("miniTINA");
			_mTina.x = buttonX + 15;
			_mTina.y = buttonY + (i * 65) + 17;
			_mTina.ani = new animation;
			int arrAniPlayerImg[] = { 0, 1 };
			KEYANIMANAGER->addArrayFrameAnimation("플레이어선택", "miniTINA", arrAniPlayerImg, 2, 1, true);
			_mTina.ani = KEYANIMANAGER->findAnimation("플레이어선택");
			_mTina.aniStart = false;
		}
		else if (!strcmp(INIDATA->loadDataString(fileName, playerNum, "name"), "CELES"))
		{
			//버튼
			_button->buttonSet("버튼네임", buttonX, buttonY + (i * 65), "CELES", 20, 1);

			//플레이어 버튼 이미지
			_mLocke.img = IMAGEMANAGER->findImage("miniCELES");
			_mLocke.x = buttonX + 15;
			_mLocke.y = buttonY + (i * 65) + 17;
			_mLocke.ani = new animation;
			int arrAniPlayerImg[] = { 0, 1 };
			KEYANIMANAGER->addArrayFrameAnimation("플레이어선택", "miniCELES", arrAniPlayerImg, 2, 1, true);
			_mLocke.ani = KEYANIMANAGER->findAnimation("플레이어선택");
			_mLocke.aniStart = false;
		}
		else if (!strcmp(INIDATA->loadDataString(fileName, playerNum, "name"), "LOCKE"))
		{
			//버튼
			_button->buttonSet("버튼네임", buttonX, buttonY + (i * 65), "LOCKE", 20, 1);

			//플레이어 버튼 이미지
			_mCeles.img = IMAGEMANAGER->findImage("miniLOCKE");
			_mCeles.x = buttonX + 15;
			_mCeles.y = buttonY + (i * 65) + 17;
			_mCeles.ani = new animation;
			int arrAniPlayerImg[] = { 0, 1 };
			KEYANIMANAGER->addArrayFrameAnimation("플레이어선택", "miniLOCKE", arrAniPlayerImg, 2, 1, true);
			_mCeles.ani = KEYANIMANAGER->findAnimation("플레이어선택");
			_mCeles.aniStart = false;
		}
		else if (!strcmp(INIDATA->loadDataString(fileName, playerNum, "name"), "SHADOW"))
		{
			//버튼
			_button->buttonSet("버튼네임", buttonX, buttonY + (i * 65), "SHADOW", 20, 1);

			//플레이어 버튼 이미지
			_mShadow.img = IMAGEMANAGER->findImage("miniSHADOW");
			_mShadow.x = buttonX + 15;
			_mShadow.y = buttonY + (i * 65) +17;
			_mShadow.ani = new animation;
			int arrAniPlayerImg[] = { 0, 1 };
			KEYANIMANAGER->addArrayFrameAnimation("플레이어선택", "miniSHADOW", arrAniPlayerImg, 2, 1, true);
			_mShadow.ani = KEYANIMANAGER->findAnimation("플레이어선택");
			_mShadow.aniStart = false;
		}
	}

	//---------------------------------------------------------------- 아이템


	//_iM->saveInventory("skgFile");
	//_iM->loadInventory("skgFile");
	itemButtonSet(_iM->getItemInventorySize());



	//--------------------------------------- 버튼 ---------------------------------------
	_itemButtonOn = false;  //아이템버튼 활성화 여부
	_charButtonOn = false;  //캐릭터버튼 활성화 여부




	return S_OK;
}

void itemMenu::release()
{

}

void itemMenu::update()
{
	//커서
	_cursorI->update();
	//버튼
	_button->update();


	//커서 컨트롤X: 메뉴버튼
	if (!_itemButtonOn)
	{
		_cursorI->keyControlX(210, _cursorXNum);

		buttonOnActive();
	}
	else
	{
		if (!_charButtonOn)
		{
			_cursorI->keyControlXY(250, 65, 3, 5);

			//선택
			buttonOnActiveItem();
		}
		else
		{
			_cursorI->keyControlY(65, 4);

			buttonOnActiveCharacter();
		}
		
	}



	//옵션 메뉴가기
	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		_button->buttonRemove();
		delete _button;
		SCENEMANAGER->changeScene("옵션");
	}
}

void itemMenu::render()
{
	_bgImage->render(getMemDC());

	//--------------------------------- 버튼 ---------------------------------
	//버튼
	_button->render();             
	//플레이어 버튼 이미지
	_mTina.img->aniRender(getMemDC(), _mTina.x, _mTina.y, _mTina.ani);
	_mLocke.img->aniRender(getMemDC(), _mLocke.x, _mLocke.y, _mLocke.ani);
	_mCeles.img->aniRender(getMemDC(), _mCeles.x, _mCeles.y, _mCeles.ani);
	_mShadow.img->aniRender(getMemDC(), _mShadow.x, _mShadow.y, _mShadow.ani);
	//--------------------------------- 버튼 ---------------------------------

	itemDescriptionRender(_cursorI->getCursorPos());      //아이템 설명

	_cursorI->render();

}


//버튼 에니메이션 시작
void itemMenu::buttonOnActive()
{
	//버튼 에니메이션 활성화
	_button->setVButtonAniStart(_cursorI->getCursorXNum(), true);
	for (int i = 0; i < _cursorXNum; ++i)
	{
		if (i == _cursorI->getCursorXNum()) continue;
		_button->setVButtonAniStart(i, false);
	}


	//상단 메뉴버튼 선택시
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		_cursorI->init(CURSOR_RIGHT, 50 , 160);
		_itemButtonOn = true;
	}

}

void itemMenu::buttonOnActiveItem()
{
	//버튼 에니메이션 활성화
	_button->setVButtonAniStart(_cursorI->getCursorPos() + 7, true);
	for (int i = 7; i < _button->getButtonNum(); ++i)
	{
		if (i == _cursorI->getCursorPos() + 7) continue;
		_button->setVButtonAniStart(i, false);
	}


	//아이템 버튼 선택시
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		_cursorI->init(CURSOR_RIGHT, 950, 120);
		_charButtonOn = true;
	}


	//나가기
	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		_cursorI->init(CURSOR_RIGHT, 150 - 50, 10 + 20);
		_itemButtonOn = false;
	}
}

void itemMenu::buttonOnActiveCharacter()
{
	//버튼 에니메이션 활성화
	_button->setVButtonAniStart(_cursorI->getCursorYNum() + 3, true);
	for (int i = 3; i < 7; ++i)
	{
		if (i == _cursorI->getCursorYNum() + 3) continue;
		_button->setVButtonAniStart(i, false);
	}

	//아이템 버튼 선택시
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
	

	}

	//캐릭터 선택
	switch (_cursorI->getCursorPos())
	{
		case 0:

		break;
		case 1:

		break;
		case 2:

		break;
		case 3:

		break;
		case 4:

		break;
	}

	//나가기
	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		_cursorI->init(CURSOR_RIGHT, 50, 160);
		_charButtonOn = false;
	}
}

//아이템 버튼 셋팅
void itemMenu::itemButtonSet(int buttonNum)
{
	//예외처리: 아이템이 없으면...
	if (buttonNum <= 0) return;

	int buttonX = 100;
	int buttonY = 150;



	//버튼
	for (int i = 0; i < buttonNum; ++i)
	{
		int intervalX = 250;
		int intervalY = 70;

		switch (i)
		{
			case 0: case 1: case 2:
				//아이템 버튼 & 이름
				_button->buttonSet("버튼아이템힐", buttonX + (i * intervalX),
					buttonY, _iM->getVItem()[itemGetNum(_iM->getItemVNum(i))]->getItemName(), 20, 2, true, _iM->getItemCount(i));
			break;
			case 3: case 4: case 5:
				_button->buttonSet("버튼아이템힐", buttonX + ((i - 3) * intervalX),
					buttonY + (1 * intervalY), _iM->getVItem()[itemGetNum(_iM->getItemVNum(i))]->getItemName(), 20, 2, true, _iM->getItemCount(i));
			break;
			case 6: case 7: case 8:
				_button->buttonSet("버튼아이템힐", buttonX + ((i - 6) * intervalX),
					buttonY + (2 * intervalY), _iM->getVItem()[itemGetNum(_iM->getItemVNum(i))]->getItemName(), 20, 2, true, _iM->getItemCount(_iM->getVItem()[i]->getItemNumber()));
			break;
			case 9: case 10: case 11:
				_button->buttonSet("버튼아이템힐", buttonX + ((i - 9) * intervalX),
					buttonY + (3 * intervalY), _iM->getVItem()[itemGetNum(_iM->getItemVNum(i))]->getItemName(), 20, 2, true, _iM->getItemCount(_iM->getVItem()[i]->getItemNumber()));
			break;
			case 12: case 13: case 14:
				_button->buttonSet("버튼아이템힐", buttonX + ((i - 12) * intervalX),
					buttonY + (4 * intervalY), _iM->getVItem()[itemGetNum(_iM->getItemVNum(i))]->getItemName(), 20, 2, true, _iM->getItemCount(_iM->getVItem()[i]->getItemNumber()));
			break;
			case 15: case 16: case 17:
				_button->buttonSet("버튼아이템힐", buttonX + ((i - 15) * intervalX),
					buttonY + (5 * intervalY), _iM->getVItem()[itemGetNum(_iM->getItemVNum(i))]->getItemName(), 20, 2, true, _iM->getItemCount(_iM->getVItem()[i]->getItemNumber()));
			break;
		}
	}

}


void itemMenu::itemDescriptionRender(int itemNum)
{
	textPrint(getMemDC(), _iM->getVItem()[itemGetNum(_iM->getItemVNum(itemNum))]->getItemDescription(), 50, 520, 20, 20, "HY견고딕", COLOR_BLUE, false);
}