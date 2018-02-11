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
			_bgImage = IMAGEMANAGER->findImage("뉴게임");
			cursorInit(CUSOR_RIGHT, 950, 190);

			buttonInit("버튼예스", 1000, 187);
			buttonInit("버튼노", 1000, 238);
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

	//선택
	switch (_cursor.currentNum)
	{
		case 0:
			//버튼 에니메이션 활성화
			_vButton[0].aniStart = true;
			_vButton[1].aniStart = false;

			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				buttonRemove();
				SCENEMANAGER->changeScene("타이틀");
			}
		break;
		case 1:
			//버튼 에니메이션 활성화
			_vButton[1].aniStart = true;
			_vButton[0].aniStart = false;

			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				buttonRemove();
				SCENEMANAGER->changeScene("로딩");
			}
		break;
	}
}


