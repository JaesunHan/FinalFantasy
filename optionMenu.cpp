#include "stdafx.h"
#include "optionMenu.h"


optionMenu::optionMenu()
{
}


optionMenu::~optionMenu()
{
}


HRESULT optionMenu::init()
{
	_bgImage = IMAGEMANAGER->findImage("�ɼǸ޴�");
	cursorInit(CUSOR_RIGHT, 950, 60);
	buttonInit("��ư��Ÿ��", 1000, 50);
	buttonInit("��ư��Ÿ��", 1000, 100);
	buttonInit("��ư��Ÿ��", 1000, 150);
	buttonInit("��ư��Ÿ��", 1000, 200);


	return S_OK;
}

void optionMenu::release()
{

}

void optionMenu::update() 
{
	cursorUpdate();
	cursorKeyControl(50, 4);
}

void optionMenu::render()
{
	_bgImage->render(getMemDC());
	cursorRender();
	buttonRender();
}
