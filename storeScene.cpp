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
	IMAGEMANAGER->addImage("messageBox", ".//image//userInterface//messageBox.bmp", 697, 206, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("amountSelectBox", ".//image//userInterface//amountSelectBox.bmp", 410, 205, true, RGB(255, 0, 255));

	SOUNDMANAGER->addSound("menuSelectLow", ".\\sound\\sfx\\menuSelectLow.wav", false, false);
	SOUNDMANAGER->addSound("DCMenuTing", ".\\sound\\sfx\\DCMenuTing.wav", false, false);

	AddFontResourceEx(
		"SDMiSaeng.ttf", 	// font file name
		FR_PRIVATE,         // font characteristics
		NULL            	// reserved
	);

	_currentPos = _prevPos = POS_BUY_SELL;
	_cursorIndex = 0;
	_listSelectIndex = 0;
	_listMaxIndex = 0;

	_currentInventory = INVENTORY_ITEM;
	_mbType = MESSAGE_NONE;

	_buySellSelectCursor.init(CURSOR_RIGHT, 130, 130);
	_listSelectCursor.init(CURSOR_RIGHT, 20, 240);

	_currentAmount = 1;

	_curVendorPage = 0;
	_curSellPage = 0;

	// 임시로 돈 세팅
	_im->setMoney(500000);

	return S_OK;
}

void storeScene::release()
{
	_vendorList.clear();
}

void storeScene::update()
{
	keyControl();

	_buySellSelectCursor.update();
	if (_currentPos == POS_BUY_LIST || _currentPos == POS_SELL_LIST) _listSelectCursor.update();
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

	if (_currentPos == POS_BUY_LIST || (_prevPos == POS_BUY_LIST && _currentPos == POS_MESSAGEBOX)) drawVendorList();
	else if (_currentPos == POS_SELL_LIST || (_prevPos == POS_SELL_LIST && _currentPos == POS_MESSAGEBOX)) drawSellItemList();
	else if (_currentPos == POS_AMOUNT_SELECT) drawAmountSelectScreen();
	
	SetTextColor(getMemDC(), RGB(0, 0, 0));
	SelectObject(getMemDC(), oldFont);
	DeleteObject(oldFont);
	DeleteObject(newFont);

	_buySellSelectCursor.render();
	if (_currentPos == POS_BUY_LIST || _currentPos == POS_SELL_LIST) _listSelectCursor.render();

	if (_mbType != MESSAGE_NONE) drawAlertScreen();

}

