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
	_bgImage = IMAGEMANAGER->findImage("�ε�޴�");
	cursorInit(CUSOR_RIGHT, 50, 38);

	_cursorXNum = 4;
	_cursorYNum = 2;

	_button = new fButton;
	_button->buttonSet("��ư����", 65, 25,  "FILE 1", 30);
	_button->buttonSet("��ư����", 255, 25, "FILE 2", 30);
	_button->buttonSet("��ư����", 445, 25, "FILE 3", 30);
	_button->buttonSet("��ư����", 635, 25, "FILE 4", 30);

	_button1 = new fButton;
	_button1->buttonSet("��ư����", 500, 187);
	_button1->buttonSet("��ư����", 500, 238);


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
		//Ŀ����ġ ����
		if (!_cursor.cursorReset)
		{
			cursorResetXY(50, 38);
		}

		_button->update();
		cursorKeyControlX(190, _cursorXNum);

		//����
		switch (_cursor.currentXNum)
		{
		case 0:
			//��ư ���ϸ��̼� Ȱ��ȭ
			_button->setVButtonAniStart(_cursor.currentXNum, true);
			for (int i = 0; i < _cursorXNum; ++i)
			{
				if (i == _cursor.currentXNum) continue;
				_button->setVButtonAniStart(i, false);
			}

			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				_button1->buttonSet("��ư����", 1000, 187);
				_button1->buttonSet("��ư��", 1000, 238);
				_saveFileSelect = true;
				_cursor.cursorReset = false;
			}
			break;
		case 1:
			//��ư ���ϸ��̼� Ȱ��ȭ
			_button->setVButtonAniStart(_cursor.currentXNum, true);
			for (int i = 0; i < _cursorXNum; ++i)
			{
				if (i == _cursor.currentXNum) continue;
				_button->setVButtonAniStart(i, false);
			}

			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				_button->buttonSet("��ư����", 1000, 187);
				_button->buttonSet("��ư��", 1000, 238);
				_saveFileSelect = true;
				_cursor.cursorReset = false;
			}
			break;
		case 2:
			//��ư ���ϸ��̼� Ȱ��ȭ
			_button->setVButtonAniStart(_cursor.currentXNum, true);
			for (int i = 0; i < _cursorXNum; ++i)
			{
				if (i == _cursor.currentXNum) continue;
				_button->setVButtonAniStart(i, false);
			}

			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				_button->buttonSet("��ư����", 1000, 187);
				_button->buttonSet("��ư��", 1000, 238);
				_saveFileSelect = true;
				_cursor.cursorReset = false;
			}
			break;
		case 3:
			//��ư ���ϸ��̼� Ȱ��ȭ
			_button->setVButtonAniStart(_cursor.currentXNum, true);
			for (int i = 0; i < _cursorXNum; ++i)
			{
				if (i == _cursor.currentXNum) continue;
				_button->setVButtonAniStart(i, false);
			}

			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				_button->buttonSet("��ư����", 1000, 187);
				_button->buttonSet("��ư��", 1000, 238);
				_saveFileSelect = true;
				_cursor.cursorReset = false;
			}
			break;
		}
	}
	else //YES&NO ��ư ����
	{
		//Ŀ����ġ ����
		if (!_cursor.cursorReset)
		{
			cursorResetXY(950, 190);
		}

		_button1->update();
		cursorKeyControlY(51, _cursorYNum);

		//����
		switch (_cursor.currentYNum)
		{
			case 0:
				//��ư ���ϸ��̼� Ȱ��ȭ
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
					SCENEMANAGER->changeScene("����ʾ�");
				}
			break;
			case 1:
				//��ư ���ϸ��̼� Ȱ��ȭ
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

