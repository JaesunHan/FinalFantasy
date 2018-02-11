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
	_saveType = SAVE_NEWGAME;


	switch (_saveType)
	{
		case SAVE_NEWGAME:
			_bgImage = IMAGEMANAGER->findImage("������");
			cursorInit(CUSOR_RIGHT, 950, 190);

			buttonInit("��ư����", 1000, 187);
			buttonInit("��ư��", 1000, 238);
		break;
		case SAVE_LOADGAME:

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
	buttonUpdate();

	cursorKeyControl(51, 2);

	//����
	switch (_cursor.currentNum)
	{
		case 0:
			//��ư ���ϸ��̼� Ȱ��ȭ
			_vButton[0].aniStart = true;
			_vButton[1].aniStart = false;

			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				buttonRemove();
				SCENEMANAGER->changeScene("Ÿ��Ʋ");
			}
		break;
		case 1:
			//��ư ���ϸ��̼� Ȱ��ȭ
			_vButton[1].aniStart = true;
			_vButton[0].aniStart = false;

			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				buttonRemove();
				SCENEMANAGER->changeScene("�ε�");
			}
		break;
	}
}


