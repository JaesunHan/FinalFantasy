#include "stdafx.h"
#include "itemMenu.h"


itemMenu::itemMenu()
{
}


itemMenu::~itemMenu()
{
}

HRESULT itemMenu::init()
{
	_bgImage = IMAGEMANAGER->findImage("로드게임메뉴");




	return S_OK;
}

void itemMenu::release()
{

}

void itemMenu::update()
{




	//옵션 메뉴가기
	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		//_button->buttonRemove();
		//delete _button;
		SCENEMANAGER->changeScene("옵션");
	}
}

void itemMenu::render()
{
	_bgImage->render(getMemDC());
}
