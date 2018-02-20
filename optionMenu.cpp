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
	//백그라운드 이미지
	_bgImage = IMAGEMANAGER->findImage("옵션메뉴");

	//커서
	_cursorXNum = 2;
	_cursorYNum = 6;
	cursorInit(CUSOR_RIGHT, 950, 60);


	//버튼
	_button = new fButton;
	_button->buttonSet("버튼판타지", 1000, 50, "Items", 30);
	_button->buttonSet("버튼판타지", 1000, 100, "Abilities", 30);
	_button->buttonSet("버튼판타지", 1000, 150, "Equips", 30);
	_button->buttonSet("버튼판타지", 1000, 200, "Status", 30);
	_button->buttonSet("버튼판타지", 1000, 250, "Save", 30);
	_button->buttonSet("버튼판타지", 1000, 300, "Config", 30);

	//선택한 세이브 파일 가져오기 
	fileLoad(INIDATA->loadDataInterger("gameData", "gameData", "fileNum"));


	return S_OK;
}

void optionMenu::release()
{

}

void optionMenu::update() 
{
	cursorUpdate();
	_button->update();

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

void optionMenu::render()
{
	_bgImage->render(getMemDC());
	cursorRender();
	_button->render();

	playerSlotRender();
	gameDataRender(false);  //게임 데이터(플레이장소/플레이시간/돈)
}
