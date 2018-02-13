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
	_bgImage = IMAGEMANAGER->findImage("로드메뉴");
	cursorInit(CUSOR_RIGHT, 50, 38);

	_cursorXNum = 4;
	_cursorYNum = 2;

	_button = new fButton;
	_button->buttonSet("버튼파일", 65, 25,  "FILE 1", 30);
	_button->buttonSet("버튼파일", 255, 25, "FILE 2", 30);
	_button->buttonSet("버튼파일", 445, 25, "FILE 3", 30);
	_button->buttonSet("버튼파일", 635, 25, "FILE 4", 30);

	_button1 = new fButton;
	_button1->buttonSet("버튼예스", 500, 187);
	_button1->buttonSet("버튼예스", 500, 238);


	_saveFileSelect = false;



	return S_OK;
}

void loadGame::release()
{

}

void loadGame::update()
{
	cursorUpdate();
	_button1->update();

	if (!_saveFileSelect)
	{
		//커서위치 리셋
		if (!_cursor.cursorReset)
		{
			cursorResetXY(50, 38);
		}

		_button->update();
		cursorKeyControlX(190, _cursorXNum);

		//선택
		switch (_cursor.currentXNum)
		{
		case 0:
			//버튼 에니메이션 활성화
			_button->setVButtonAniStart(_cursor.currentXNum, true);
			for (int i = 0; i < _cursorXNum; ++i)
			{
				if (i == _cursor.currentXNum) continue;
				_button->setVButtonAniStart(i, false);
			}

			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				_button1->buttonSet("버튼예스", 1000, 187);
				_button1->buttonSet("버튼노", 1000, 238);
				_saveFileSelect = true;
				_cursor.cursorReset = false;
			}
			break;
		case 1:
			//버튼 에니메이션 활성화
			_button->setVButtonAniStart(_cursor.currentXNum, true);
			for (int i = 0; i < _cursorXNum; ++i)
			{
				if (i == _cursor.currentXNum) continue;
				_button->setVButtonAniStart(i, false);
			}

			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				_button->buttonSet("버튼예스", 1000, 187);
				_button->buttonSet("버튼노", 1000, 238);
				_saveFileSelect = true;
				_cursor.cursorReset = false;
			}
			break;
		case 2:
			//버튼 에니메이션 활성화
			_button->setVButtonAniStart(_cursor.currentXNum, true);
			for (int i = 0; i < _cursorXNum; ++i)
			{
				if (i == _cursor.currentXNum) continue;
				_button->setVButtonAniStart(i, false);
			}

			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				_button->buttonSet("버튼예스", 1000, 187);
				_button->buttonSet("버튼노", 1000, 238);
				_saveFileSelect = true;
				_cursor.cursorReset = false;
			}
			break;
		case 3:
			//버튼 에니메이션 활성화
			_button->setVButtonAniStart(_cursor.currentXNum, true);
			for (int i = 0; i < _cursorXNum; ++i)
			{
				if (i == _cursor.currentXNum) continue;
				_button->setVButtonAniStart(i, false);
			}

			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				_button->buttonSet("버튼예스", 1000, 187);
				_button->buttonSet("버튼노", 1000, 238);
				_saveFileSelect = true;
				_cursor.cursorReset = false;
			}
			break;
		}
	}
	else //YES&NO 버튼 선택
	{
		//커서위치 리셋
		if (!_cursor.cursorReset)
		{
			cursorResetXY(950, 190);
		}

		_button1->update();
		cursorKeyControlY(51, _cursorYNum);

		//선택
		switch (_cursor.currentYNum)
		{
			case 0:
				//버튼 에니메이션 활성화
				_button->setVButtonAniStart(_cursor.currentYNum + _cursorXNum, true);
				for (int i = _cursorXNum; i < _cursorXNum + _cursorYNum; ++i)
				{
					if (i == _cursor.currentYNum + _cursorXNum) continue;
					_button->setVButtonAniStart(i, false);
				}

				if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
				{
					_button->buttonRemove();
					delete _button;

					_saveFileSelect = false;
					SCENEMANAGER->changeScene("월드맵씬");
				}
			break;
			case 1:
				//버튼 에니메이션 활성화
				_button->setVButtonAniStart(_cursor.currentYNum + _cursorXNum, true);
				for (int i = _cursorXNum; i < _cursorXNum + _cursorYNum; ++i)
				{
					if (i == _cursor.currentYNum + _cursorXNum) continue;
					_button->setVButtonAniStart(i, false);
				}

				if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
				{
					_saveFileSelect = false;
					_cursor.cursorReset = false;
				}
			break;
		}
	}
}

void loadGame::render()
{
	_bgImage->render(getMemDC());
	_button->render();
	_button1->render();
	cursorRender();

}

