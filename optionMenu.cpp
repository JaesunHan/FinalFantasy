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

	return S_OK;
}

void optionMenu::release()
{

}

void optionMenu::update() 
{

}