void storeScene::keyControl(void)
{
	int curPageItemNum;

	if (_currentPos == POS_BUY_SELL)
	{
		_buySellSelectCursor.keyControlX(400, 2);

		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			SOUNDMANAGER->play("menuSelectLow", CH_EFFECT08, 1.0f);

			if (!_buySellSelectCursor.getCursorXNum()) _currentPos = POS_BUY_LIST;
			else if (_buySellSelectCursor.getCursorXNum()) _currentPos = POS_SELL_LIST;
		}

		if (KEYMANAGER->isOnceKeyDown(VK_BACK))
		{
			SOUNDMANAGER->play("DCMenuTing", CH_EFFECT08, 1.0f);

			SCENEMANAGER->changeSceneType0("타운맵씬", false);

			_im->saveInventory("skgFile");
			return;
		}
	}
	if (_currentPos == POS_BUY_LIST)
	{
		if (_curVendorPage < _maxVendorPage) curPageItemNum = MAX_DRAWNUM;
		else curPageItemNum = _vendorList.size() % MAX_DRAWNUM;

		_listSelectCursor.keyControlXY(280, 90, 3, curPageItemNum);

		if (KEYMANAGER->isOnceKeyDown(VK_BACK))
		{
			SOUNDMANAGER->play("DCMenuTing", CH_EFFECT08, 1.0f);

			_currentPos = POS_BUY_SELL;
			_listSelectCursor.init(CURSOR_RIGHT, 20, 240);
		}

		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			if (_im->getMoney() >= _vendorList[_listSelectCursor.getCursorPos() + MAX_DRAWNUM * _curVendorPage]->getPrice())
			{
				switch (_vendorList[_listSelectCursor.getCursorPos() + MAX_DRAWNUM * _curVendorPage]->getItmeKind())
				{
				case ITEM_EXPENDABLE:
					if (_im->getItemCountByVector(_vendorList[_listSelectCursor.getCursorPos() + MAX_DRAWNUM * _curVendorPage]->getItemNumber() - 1) + 1 > 99)
					{
						_prevPos = _currentPos;
						_currentPos = POS_MESSAGEBOX;
						_mbType = MESSAGE_OVER_ITEM;
						return;
					}
					break;
				case ITEM_WEAPON:
					if (_im->getWeaponCountByVector(_vendorList[_listSelectCursor.getCursorPos() + MAX_DRAWNUM * _curVendorPage]->getItemNumber() - 1) + 1 > 99)
					{
						_prevPos = _currentPos;
						_currentPos = POS_MESSAGEBOX;
						_mbType = MESSAGE_OVER_ITEM;
						return;
					}
					break;
				case ITEM_ARMOR: case ITEM_HELMET: case ITEM_SUB_WEAPON: case ITEM_ACCESSORY:
					if (_im->getArmorCountByVector(_vendorList[_listSelectCursor.getCursorPos() + MAX_DRAWNUM * _curVendorPage]->getItemNumber() - 1) + 1 > 99)
					{
						_prevPos = _currentPos;
						_currentPos = POS_MESSAGEBOX;
						_mbType = MESSAGE_OVER_ITEM;
						return;
					}
					break;
				default:
					break;
				}

				SOUNDMANAGER->play("menuSelectLow", CH_EFFECT08, 1.0f);
				_prevPos = _currentPos;
				_currentPos = POS_AMOUNT_SELECT;
			}
			else if (_im->getMoney() < _vendorList[_listSelectCursor.getCursorPos() + MAX_DRAWNUM * _curVendorPage]->getPrice())
			{
				_prevPos = _currentPos;
				_currentPos = POS_MESSAGEBOX;
				_mbType = MESSAGE_NO_MONEY;
			}
		}

		if (KEYMANAGER->isOnceKeyDown(VK_PRIOR))
		{
			if (_curVendorPage > 0) --_curVendorPage;
			else _curVendorPage = _maxVendorPage;

			_listSelectCursor.resetCursorPos();
		}
		if (KEYMANAGER->isOnceKeyDown(VK_NEXT))
		{
			if (_curVendorPage < _maxVendorPage) ++_curVendorPage;
			else _curVendorPage = 0;

			_listSelectCursor.resetCursorPos();
		}
	}
	if (_currentPos == POS_SELL_LIST)
	{
		if (_currentInventory == INVENTORY_WEAPON)
		{
			_maxSellPage = _im->getWeaponInventorySize() / MAX_DRAWNUM;
			if (_curSellPage < _maxSellPage) curPageItemNum = MAX_DRAWNUM;
			else curPageItemNum = _im->getWeaponInventorySize() % MAX_DRAWNUM;
		}
		else if (_currentInventory == INVENTORY_ARMOR)
		{
			_maxSellPage = _im->getArmorInventorySize() / MAX_DRAWNUM;
			if (_curSellPage < _maxSellPage) curPageItemNum = MAX_DRAWNUM;
			else curPageItemNum = _im->getArmorInventorySize() % MAX_DRAWNUM;
		}
		else if (_currentInventory == INVENTORY_ITEM)
		{
			_maxSellPage = _im->getItemInventorySize() / MAX_DRAWNUM;
			if (_curSellPage < _maxSellPage) curPageItemNum = MAX_DRAWNUM;
			else curPageItemNum = _im->getItemInventorySize() % MAX_DRAWNUM;
		}

		_listSelectCursor.keyControlXY(280, 90, 3, curPageItemNum);

		if (KEYMANAGER->isOnceKeyDown(VK_BACK))
		{
			SOUNDMANAGER->play("DCMenuTing", CH_EFFECT08, 1.0f);

			_currentPos = POS_BUY_SELL;
			_listSelectCursor.init(CURSOR_RIGHT, 20, 240);
		}

		if (KEYMANAGER->isOnceKeyDown(VK_TAB))
		{
			if (_currentInventory < INVENTORY_END - 1)_currentInventory++;
			else _currentInventory = 0;
			_listSelectCursor.init(CURSOR_RIGHT, 20, 240);

			if (_currentInventory == INVENTORY_WEAPON)
			{
				_maxSellPage = _im->getWeaponInventorySize() / MAX_DRAWNUM;
				if (_curSellPage < _maxSellPage) curPageItemNum = MAX_DRAWNUM;
				else curPageItemNum = _im->getWeaponInventorySize() % MAX_DRAWNUM;
			}
			else if (_currentInventory == INVENTORY_ARMOR)
			{
				_maxSellPage = _im->getArmorInventorySize() / MAX_DRAWNUM;
				if (_curSellPage < _maxSellPage) curPageItemNum = MAX_DRAWNUM;
				else curPageItemNum = _im->getArmorInventorySize() % MAX_DRAWNUM;
			}
			else if (_currentInventory == INVENTORY_ITEM)
			{
				_maxSellPage = _im->getItemInventorySize() / MAX_DRAWNUM;
				if (_curSellPage < _maxSellPage) curPageItemNum = MAX_DRAWNUM;
				else curPageItemNum = _im->getItemInventorySize() % MAX_DRAWNUM;
			}
		}

		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			if (_currentInventory == INVENTORY_WEAPON)
			{
				if (_im->getWeaponInventorySize() <= 0) return;
			}
			else if (_currentInventory == INVENTORY_ARMOR)
			{
				if (_im->getArmorInventorySize() <= 0) return;
			}
			else if (_currentInventory == INVENTORY_ITEM)
			{
				if (_im->getItemInventorySize() <= 0) return;
			}

			SOUNDMANAGER->play("menuSelectLow", CH_EFFECT08, 1.0f);

			_prevPos = _currentPos;
			_currentPos = POS_AMOUNT_SELECT;
			return;
		}

		if (KEYMANAGER->isOnceKeyDown(VK_PRIOR))
		{
			if (_curSellPage > 0) --_curSellPage;
			else _curSellPage = _maxSellPage;

			_listSelectCursor.resetCursorPos();
		}
		if (KEYMANAGER->isOnceKeyDown(VK_NEXT))
		{
			if (_curSellPage < _maxSellPage) ++_curSellPage;
			else _curSellPage = 0;

			_listSelectCursor.resetCursorPos();
		}
	}
	if (_currentPos == POS_AMOUNT_SELECT && _prevPos == POS_BUY_LIST)
	{
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			if (SOUNDMANAGER->isPlaySound(CH_MENUSCENE)) return;

			SOUNDMANAGER->play("menuSelectLow", CH_MENUSCENE, EFFECTVOLUME);

			if (_im->getMoney() >= _vendorList[_listSelectCursor.getCursorPos() + _curVendorPage * MAX_DRAWNUM]->getPrice() * (_currentAmount + 1))
			{
				switch (_vendorList[_listSelectCursor.getCursorPos() + _curVendorPage * MAX_DRAWNUM]->getItmeKind())
				{
				case ITEM_EXPENDABLE:
					if (_im->getItemCountByVector(_vendorList[_listSelectCursor.getCursorPos() + _curVendorPage * MAX_DRAWNUM]->getItemNumber() - 1) + _currentAmount + 1 <= 99)
						++_currentAmount;
					break;
				case ITEM_WEAPON:
					if (_im->getWeaponCountByVector(_vendorList[_listSelectCursor.getCursorPos() + _curVendorPage * MAX_DRAWNUM]->getItemNumber() - 1) + _currentAmount + 1 <= 99)
						++_currentAmount;
					break;
				case ITEM_ARMOR: case ITEM_HELMET: case ITEM_SUB_WEAPON: case ITEM_ACCESSORY:
					if (_im->getArmorCountByVector(_vendorList[_listSelectCursor.getCursorPos() + _curVendorPage * MAX_DRAWNUM]->getItemNumber() - 1) + _currentAmount + 1 <= 99)
						++_currentAmount;
					break;
				default:
					break;
				}
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			if (SOUNDMANAGER->isPlaySound(CH_MENUSCENE)) return;

			SOUNDMANAGER->play("menuSelectLow", CH_MENUSCENE, EFFECTVOLUME);

			if (_currentAmount > 1) --_currentAmount;
		}

		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			switch (_vendorList[_cursorIndex]->getItmeKind())
			{
			case ITEM_EXPENDABLE:
				_im->changeItemNumber(_vendorList[_listSelectCursor.getCursorPos() + _curVendorPage * MAX_DRAWNUM]->getItemName(), _currentAmount);

				break;
			case ITEM_WEAPON:
				_im->changeWeaponNumber(_vendorList[_listSelectCursor.getCursorPos() + _curVendorPage * MAX_DRAWNUM]->getItemName(), _currentAmount);

				break;
			case ITEM_ARMOR: case ITEM_HELMET: case ITEM_SUB_WEAPON: case ITEM_ACCESSORY:
				_im->changeArmorNumber(_vendorList[_listSelectCursor.getCursorPos() + _curVendorPage * MAX_DRAWNUM]->getItemName(), _currentAmount);
				break;
			default:
				break;
			}
			
			_im->setMoney(_im->getMoney() - _vendorList[_listSelectCursor.getCursorPos() + _curVendorPage * MAX_DRAWNUM]->getPrice() * _currentAmount);

			SOUNDMANAGER->play("menuSelectLow", CH_EFFECT08, 1.0f);

			_currentPos = _prevPos;
			_currentAmount = 1;
		}

		if (KEYMANAGER->isOnceKeyDown(VK_BACK))
		{
			SOUNDMANAGER->play("DCMenuTing", CH_EFFECT08, 1.0f);

			_currentPos = _prevPos;
			_currentAmount = 1;
		}
	}
	if (_currentPos == POS_AMOUNT_SELECT && _prevPos == POS_SELL_LIST)
	{
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			if (SOUNDMANAGER->isPlaySound(CH_MENUSCENE)) return;

			SOUNDMANAGER->play("menuSelectLow", CH_MENUSCENE, EFFECTVOLUME);

			if (_currentInventory == INVENTORY_WEAPON)
			{
				if (_im->getWeaponInventorySize() <= 0) return;
				if (_currentAmount + 1 <= _im->getWeaponCount(_listSelectCursor.getCursorPos() + _curSellPage * MAX_DRAWNUM)) ++_currentAmount;
			}
			else if (_currentInventory == INVENTORY_ARMOR)
			{
				if (_im->getArmorInventorySize() <= 0) return;
				if (_currentAmount + 1 <= _im->getArmorCount(_listSelectCursor.getCursorPos() + _curSellPage * MAX_DRAWNUM)) ++_currentAmount;
			}
			else if (_currentInventory == INVENTORY_ITEM)
			{
				if (_im->getItemInventorySize() <= 0) return;
				if (_currentAmount + 1 <= _im->getItemCount(_listSelectCursor.getCursorPos() + _curSellPage * MAX_DRAWNUM)) ++_currentAmount;
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			if (SOUNDMANAGER->isPlaySound(CH_MENUSCENE)) return;

			SOUNDMANAGER->play("menuSelectLow", CH_MENUSCENE, EFFECTVOLUME);

			if (_currentAmount > 1) --_currentAmount;
		}

		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			if (_currentInventory == INVENTORY_WEAPON)
			{
				if (_im->getWeaponInventorySize() <= 0) return;

				_im->setMoney(_im->getMoney() + _im->getVItem()[_im->getWeaponVNum(_listSelectCursor.getCursorPos() + _curSellPage * MAX_DRAWNUM)]->getPrice() / 2 * _currentAmount);
				_im->changeWeaponNumber(_im->getWeaponVNum(_listSelectCursor.getCursorPos() + _curSellPage * MAX_DRAWNUM), -_currentAmount);
			}
			else if (_currentInventory == INVENTORY_ARMOR)
			{
				if (_im->getArmorInventorySize() <= 0) return;

				_im->setMoney(_im->getMoney() + _im->getVItem()[_im->getArmorVNum(_listSelectCursor.getCursorPos() + _curSellPage * MAX_DRAWNUM)]->getPrice() / 2 * _currentAmount);
				_im->changeArmorNumber(_im->getArmorVNum(_listSelectCursor.getCursorPos() + _curSellPage * MAX_DRAWNUM), -_currentAmount);
			}
			else if (_currentInventory == INVENTORY_ITEM)
			{
				if (_im->getItemInventorySize() <= 0) return;

				_im->setMoney(_im->getMoney() + _im->getVItem()[_im->getItemVNum(_listSelectCursor.getCursorPos() + _curSellPage * MAX_DRAWNUM)]->getPrice() / 2 * _currentAmount);
				_im->changeItemNumber(_im->getItemVNum(_listSelectCursor.getCursorPos() + _curSellPage * MAX_DRAWNUM), -_currentAmount);
			}

			_listSelectCursor.resetCursorPos();
			
			SOUNDMANAGER->play("menuSelectLow", CH_EFFECT08, 1.0f);

			_currentPos = _prevPos;
			_currentAmount = 1;
		}

		if (KEYMANAGER->isOnceKeyDown(VK_BACK))
		{
			SOUNDMANAGER->play("DCMenuTing", CH_EFFECT08, 1.0f);
			_currentPos = _prevPos;
			_currentAmount = 1;
		}
	}
	if (_currentPos == POS_MESSAGEBOX)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_BACK) || KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			SOUNDMANAGER->play("DCMenuTing", CH_EFFECT08, 1.0f);

			_currentPos = _prevPos;
			_mbType = MESSAGE_NONE;
		}
	}
}

