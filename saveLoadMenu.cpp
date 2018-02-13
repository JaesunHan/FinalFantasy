#include "stdafx.h"
#include "saveLoadMenu.h"
#include "titleScene.h"


saveLoadMenu::saveLoadMenu()
{
}
saveLoadMenu::~saveLoadMenu()
{
}


HRESULT saveLoadMenu::init()
{
	_bgImage = IMAGEMANAGER->findImage("세이브메뉴");
	cursorInit(CUSOR_RIGHT, 950, 190);
	_cursorYNum = 2;

	_button = new fButton;
	_button->buttonSet("버튼예스", 1000, 187);
	_button->buttonSet("버튼노", 1000, 238);


	return S_OK;
}

void saveLoadMenu::release()
{

}

void saveLoadMenu::update()	
{
	cursorUpdate();
	_button->update();

	cursorKeyControlY(51, _cursorYNum);

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
				SCENEMANAGER->changeScene("타이틀");
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
				SCENEMANAGER->changeScene("로딩");
			}
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

void saveLoadMenu::render()
{
	_bgImage->render(getMemDC());
	_button->render();
	cursorRender();
}


