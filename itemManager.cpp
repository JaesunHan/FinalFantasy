#include "stdafx.h"
#include "itemManager.h"


itemManager::itemManager()
{
}


itemManager::~itemManager()
{
}

HRESULT itemManager::init()
{
	weaponItem* temp = new weaponItem;
	//temp->init("소꽁구단검", "소꽁구가 사람을...", 25, )

	return S_OK;
}