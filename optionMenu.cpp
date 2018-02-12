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

	_button = new fButton;

	_button->buttonSet("��ư��Ÿ��", 1000, 50, "Abilities", 12);
	_button->buttonSet("��ư��Ÿ��", 1000, 100);
	_button->buttonSet("��ư��Ÿ��", 1000, 150);
	_button->buttonSet("��ư��Ÿ��", 1000, 200);


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
	_button->render();
}
