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
	_bgImage = IMAGEMANAGER->findImage("옵션메뉴");
	cursorInit(CUSOR_RIGHT, 950, 60);

	_button = new fButton;

	_button->buttonSet("버튼판타지", 1000, 50, "Items", 12);
	_button->buttonSet("버튼판타지", 1000, 100, "Abilities", 12);
	_button->buttonSet("버튼판타지", 1000, 150, "Equips", 12);
	_button->buttonSet("버튼판타지", 1000, 200, "Status", 12);
	_button->buttonSet("버튼판타지", 1000, 250, "Save", 12);
	_button->buttonSet("버튼판타지", 1000, 300, "Config", 12);


	return S_OK;
}

void optionMenu::release()
{

}

void optionMenu::update() 
{
	cursorUpdate();
	cursorKeyControl(50, 6);
}

void optionMenu::render()
{
	_bgImage->render(getMemDC());
	cursorRender();
	_button->render();
}
