#include "stdafx.h"
#include "optionMenu.h"


optionMenu::optionMenu()
{
}


optionMenu::~optionMenu()
{
}


HRESULT optionMenu::init()
{
	//==============뉴게임을 했을시 타임이 먹는다!============
	_gameEndTime = TIMEMANAGER->getWorldTime();
	_gameTotalTime = _gameEndTime - _gameStartTime;
	//==============뉴게임을 했을시 타임이 먹는다!============

	//백그라운드 이미지
	_bgImage = IMAGEMANAGER->findImage("옵션메뉴");

	//커서
	_cursorXNum = 2;
	_cursorYNum = 6;
	cursorInit(CUSOR_RIGHT, 950, 60);
	_cursorReset = false;


	//버튼
	_button = new fButton;
	_button->buttonSet("버튼판타지", 1000, 50, "Items", 30);
	_button->buttonSet("버튼판타지", 1000, 100, "Abilities", 30);
	_button->buttonSet("버튼판타지", 1000, 150, "Equips", 30);
	_button->buttonSet("버튼판타지", 1000, 200, "Status", 30);
	_button->buttonSet("버튼판타지", 1000, 250, "Save", 30);
	_button->buttonSet("버튼판타지", 1000, 300, "Config", 30);

	//tmp 파일 가져오기 (skgFile)
	fileLoad(0, -1, true);

	//슬롯변경
	_changeSlotNum = 0;
	_slotSelectCount = 2;
	_previousSlotNum = 0;
	_isSlotReload = false;

	//사운드
	SOUNDMANAGER->addSound("battleMenuOpen", ".\\sound\\sfx\\battleMenuOpen.wav", false, false);
	SOUNDMANAGER->addSound("menuSelectLow", ".\\sound\\sfx\\menuSelectLow.wav", false, false);


	return S_OK;
}

void optionMenu::release()
{

}

