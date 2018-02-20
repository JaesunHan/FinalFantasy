#include "stdafx.h"
#include "storeScene.h"
#include "itemManager.h"

storeScene::storeScene()
{
}


storeScene::~storeScene()
{
}

HRESULT storeScene::init()
{
	IMAGEMANAGER->addImage("storeScreen", ".//image//userInterface//Store.bmp", 1200, 640, true, RGB(255, 0, 255));

	return S_OK;
}

void storeScene::release()
{
	_vendorList.clear();
}

void storeScene::update()
{
}

void storeScene::render()
{
	IMAGEMANAGER->render("storeScreen", getMemDC());

	for (int i = 0; i < _vendorList.size(); i++)
	{
		TextOut(getMemDC(), 200 + (i % 3) * 150, 200 + (i / 3) * 50, _vendorList[i]->getItemName(), strlen(_vendorList[i]->getItemName()));
	}
}

void storeScene::setStoreKey(string key)
{
	_storeKey = key;

	if (key == "weaponStore")
	{
		for (int i = 0; i < _im->getVItem().size(); i++)
		{
			if (_im->getVItem()[i]->getItmeKind() == ITEM_WEAPON)
			{
				_vendorList.push_back(_im->getVItem()[i]);
			}
		}
	}
}
