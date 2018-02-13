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
	_bgImage = IMAGEMANAGER->findImage("���̺�޴�");
	cursorInit(CUSOR_RIGHT, 950, 190);
	_cursorYNum = 2;

	_button = new fButton;
	_button->buttonSet("��ư����", 1000, 187);
	_button->buttonSet("��ư��", 1000, 238);


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

	//����
	switch (_cursor.currentYNum)
	{
		case 0:
			//��ư ���ϸ��̼� Ȱ��ȭ
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
				SCENEMANAGER->changeScene("Ÿ��Ʋ");
			}
		break;
		case 1:
			//��ư ���ϸ��̼� Ȱ��ȭ
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
				SCENEMANAGER->changeScene("�ε�");
			}
		break;
	}

	//�ɼ� �޴�����
	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		_button->buttonRemove();
		delete _button;
		SCENEMANAGER->changeScene("�ɼ�");
	}
}

void saveLoadMenu::render()
{
	_bgImage->render(getMemDC());
	_button->render();
	cursorRender();
}


