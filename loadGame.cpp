#include "stdafx.h"
#include "loadGame.h"


loadGame::loadGame()
{
}


loadGame::~loadGame()
{
}


HRESULT loadGame::init()
{
	_bgImage = IMAGEMANAGER->findImage("로드게임메뉴");
	cursorInit(CUSOR_RIGHT, 950, 190);

	_button = new fButton;
	_button->buttonSet("버튼예스", 1000, 187);
	_button->buttonSet("버튼노", 1000, 238);






	return S_OK;
}

void loadGame::release()
{

}

void loadGame::update()
{
	cursorUpdate();
	_button->update();

	cursorKeyControl(51, 2);

	//선택
	switch (_cursor.currentNum)
	{
	case 0:
		//버튼 에니메이션 활성화
		_button->setVButtonAniStart(0, true);
		_button->setVButtonAniStart(1, false);

		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			_button->buttonRemove();
			delete _button;
			SCENEMANAGER->changeScene("타이틀");
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
			SCENEMANAGER->changeScene("로딩");
		}
		break;
	}
}

void loadGame::render()
{
	_bgImage->render(getMemDC());
	_button->render();
	cursorRender();
}

