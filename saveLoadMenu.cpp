#include "stdafx.h"
#include "saveLoadMenu.h"


saveLoadMenu::saveLoadMenu()
{
}
saveLoadMenu::~saveLoadMenu()
{
}


HRESULT saveLoadMenu::init()
{
	_saveType = SAVE_NEWGAME;


	switch (_saveType)
	{
		case SAVE_NEWGAME:
			_bgImage = IMAGEMANAGER->findImage("¥∫∞‘¿”");
			cursorInit(CUSOR_RIGHT, 475, 402);
		break;
		case SAVE_LOADGAME:

		break;
	}




	return S_OK;
}

void saveLoadMenu::release()
{

}

void saveLoadMenu::update()	
{
	cursorUpdate();
}