void storeScene::drawStoreInterface(void)
{
	HFONT newFont = CreateFont(40, 0, 0, 0, 1000, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("Sandoll 미생"));
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), newFont);
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	
	// 구매 판매 버튼 출력
	IMAGEMANAGER->frameRender("buySellButton", getMemDC(), 150, 118, !_buySellSelectCursor.getCursorXNum(), 0);
	IMAGEMANAGER->frameRender("buySellButton", getMemDC(), 550, 118, _buySellSelectCursor.getCursorXNum(), 0);

	outlineTextOut(getMemDC(), 230, 122, "구매", GetTextColor(getMemDC()), RGB(0, 0, 0), GetTextColor(getMemDC()), 40);
	outlineTextOut(getMemDC(), 620, 122, "판매", GetTextColor(getMemDC()), RGB(0, 0, 0), GetTextColor(getMemDC()), 40);

	DeleteObject(newFont);
	newFont = CreateFont(20, 0, 0, 0, 1000, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("Sandoll 미생"));
	SetTextAlign(getMemDC(), TA_RIGHT);

	// 소지금 출력
	outlineTextOut(getMemDC(), 1100, 580, to_string(_im->getMoney()).c_str(), RGB(255, 255, 255), RGB(0, 0, 0), RGB(255, 255, 255), 20);
	outlineTextOut(getMemDC(), 1150, 580, "Gil", RGB(180, 180, 20), RGB(0, 0, 0), RGB(255, 255, 255), 20);

	SetTextColor(getMemDC(), RGB(255, 255, 255));
	SetTextAlign(getMemDC(), TA_LEFT);
}

