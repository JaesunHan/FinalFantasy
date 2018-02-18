#include "stdafx.h"
#include "abilitiesMenu.h"


abilitiesMenu::abilitiesMenu()
{
}


abilitiesMenu::~abilitiesMenu()
{
}



HRESULT abilitiesMenu::init()
{
	_bgImage = IMAGEMANAGER->findImage("로드게임메뉴");



	return S_OK;
}

void abilitiesMenu::release()
{

}

void abilitiesMenu::update()
{

	//옵션 메뉴가기
	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		//_button->buttonRemove();
		//delete _button;
		SCENEMANAGER->changeScene("옵션");
	}
}

void abilitiesMenu::render()
{
	_bgImage->render(getMemDC());

}


