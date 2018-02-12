#include "stdafx.h"
#include "statusMenu.h"


statusMenu::statusMenu()
{
}


statusMenu::~statusMenu()
{
}

HRESULT statusMenu::init()
{
	_bgImage = IMAGEMANAGER->findImage("로드게임메뉴");




	return S_OK;
}

void statusMenu::release()
{

}

void statusMenu::update()
{




	//옵션 메뉴가기
	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		//_button->buttonRemove();
		//delete _button;
		SCENEMANAGER->changeScene("옵션");
	}
}

void statusMenu::render()
{
	_bgImage->render(getMemDC());
}