void storeScene::drawVendorList(void)
{
	int curPageItemNum;
	char listPage[256] = "";

	if (_curVendorPage < _maxVendorPage) curPageItemNum = MAX_DRAWNUM;
	else curPageItemNum = _vendorList.size() % MAX_DRAWNUM;

	for (int i = 0; i < curPageItemNum; i++)
	{
		if (i == _listSelectCursor.getCursorPos())IMAGEMANAGER->frameRender("storeButton", getMemDC(), 55 + (i % 3) * 280, 220 + (i / 3) * 90, 1, 0);
		else IMAGEMANAGER->frameRender("storeButton", getMemDC(), 55 + (i % 3) * 280, 220 + (i / 3) * 90, 0, 0);

		TextOut(getMemDC(), 75 + (i % 3) * 280, 235 + (i / 3) * 90, _vendorList[_curVendorPage * MAX_DRAWNUM + i]->getItemName(),
			strlen(_vendorList[_curVendorPage * MAX_DRAWNUM + i]->getItemName()));

		SetTextAlign(getMemDC(), TA_RIGHT);
		TextOut(getMemDC(), 260 + (i % 3) * 280, 255 + (i / 3) * 90,
			to_string(_vendorList[_curVendorPage * MAX_DRAWNUM + i]->getPrice()).c_str(),
			strlen(to_string(_vendorList[_curVendorPage * MAX_DRAWNUM + i]->getPrice()).c_str()));
		SetTextAlign(getMemDC(), TA_LEFT);
	}

	HFONT newFont = CreateFont(30, 0, 0, 0, 1000, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("Sandoll 미생"));
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), newFont);

	wsprintf(listPage, "%d of %d", _curVendorPage + 1, _maxVendorPage + 1);
	outlineTextOut(getMemDC(), 420, 490, listPage, RGB(255, 255, 255), RGB(0, 0, 0), RGB(255, 255, 255), 20);

	SelectObject(getMemDC(), oldFont);
	DeleteObject(newFont);
	DeleteObject(oldFont);
}

