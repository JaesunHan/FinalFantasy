#include "stdafx.h"
#include "newGame.h"


newGame::newGame()
{
}


newGame::~newGame()
{
}


HRESULT newGame::init()
{
	_bgImage = IMAGEMANAGER->findImage("뉴게임메뉴");
	cursorInit(CUSOR_RIGHT, 950, 190);

	_button = new fButton;
	_button->buttonSet("버튼예스", 1000, 187);
	_button->buttonSet("버튼노", 1000, 238);






	return S_OK;
}

void newGame::release()
{

}

void newGame::update()
{
	cursorUpdate();
	_button->update();

	cursorKeyControlY(51, 2);

	//선택
	switch (_cursor.currentYNum)
	{
	case 0:
		//버튼 에니메이션 활성화
		_button->setVButtonAniStart(0, true);
		_button->setVButtonAniStart(1, false);

		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			_button->buttonRemove();
			delete _button;
			SCENEMANAGER->changeScene("월드맵씬");
		}
		break;
	case 1:
		//버튼 에니메이션 활성화
		_button->setVButtonAniStart(1, true);
		_button->setVButtonAniStart(0, false);

		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			_button->buttonRemove();
			delete _button;
			SCENEMANAGER->changeScene("타이틀");
		}
		break;
	}
}

void newGame::render()
{
	_bgImage->render(getMemDC());
	_button->render();
	cursorRender();
}


