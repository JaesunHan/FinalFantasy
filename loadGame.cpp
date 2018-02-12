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
	_bgImage = IMAGEMANAGER->findImage("�ε���Ӹ޴�");
	cursorInit(CUSOR_RIGHT, 950, 190);

	_button = new fButton;
	_button->buttonSet("��ư����", 1000, 187);
	_button->buttonSet("��ư��", 1000, 238);






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

	//����
	switch (_cursor.currentNum)
	{
	case 0:
		//��ư ���ϸ��̼� Ȱ��ȭ
		_button->setVButtonAniStart(0, true);
		_button->setVButtonAniStart(1, false);

		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			_button->buttonRemove();
			delete _button;
			SCENEMANAGER->changeScene("Ÿ��Ʋ");
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
			SCENEMANAGER->changeScene("�ε�");
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