void optionMenu::update() 
{
	_gameTotalTime += TIMEMANAGER->getElapsedTime();

	cursorUpdate();
	_button->update();

	//커서 컨트롤X  
	cursorKeyControlX(920, _cursorXNum, true);

	if (_cursor.currentXNum == 0)
	{
		if (!_cursorReset)
		{
			//슬롯 에니메이션 끄기
			for (int i = 0; i < 4; ++i)
			{
				playerSlotAniStart(i, false);
				playerSlotUpdate();
			}

			cursorResetXY(950, 60);
			_cursor.currentYNum = 0;
			_cursorReset = true;
		}

		cursorKeyControlY(50, _cursorYNum);

		//선택
		switch (_cursor.currentYNum)
		{
		case 0:
			//버튼 에니메이션 활성화
			_button->setVButtonAniStart(_cursor.currentYNum, true);
			for (int i = 0; i < _cursorYNum; ++i)
			{
				if (i == _cursor.currentYNum) continue;
				_button->setVButtonAniStart(i, false);
			}

			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				_button->buttonRemove();
				delete _button;
				SCENEMANAGER->changeScene("아이템");
			}
			break;
		case 1:
			//버튼 에니메이션 활성화
			_button->setVButtonAniStart(_cursor.currentYNum, true);
			for (int i = 0; i < _cursorYNum; ++i)
			{
				if (i == _cursor.currentYNum) continue;
				_button->setVButtonAniStart(i, false);
			}

			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				_button->buttonRemove();
				delete _button;
				SCENEMANAGER->changeScene("능력치");
			}
			break;
		case 2:
			//버튼 에니메이션 활성화
			_button->setVButtonAniStart(_cursor.currentYNum, true);
			for (int i = 0; i < _cursorYNum; ++i)
			{
				if (i == _cursor.currentYNum) continue;
				_button->setVButtonAniStart(i, false);
			}

			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				_button->buttonRemove();
				delete _button;
				SCENEMANAGER->changeScene("장비");
			}
			break;
		case 3:
			//버튼 에니메이션 활성화
			_button->setVButtonAniStart(_cursor.currentYNum, true);
			for (int i = 0; i < _cursorYNum; ++i)
			{
				if (i == _cursor.currentYNum) continue;
				_button->setVButtonAniStart(i, false);
			}

			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				_button->buttonRemove();
				delete _button;
				SCENEMANAGER->changeScene("상태");
			}
			break;
		case 4:
			//버튼 에니메이션 활성화
			_button->setVButtonAniStart(_cursor.currentYNum, true);
			for (int i = 0; i < _cursorYNum; ++i)
			{
				if (i == _cursor.currentYNum) continue;
				_button->setVButtonAniStart(i, false);
			}

			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				_button->buttonRemove();
				delete _button;
				SCENEMANAGER->changeScene("세이브로드");
			}
			break;
		case 5:
			//버튼 에니메이션 활성화
			_button->setVButtonAniStart(_cursor.currentYNum, true);
			for (int i = 0; i < _cursorYNum; ++i)
			{
				if (i == _cursor.currentYNum) continue;
				_button->setVButtonAniStart(i, false);
			}

			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				_button->buttonRemove();
				delete _button;
				SCENEMANAGER->changeScene("사운드");
			}
			break;
		}

		//옵션메뉴 나가기
		if (KEYMANAGER->isOnceKeyDown(VK_BACK))
		{
			_button->buttonRemove();
			delete _button;
			SCENEMANAGER->changeScene("월드맵씬", false);
		}
	}
	else
	{
		if (_cursorReset)
		{
			//버튼 에니메이션 끄기
			for (int i = 0; i < _cursorYNum; ++i)
			{
				_button->setVButtonAniStart(i, false);
			}

			cursorResetXY(30, 150);
			_cursor.currentYNum = 0;
			_cursorReset = false;
		}

		cursorKeyControlY(137, 4);
		playerSlotUpdate();

		//선택
		switch (_cursor.currentYNum)
		{
			case 0:
				//버튼 에니메이션 활성화
				slotAniOn();
				
				//슬롯 변경
				slotChangeKey();
			break;
			case 1:
				//버튼 에니메이션 활성화
				slotAniOn();

				//슬롯선택
				slotChangeKey();
			break;
			case 2:
				//버튼 에니메이션 활성화
				slotAniOn();

				//슬롯선택
				slotChangeKey();
			break;
			case 3:
				//버튼 에니메이션 활성화
				slotAniOn();

				//슬롯선택
				slotChangeKey();
			break;
		}

		//템프파일 로드
		if (_isSlotReload)
		{
			fileLoad(0, -1, true);
			_isSlotReload = false;
		}
	}


}

void optionMenu::render()
{
	_bgImage->render(getMemDC());
	_button->render();
	playerSlotRender();
	cursorRender();

	gameDataRender(false);  //게임 데이터(플레이장소/플레이시간/돈)
	gamePlayTime();			//게임 플레이 타임


	//test
	char buff[32];
	textPrint(getMemDC(), itoa(_changeSlotNum, buff, 10), 20, 100);
	textPrint(getMemDC(), itoa(_previousSlotNum, buff, 10), 20, 120);
	textPrint(getMemDC(), itoa(_cursor.currentYNum, buff, 10), 20, 140);
}

void optionMenu::slotAniOn()
{
	if (_changeSlotNum != _cursor.currentYNum)
	{
		playerSlotAniStart(_cursor.currentYNum, true);

		for (int i = 0; i < 4; ++i)
		{
			if (i == _cursor.currentYNum) continue;
			playerSlotAniStart(i, false);
		}
	}
}

void optionMenu::slotChangeKey()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		_slotSelectCount--;

		if (_slotSelectCount <= 0)
		{
			_changeSlotNum = slotSelect(_cursor.currentYNum);
			slotChange(_cursor.currentYNum, _previousSlotNum);

			//초기화
			_slotSelectCount = 2;
			_isSlotReload = true;
		}
		else
		{
			_previousSlotNum = _cursor.currentYNum;
		}
	}
}