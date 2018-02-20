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
	IMAGEMANAGER->addFrameImage("storeButton", ".//image//userInterface//itemButton.bmp", 570, 81, 2, 1, true, RGB(255, 0, 255));

	AddFontResourceEx(
		"SDMiSaeng.ttf", 	// font file name
		FR_PRIVATE,         // font characteristics
		NULL            	// reserved
	);

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

	HFONT newFont = CreateFont(30, 0, 0, 0, 1000, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("Sandoll �̻�"));
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), newFont);
	SetTextColor(getMemDC(), RGB(255, 255, 255));

	for (int i = 0; i < _vendorList.size(); i++)
	{
		IMAGEMANAGER->frameRender("storeButton", getMemDC(), 20 + (i % 3) * 290, 220 + (i / 3) * 90, 0, 0);

		TextOut(getMemDC(), 40 + (i % 3) * 290, 245 + (i / 3) * 90, _vendorList[i]->getItemName(), strlen(_vendorList[i]->getItemName()));

		SetTextAlign(getMemDC(), TA_RIGHT);
		TextOut(getMemDC(), 285 + (i % 3) * 290, 260 + (i / 3) * 90,
			to_string(_vendorList[i]->getPrice()).c_str(), strlen(to_string(_vendorList[i]->getPrice()).c_str()));
		SetTextAlign(getMemDC(), TA_LEFT);
	}

	SetTextColor(getMemDC(), RGB(0, 0, 255));
	SelectObject(getMemDC(), oldFont);
	DeleteObject(oldFont);
	DeleteObject(newFont);
}

void storeScene::setStoreKey(string key)
{
	_storeKey = key;

	if (key == "weaponStore")
	{
		for (int i = 0; i < _im->getVItem().size(); i++)
		{
			if (_im->getVItem()[i]->getItmeKind() == ITEM_WEAPON && _im->getVItem()[i]->getPrice() != 2)
			{
				_vendorList.push_back(_im->getVItem()[i]);
			}
		}
	}
	else if (key == "armorStore")
	{
		for (int i = 0; i < _im->getVItem().size(); i++)
		{
			if ((_im->getVItem()[i]->getItmeKind() == ITEM_ARMOR || _im->getVItem()[i]->getItmeKind() == ITEM_HELMET
				|| _im->getVItem()[i]->getItmeKind() == ITEM_SUB_WEAPON) && _im->getVItem()[i]->getPrice() != 2)
			{
				_vendorList.push_back(_im->getVItem()[i]);
			}
		}
	}
	else if (key == "consumableStore")
	{
		for (int i = 0; i < _im->getVItem().size(); i++)
		{
			if (_im->getVItem()[i]->getItmeKind() == ITEM_EXPENDABLE && _im->getVItem()[i]->getPrice() != 2)
			{
				_vendorList.push_back(_im->getVItem()[i]);
			}
		}
	}

}
