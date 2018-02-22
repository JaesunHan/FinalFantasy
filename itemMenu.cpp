#include "stdafx.h"
#include "itemMenu.h"


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
	_cursorXNum = 3;
	cursorInit(CUSOR_RIGHT, buttonX - 50, buttonY + 20);
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

	//----------------------------------------------------------------- 아이템
	itemButtonSet(0);



	//--------------------------------------- 버튼 ---------------------------------------




	return S_OK;
}

void itemMenu::release()
{

}

void itemMenu::update()
{
	//커서
	cursorUpdate();

	//커서 컨트롤X  
	cursorKeyControlX(210, _cursorXNum);

	//버튼
	_button->update();

	//선택
	switch (_cursor.currentXNum)
	{
		case 0:
			buttonOnActive();
		break;
		case 1:
			buttonOnActive();
		break;
		case 2:
			buttonOnActive();
		break;
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

	cursorRender();                //커서
}


//버튼 에니메이션 시작
void itemMenu::buttonOnActive()
{
	//버튼 에니메이션 활성화
	_button->setVButtonAniStart(_cursor.currentXNum, true);
	for (int i = 0; i < _cursorXNum; ++i)
	{
		if (i == _cursor.currentXNum) continue;
		_button->setVButtonAniStart(i, false);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{

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
				_button->buttonSet("버튼아이템힐", buttonX + (i * intervalX),
					buttonY, "Positon", 30, 1);
			break;
			case 3: case 4: case 5:
				_button->buttonSet("버튼아이템힐", buttonX + ((i - 3) * intervalX),
					buttonY + (1 * intervalY), "Positon", 30, 1);
			break;
			case 6: case 7: case 8:
				_button->buttonSet("버튼아이템힐", buttonX + ((i - 6) * intervalX),
					buttonY + (2 * intervalY), "Positon", 30, 1);
			break;
			case 9: case 10: case 11:
				_button->buttonSet("버튼아이템힐", buttonX + ((i - 9) * intervalX),
					buttonY + (3 * intervalY), "Positon", 30, 1);
			break;
			case 12: case 13: case 14:
				_button->buttonSet("버튼아이템힐", buttonX + ((i - 12) * intervalX),
					buttonY + (4 * intervalY), "Positon", 30, 1);
			break;
			case 15: case 16: case 17:
				_button->buttonSet("버튼아이템힐", buttonX + ((i - 15) * intervalX),
					buttonY + (5 * intervalY), "Positon", 30, 1);
			break;
		}
	}



}