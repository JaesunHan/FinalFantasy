#include "stdafx.h"
#include "equipMenu.h"


equipMenu::equipMenu()
{
}


equipMenu::~equipMenu()
{
}

HRESULT equipMenu::init()
{
	_bgImage = IMAGEMANAGER->findImage("로드게임메뉴");




	return S_OK;
}

void equipMenu::release()
{

}

void equipMenu::update()
{




	//옵션 메뉴가기
	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		//_button->buttonRemove();
		//delete _button;
		SCENEMANAGER->changeScene("옵션");
	}
}

void equipMenu::render()
{
	_bgImage->render(getMemDC());
}
