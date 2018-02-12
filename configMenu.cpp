#include "stdafx.h"
#include "configMenu.h"


configMenu::configMenu()
{
}


configMenu::~configMenu()
{
}

HRESULT configMenu::init()
{
	_bgImage = IMAGEMANAGER->findImage("로드게임메뉴");





	return S_OK;
}

void configMenu::release()
{

}

void configMenu::update()
{




	//옵션 메뉴가기
	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		//_button->buttonRemove();
		//delete _button;
		SCENEMANAGER->changeScene("옵션");
	}
}

void configMenu::render()
{
	_bgImage->render(getMemDC());
}
