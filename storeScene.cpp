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
	IMAGEMANAGER->addFrameImage("buySellButton", ".//image//userInterface//button_fantasy.bmp", 406, 49, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("storeButton", ".//image//userInterface//itemButton.bmp", 456, 65, 2, 1, true, RGB(255, 0, 255));

	AddFontResourceEx(
		"SDMiSaeng.ttf", 	// font file name
		FR_PRIVATE,         // font characteristics
		NULL            	// reserved
	);

	_currentPos = POS_BUY_SELL;
	_cursorIndex = 0;

	_buySellSelectCursor.init(CURSOR_RIGHT, 130, 130);
	

	return S_OK;
}

void storeScene::release()
{
	_vendorList.clear();
}

void storeScene::update()
{
	//keyControl();
	_buySellSelectCursor.keyControlX(400, 2);

	_buySellSelectCursor.update();
}

void storeScene::render()
{
	IMAGEMANAGER->render("storeScreen", getMemDC());

	HFONT newFont = CreateFont(50, 0, 0, 0, 1000, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("Sandoll 미생"));
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), newFont);

	SetTextColor(getMemDC(), RGB(40, 5, 0));
	TextOut(getMemDC(), 35, 22, _storeName.c_str(), strlen(_storeName.c_str()));

	DeleteObject(newFont);
	newFont = CreateFont(40, 0, 0, 0, 1000, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("Sandoll 미생"));
	SelectObject(getMemDC(), newFont);
	SetTextColor(getMemDC(), RGB(255, 255, 255));

	drawStoreInterface();

	DeleteObject(newFont);
	newFont = CreateFont(20, 0, 0, 0, 1000, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("Sandoll 미생"));
	SelectObject(getMemDC(), newFont);

	drawVendorList();
	
	SetTextColor(getMemDC(), RGB(0, 0, 0));
	SelectObject(getMemDC(), oldFont);
	DeleteObject(oldFont);
	DeleteObject(newFont);

	_buySellSelectCursor.render();
}

void storeScene::keyControl(void)
{
	if (_currentPos == POS_BUY_SELL)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT) || KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			_cursorIndex = !_cursorIndex;
		}
	}
}

void storeScene::drawStoreInterface(void)
{
	IMAGEMANAGER->frameRender("buySellButton", getMemDC(), 150, 118, !_buySellSelectCursor.getCursorXNum(), 0);
	IMAGEMANAGER->frameRender("buySellButton", getMemDC(), 550, 118, _buySellSelectCursor.getCursorXNum(), 0);

	outlineTextOut(getMemDC(), 230, 122, "구매", GetTextColor(getMemDC()), RGB(0, 0, 0), GetTextColor(getMemDC()), 40);
	outlineTextOut(getMemDC(), 620, 122, "판매", GetTextColor(getMemDC()), RGB(0, 0, 0), GetTextColor(getMemDC()), 40);
}

void storeScene::drawVendorList(void)
{
	for (int i = 0; i < _vendorList.size(); i++)
	{
		IMAGEMANAGER->frameRender("storeButton", getMemDC(), 55 + (i % 3) * 280, 220 + (i / 3) * 90, 0, 0);

		TextOut(getMemDC(), 75 + (i % 3) * 280, 235 + (i / 3) * 90, _vendorList[i]->getItemName(), strlen(_vendorList[i]->getItemName()));

		SetTextAlign(getMemDC(), TA_RIGHT);
		TextOut(getMemDC(), 260 + (i % 3) * 280, 255 + (i / 3) * 90,
			to_string(_vendorList[i]->getPrice()).c_str(), strlen(to_string(_vendorList[i]->getPrice()).c_str()));
		SetTextAlign(getMemDC(), TA_LEFT);
	}
}

void storeScene::setStoreKey(string key)
{
	_storeKey = key;

	if (key == "weaponStore")
	{
		_storeName = "무기 상점";
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
		_storeName = "방어구 상점";
		for (int i = 0; i < _im->getVItem().size(); i++)
		{
			if ((_im->getVItem()[i]->getItmeKind() == ITEM_ARMOR || _im->getVItem()[i]->getItmeKind() == ITEM_HELMET
				|| _im->getVItem()[i]->getItmeKind() == ITEM_SUB_WEAPON) && _im->getVItem()[i]->getPrice() != 2)
			{
				_vendorList.push_back(_im->getVItem()[i]);
			}
		}
	}
	else if (key == "itemShop")
	{
		_storeName = "도구 상점";
		for (int i = 0; i < _im->getVItem().size(); i++)
		{
			if (_im->getVItem()[i]->getItmeKind() == ITEM_EXPENDABLE && _im->getVItem()[i]->getPrice() != 2)
			{
				_vendorList.push_back(_im->getVItem()[i]);
			}
		}
	}

}
