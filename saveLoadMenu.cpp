#include "stdafx.h"
#include "saveLoadMenu.h"


saveLoadMenu::saveLoadMenu()
{
}
saveLoadMenu::~saveLoadMenu()
{
}


HRESULT saveLoadMenu::init()
{
	switch (_title->getSaveType())
	{
		case SAVE_NEWGAME:
			_bgImage = IMAGEMANAGER->findImage("������");
			cursorInit(CUSOR_RIGHT, 950, 190);

			_button = new fButton;
			_button->buttonSet("��ư����", 1000, 187);
			_button->buttonSet("��ư��", 1000, 238);

		break;
		case SAVE_LOADGAME:
			_bgImage = IMAGEMANAGER->findImage("�ε���Ӹ޴�");
			cursorInit(CUSOR_RIGHT, 950, 190);

			_button = new fButton;
			_button->buttonSet("��ư����", 1000, 187);
			_button->buttonSet("��ư��", 1000, 238);
		break;
	}




	return S_OK;
}

void saveLoadMenu::release()
{

}

void saveLoadMenu::update()	
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

void saveLoadMenu::render()
{
	_bgImage->render(getMemDC());
	_button->render();
	cursorRender();

	char str[32];
	sprintf(str, "%d", _cursor.currentNum);
	TextOut(getMemDC(), 10, 100, str, strlen(str));

}


