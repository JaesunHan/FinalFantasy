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
	_bgImage = IMAGEMANAGER->findImage("�����Ӹ޴�");
	cursorInit(CUSOR_RIGHT, 950, 190);

	_button = new fButton;
	_button->buttonSet("��ư����", 1000, 187);
	_button->buttonSet("��ư��", 1000, 238);






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

	//����
	switch (_cursor.currentYNum)
	{
	case 0:
		//��ư ���ϸ��̼� Ȱ��ȭ
		_button->setVButtonAniStart(0, true);
		_button->setVButtonAniStart(1, false);

		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			_button->buttonRemove();
			delete _button;
			SCENEMANAGER->changeScene("����ʾ�");
		}
		break;
	case 1:
		//��ư ���ϸ��̼� Ȱ��ȭ
		_button->setVButtonAniStart(1, true);
		_button->setVButtonAniStart(0, false);

		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			_button->buttonRemove();
			delete _button;
			SCENEMANAGER->changeScene("Ÿ��Ʋ");
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