void storeScene::drawSellItemList(void)
{
	int curPageItemNum;
	char listPage[256] = "";

	if (_currentInventory == INVENTORY_ITEM)
	{
		if (_curSellPage < _maxSellPage) curPageItemNum = MAX_DRAWNUM;
		else curPageItemNum = _im->getItemInventorySize() % MAX_DRAWNUM;

		for (int i = 0; i < curPageItemNum; i++)
		{
			if (i == _listSelectCursor.getCursorPos()) IMAGEMANAGER->frameRender("storeButton", getMemDC(), 55 + (i % 3) * 280, 220 + (i / 3) * 90, 1, 0);
			else IMAGEMANAGER->frameRender("storeButton", getMemDC(), 55 + (i % 3) * 280, 220 + (i / 3) * 90, 0, 0);

			//맵정보에는 아이템, 웨폰, 아머 이렇게 있다. 접근시 아이템매니저 벡터를 접근한뒤 해당 아이템의 맵정보에 접근가능하다. 
			//아이템 이름 불러온다.                  //아이템 매니저의 벡터를 돌아 -> 맵정보에 [아이템]맵에 있는 벡터arry넘버를 반환받아-> 인벤토리의 아이템 이름을 받아온다.
			TextOut(getMemDC(), 75 + (i % 3) * 280, 235 + (i / 3) * 90, _im->getVItem()[_im->getItemVNum(_curSellPage * MAX_DRAWNUM + i)]->getItemName(),
				strlen(_im->getVItem()[_im->getItemVNum(_curSellPage * MAX_DRAWNUM + i)]->getItemName()));
			//아이템 [가격] 출력
			sprintf(str, "가격");
			TextOut(getMemDC(), 240 + (i % 3) * 280, 235 + (i / 3) * 90, str, strlen(str));
			//아이템 갯수 불러온다.
			TextOut(getMemDC(), 75 + (i % 3) * 280, 255 + (i / 3) * 90, to_string(_im->getItemCount(_curSellPage * MAX_DRAWNUM + i)).c_str(),
				strlen(to_string(_im->getItemCount(_curSellPage * MAX_DRAWNUM + i)).c_str()));
			SetTextAlign(getMemDC(), TA_RIGHT);
			//아이템 가격 불러온다.
			TextOut(getMemDC(), 260 + (i % 3) * 280, 255 + (i / 3) * 90,
				to_string(_im->getVItem()[_im->getItemVNum(_curSellPage * MAX_DRAWNUM + i)]->getPrice() / 2).c_str(),
				strlen(to_string(_im->getVItem()[_im->getItemVNum(_curSellPage * MAX_DRAWNUM + i)]->getPrice() / 2).c_str()));
			SetTextAlign(getMemDC(), TA_LEFT);
		}
	}
	else if (_currentInventory == INVENTORY_WEAPON)
	{
		if (_curSellPage < _maxSellPage) curPageItemNum = MAX_DRAWNUM;
		else curPageItemNum = _im->getWeaponInventorySize() % MAX_DRAWNUM;

		for (int i = 0; i < curPageItemNum; i++)
		{
			if (i == _listSelectCursor.getCursorPos()) IMAGEMANAGER->frameRender("storeButton", getMemDC(), 55 + (i % 3) * 280, 220 + (i / 3) * 90, 1, 0);
			else IMAGEMANAGER->frameRender("storeButton", getMemDC(), 55 + (i % 3) * 280, 220 + (i / 3) * 90, 0, 0);

			//맵정보에는 아이템, 웨폰, 아머 이렇게 있다. 접근시 아이템매니저 벡터를 접근한뒤 해당 아이템의 맵정보에 접근가능하다. 
			//아이템 이름 불러온다.                  //아이템 매니저의 벡터를 돌아 -> 맵정보에 [아이템]맵에 있는 벡터arry넘버를 반환받아-> 인벤토리의 아이템 이름을 받아온다.
			TextOut(getMemDC(), 75 + (i % 3) * 280, 235 + (i / 3) * 90, _im->getVItem()[_im->getWeaponVNum(_curSellPage * MAX_DRAWNUM + i)]->getItemName(), 
				strlen(_im->getVItem()[_im->getWeaponVNum(_curSellPage * MAX_DRAWNUM + i)]->getItemName()));
			//아이템 [가격] 출력
			sprintf(str, "가격");
			TextOut(getMemDC(), 240 + (i % 3) * 280, 235 + (i / 3) * 90, str, strlen(str));
			//아이템 갯수 불러온다.
			TextOut(getMemDC(), 75 + (i % 3) * 280, 255 + (i / 3) * 90, to_string(_im->getWeaponCount(_curSellPage * MAX_DRAWNUM + i)).c_str(),
				strlen(to_string(_im->getWeaponCount(_curSellPage * MAX_DRAWNUM + i)).c_str()));
			SetTextAlign(getMemDC(), TA_RIGHT);
			//아이템 가격 불러온다.
			TextOut(getMemDC(), 260 + (i % 3) * 280, 255 + (i / 3) * 90,
				to_string(_im->getVItem()[_im->getWeaponVNum(_curSellPage * MAX_DRAWNUM + i)]->getPrice() / 2).c_str(),
				strlen(to_string(_im->getVItem()[_im->getWeaponVNum(_curSellPage * MAX_DRAWNUM + i)]->getPrice() / 2).c_str()));
			SetTextAlign(getMemDC(), TA_LEFT);
		}
	}
	else if (_currentInventory == INVENTORY_ARMOR)
	{
		if (_curSellPage < _maxSellPage) curPageItemNum = MAX_DRAWNUM;
		else curPageItemNum = _im->getArmorInventorySize() % MAX_DRAWNUM;

		for (int i = 0; i < curPageItemNum; i++)
		{
			if (i == _listSelectCursor.getCursorPos()) IMAGEMANAGER->frameRender("storeButton", getMemDC(), 55 + (i % 3) * 280, 220 + (i / 3) * 90, 1, 0);
			else IMAGEMANAGER->frameRender("storeButton", getMemDC(), 55 + (i % 3) * 280, 220 + (i / 3) * 90, 0, 0);

			//맵정보에는 아이템, 웨폰, 아머 이렇게 있다. 접근시 아이템매니저 벡터를 접근한뒤 해당 아이템의 맵정보에 접근가능하다. 
			//아이템 이름 불러온다.                  //아이템 매니저의 벡터를 돌아 -> 맵정보에 [아이템]맵에 있는 벡터arry넘버를 반환받아-> 인벤토리의 아이템 이름을 받아온다.
			TextOut(getMemDC(), 75 + (i % 3) * 280, 235 + (i / 3) * 90, _im->getVItem()[_im->getArmorVNum(_curSellPage * MAX_DRAWNUM + i)]->getItemName(),
				strlen(_im->getVItem()[_im->getArmorVNum(_curSellPage * MAX_DRAWNUM + i)]->getItemName()));
			//아이템 [가격] 출력
			sprintf(str, "가격");
			TextOut(getMemDC(), 240 + (i % 3) * 280, 235 + (i / 3) * 90, str, strlen(str));
			//아이템 갯수 불러온다.
			TextOut(getMemDC(), 75 + (i % 3) * 280, 255 + (i / 3) * 90, to_string(_im->getArmorCount(_curSellPage * MAX_DRAWNUM + i)).c_str(),
				strlen(to_string(_im->getArmorCount(_curSellPage * MAX_DRAWNUM + i)).c_str()));
			SetTextAlign(getMemDC(), TA_RIGHT);
			//아이템 가격 불러온다.
			TextOut(getMemDC(), 260 + (i % 3) * 280, 255 + (i / 3) * 90,
				to_string(_im->getVItem()[_im->getArmorVNum(_curSellPage * MAX_DRAWNUM + i)]->getPrice() / 2).c_str(),
				strlen(to_string(_im->getVItem()[_im->getArmorVNum(_curSellPage * MAX_DRAWNUM + i)]->getPrice() / 2).c_str()));
			SetTextAlign(getMemDC(), TA_LEFT);
		}
	}

	HFONT newFont = CreateFont(30, 0, 0, 0, 1000, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("Sandoll 미생"));
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), newFont);

	wsprintf(listPage, "%d of %d", _curSellPage + 1, _maxSellPage + 1);
	outlineTextOut(getMemDC(), 420, 490, listPage, RGB(255, 255, 255), RGB(0, 0, 0), RGB(255, 255, 255), 20);

	SelectObject(getMemDC(), oldFont);
	DeleteObject(newFont);
	DeleteObject(oldFont);
}

