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

	return S_OK;
}

void optionMenu::release()
{

}

void optionMenu::update() 
{

}