void storeScene::drawAmountSelectScreen(void)
{
	char itemName[256] = "";
	int itemPrice = 0;

	if (_prevPos == POS_BUY_LIST)
	{
		strcpy(itemName, _vendorList[_listSelectCursor.getCursorPos() + MAX_DRAWNUM * _curVendorPage]->getItemName());
		itemPrice = _vendorList[_listSelectCursor.getCursorPos() + MAX_DRAWNUM * _curVendorPage]->getPrice();
	}
	else if (_prevPos == POS_SELL_LIST)
	{
		switch (_currentInventory)
		{
		case INVENTORY_ITEM:
			strcpy(itemName, _im->getVItem()[_im->getItemVNum(_listSelectCursor.getCursorPos() + _curSellPage * MAX_DRAWNUM)]->getItemName());
			itemPrice = _im->getVItem()[_im->getItemVNum(_listSelectCursor.getCursorPos() + _curSellPage * MAX_DRAWNUM)]->getPrice() / 2;
			break;
		case INVENTORY_WEAPON:
			strcpy(itemName, _im->getVItem()[_im->getWeaponVNum(_listSelectCursor.getCursorPos() + _curSellPage * MAX_DRAWNUM)]->getItemName());
			itemPrice = _im->getVItem()[_im->getWeaponVNum(_listSelectCursor.getCursorPos() + _curSellPage * MAX_DRAWNUM)]->getPrice() / 2;
			break;
		case INVENTORY_ARMOR:
			strcpy(itemName, _im->getVItem()[_im->getArmorVNum(_listSelectCursor.getCursorPos() + _curSellPage * MAX_DRAWNUM)]->getItemName());
			itemPrice = _im->getVItem()[_im->getArmorVNum(_listSelectCursor.getCursorPos() + _curSellPage * MAX_DRAWNUM)]->getPrice() / 2;
			break;
		default:
			break;
		}
	}

	IMAGEMANAGER->render("amountSelectBox", getMemDC(), 210, 265);

	HFONT newFont = CreateFont(30, 0, 0, 0, 1000, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("Sandoll 미생"));
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), newFont);

	outlineTextOut(getMemDC(), 245, 300, itemName, RGB(255, 255, 255), RGB(0, 0, 0), RGB(255, 255, 255), 30);
	outlineTextOut(getMemDC(), 400, 350, "X", RGB(255, 255, 255), RGB(0, 0, 0), RGB(255, 255, 255), 30);

	SetTextAlign(getMemDC(), TA_RIGHT);
	outlineTextOut(getMemDC(), 460, 350, to_string(_currentAmount).c_str(), RGB(255, 255, 255), RGB(0, 0, 0), RGB(255, 255, 255), 30);
	outlineTextOut(getMemDC(), 440, 390, to_string(itemPrice * _currentAmount).c_str(), RGB(255, 255, 255), RGB(0, 0, 0), RGB(255, 255, 255), 30);
	outlineTextOut(getMemDC(), 490, 390, "Gil", RGB(180, 180, 20), RGB(0, 0, 0), RGB(255, 255, 255), 30);
	SetTextAlign(getMemDC(), TA_LEFT);

	SelectObject(getMemDC(), oldFont);
	DeleteObject(newFont);
	DeleteObject(oldFont);
}

void storeScene::drawAlertScreen(void)
{
	IMAGEMANAGER->render("messageBox", getMemDC(), 100, 265);

	HFONT newFont = CreateFont(40, 0, 0, 0, 1000, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("Sandoll 미생"));
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), newFont);
	
	if (_mbType == MESSAGE_NO_MONEY)
	{
		outlineTextOut(getMemDC(), 180, 330, "소지금이 부족합니다.", RGB(255, 255, 255), RGB(0, 0, 0), RGB(255, 255, 255), 60);
	}

	if (_mbType == MESSAGE_OVER_ITEM)
	{
		outlineTextOut(getMemDC(), 180, 330, "해당 아이템의 최대 보유수를 초과합니다.", RGB(255, 255, 255), RGB(0, 0, 0), RGB(255, 255, 255), 40);
	}

	SelectObject(getMemDC(), oldFont);
	DeleteObject(newFont);
	DeleteObject(oldFont);
}

void storeScene::setStoreKey(string key)
{
	this->release();

	_storeKey = key;

	if (key == "weaponStore")
	{
		_storeName = "무기 상점";
		for (int i = 0; i < _im->getVItem().size(); i++)
		{
			if (_im->getVItem()[i]->getItmeKind() == ITEM_WEAPON && (_im->getVItem()[i]->getPrice() != 0 && _im->getVItem()[i]->getPrice() != 2))
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
				|| _im->getVItem()[i]->getItmeKind() == ITEM_SUB_WEAPON) && (_im->getVItem()[i]->getPrice() != 0 && _im->getVItem()[i]->getPrice() != 2))
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
			if (_im->getVItem()[i]->getItmeKind() == ITEM_EXPENDABLE && (_im->getVItem()[i]->getPrice() != 0 && _im->getVItem()[i]->getPrice() != 2))
			{
				_vendorList.push_back(_im->getVItem()[i]);
			}
		}
	}

	_maxVendorPage = _vendorList.size() / 9;
}
