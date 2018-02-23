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

	// 임시로 돈 세팅
	//_im->setMoney(500000);

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
	if (_currentPos == POS_BUY_SELL)
	{
		_buySellSelectCursor.keyControlX(400, 2);

		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			if (!_buySellSelectCursor.getCursorXNum()) _currentPos = POS_BUY_LIST;
			else if (_buySellSelectCursor.getCursorXNum()) _currentPos = POS_SELL_LIST;
		}

		if (KEYMANAGER->isOnceKeyDown(VK_BACK))
		{
			SCENEMANAGER->changeSceneType0("타운맵씬", false);
			return;
		}
	}
	if (_currentPos == POS_BUY_LIST)
	{
		_listSelectCursor.keyControlXY(280, 90, 3, _vendorList.size());

		if (KEYMANAGER->isOnceKeyDown(VK_BACK))
		{
			_currentPos = POS_BUY_SELL;
			_listSelectCursor.init(CURSOR_RIGHT, 20, 240);
		}

		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			if (_im->getMoney() >= _vendorList[_listSelectCursor.getCursorPos()]->getPrice())
			{
				switch (_vendorList[_cursorIndex]->getItmeKind())
				{
				case ITEM_EXPENDABLE:
					if (_im->getItemCountByVector(_vendorList[_listSelectCursor.getCursorPos()]->getItemNumber() - 1) + 1 > 99)
					{
						_prevPos = _currentPos;
						_currentPos = POS_MESSAGEBOX;
						_mbType = MESSAGE_OVER_ITEM;
						return;
					}
					break;
				case ITEM_WEAPON:
					if (_im->getWeaponCountByVector(_vendorList[_listSelectCursor.getCursorPos()]->getItemNumber() - 1) + 1 > 99)
					{
						_prevPos = _currentPos;
						_currentPos = POS_MESSAGEBOX;
						_mbType = MESSAGE_OVER_ITEM;
						return;
					}
					break;
				case ITEM_ARMOR: case ITEM_HELMET: case ITEM_SUB_WEAPON: case ITEM_ACCESSORY:
					if (_im->getArmorCountByVector(_vendorList[_listSelectCursor.getCursorPos()]->getItemNumber() - 1) + 1 > 99)
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

				_prevPos = _currentPos;
				_currentPos = POS_AMOUNT_SELECT;

				//_im->setMoney(_im->getMoney() - _vendorList[_listSelectCursor.getCursorPos()]->getPrice());
			}
			else if (_im->getMoney() < _vendorList[_listSelectCursor.getCursorPos()]->getPrice())
			{
				_prevPos = _currentPos;
				_currentPos = POS_MESSAGEBOX;
				_mbType = MESSAGE_NO_MONEY;
			}
		}
	}
	if (_currentPos == POS_SELL_LIST)
	{
		if (_currentInventory == INVENTORY_WEAPON) _listSelectCursor.keyControlXY(280, 90, 3, _im->getWeaponInventorySize());
		else if (_currentInventory == INVENTORY_ARMOR) _listSelectCursor.keyControlXY(280, 90, 3, _im->getArmorInventorySize());
		else if (_currentInventory == INVENTORY_ITEM) _listSelectCursor.keyControlXY(280, 90, 3, _im->getItemInventorySize());

		if (KEYMANAGER->isOnceKeyDown(VK_BACK))
		{
			_currentPos = POS_BUY_SELL;
			_listSelectCursor.init(CURSOR_RIGHT, 20, 240);
		}

		if (KEYMANAGER->isOnceKeyDown(VK_TAB))
		{
			if (_currentInventory < INVENTORY_END - 1)_currentInventory++;
			else _currentInventory = 0;
			_listSelectCursor.init(CURSOR_RIGHT, 20, 240);
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

			_prevPos = _currentPos;
			_currentPos = POS_AMOUNT_SELECT;
			return;
		}
	}
	if (_currentPos == POS_AMOUNT_SELECT && _prevPos == POS_BUY_LIST)
	{
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			if (_im->getMoney() >= _vendorList[_listSelectCursor.getCursorPos()]->getPrice() * (_currentAmount + 1))
			{
				switch (_vendorList[_cursorIndex]->getItmeKind())
				{
				case ITEM_EXPENDABLE:
					if (_im->getItemCountByVector(_vendorList[_listSelectCursor.getCursorPos()]->getItemNumber() - 1) + _currentAmount + 1 <= 99)
						++_currentAmount;
					break;
				case ITEM_WEAPON:
					if (_im->getWeaponCountByVector(_vendorList[_listSelectCursor.getCursorPos()]->getItemNumber() - 1) + _currentAmount + 1 <= 99)
						++_currentAmount;
					break;
				case ITEM_ARMOR: case ITEM_HELMET: case ITEM_SUB_WEAPON: case ITEM_ACCESSORY:
					if (_im->getArmorCountByVector(_vendorList[_listSelectCursor.getCursorPos()]->getItemNumber() - 1) + _currentAmount + 1 <= 99)
						++_currentAmount;
					break;
				default:
					break;
				}
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			if (_currentAmount > 1) --_currentAmount;
		}

		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			switch (_vendorList[_cursorIndex]->getItmeKind())
			{
			case ITEM_EXPENDABLE:
				_im->changeItemNumber(_vendorList[_listSelectCursor.getCursorPos()]->getItemName(), _currentAmount);

				break;
			case ITEM_WEAPON:
				_im->changeWeaponNumber(_vendorList[_listSelectCursor.getCursorPos()]->getItemName(), _currentAmount);

				break;
			case ITEM_ARMOR: case ITEM_HELMET: case ITEM_SUB_WEAPON: case ITEM_ACCESSORY:
				_im->changeArmorNumber(_vendorList[_listSelectCursor.getCursorPos()]->getItemName(), _currentAmount);
				break;
			default:
				break;
			}
			
			_im->setMoney(_im->getMoney() - _vendorList[_listSelectCursor.getCursorPos()]->getPrice() * _currentAmount);

			_currentPos = _prevPos;
			_currentAmount = 1;
		}

		if (KEYMANAGER->isOnceKeyDown(VK_BACK))
		{
			_currentPos = _prevPos;
			_currentAmount = 1;
		}
	}
	if (_currentPos == POS_AMOUNT_SELECT && _prevPos == POS_SELL_LIST)
	{
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			if (_currentInventory == INVENTORY_WEAPON)
			{
				if (_im->getWeaponInventorySize() <= 0) return;
				if (_currentAmount + 1 <= _im->getWeaponCount(_listSelectCursor.getCursorPos())) ++_currentAmount;
			}
			else if (_currentInventory == INVENTORY_ARMOR)
			{
				if (_im->getArmorInventorySize() <= 0) return;
				if (_currentAmount + 1 <= _im->getArmorCount(_listSelectCursor.getCursorPos())) ++_currentAmount;
			}
			else if (_currentInventory == INVENTORY_ITEM)
			{
				if (_im->getItemInventorySize() <= 0) return;
				if (_currentAmount + 1 <= _im->getItemCount(_listSelectCursor.getCursorPos())) ++_currentAmount;
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			if (_currentAmount > 1) --_currentAmount;
		}

		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			if (_currentInventory == INVENTORY_WEAPON)
			{
				if (_im->getWeaponInventorySize() <= 0) return;

				_im->setMoney(_im->getMoney() + _im->getVItem()[_im->getWeaponVNum(_listSelectCursor.getCursorPos())]->getPrice() / 2 * _currentAmount);
				_im->changeWeaponNumber(_im->getWeaponVNum(_listSelectCursor.getCursorPos()), -_currentAmount);
			}
			else if (_currentInventory == INVENTORY_ARMOR)
			{
				if (_im->getArmorInventorySize() <= 0) return;

				_im->setMoney(_im->getMoney() + _im->getVItem()[_im->getArmorVNum(_listSelectCursor.getCursorPos())]->getPrice() / 2 * _currentAmount);
				_im->changeArmorNumber(_im->getArmorVNum(_listSelectCursor.getCursorPos()), -_currentAmount);
			}
			else if (_currentInventory == INVENTORY_ITEM)
			{
				if (_im->getItemInventorySize() <= 0) return;

				_im->setMoney(_im->getMoney() + _im->getVItem()[_im->getItemVNum(_listSelectCursor.getCursorPos())]->getPrice() / 2 * _currentAmount);
				_im->changeItemNumber(_im->getItemVNum(_listSelectCursor.getCursorPos()), -_currentAmount);
			}

			_listSelectCursor.resetCursorPos();
			
			_currentPos = _prevPos;
			_currentAmount = 1;
		}

		if (KEYMANAGER->isOnceKeyDown(VK_BACK))
		{
			_currentPos = _prevPos;
			_currentAmount = 1;
		}
	}
	if (_currentPos == POS_MESSAGEBOX)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_BACK) || KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
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
	for (int i = 0; i < _vendorList.size(); i++)
	{
		if (i == _listSelectCursor.getCursorPos())IMAGEMANAGER->frameRender("storeButton", getMemDC(), 55 + (i % 3) * 280, 220 + (i / 3) * 90, 1, 0);
		else IMAGEMANAGER->frameRender("storeButton", getMemDC(), 55 + (i % 3) * 280, 220 + (i / 3) * 90, 0, 0);

		TextOut(getMemDC(), 75 + (i % 3) * 280, 235 + (i / 3) * 90, _vendorList[i]->getItemName(), strlen(_vendorList[i]->getItemName()));

		SetTextAlign(getMemDC(), TA_RIGHT);
		TextOut(getMemDC(), 260 + (i % 3) * 280, 255 + (i / 3) * 90,
			to_string(_vendorList[i]->getPrice()).c_str(), strlen(to_string(_vendorList[i]->getPrice()).c_str()));
		SetTextAlign(getMemDC(), TA_LEFT);
	}
}

void storeScene::drawSellItemList(void)
{
	if (_currentInventory == INVENTORY_ITEM)
	{
		for (int i = 0; i < _im->getItemInventorySize(); i++)
		{
			if (i == _listSelectCursor.getCursorPos()) IMAGEMANAGER->frameRender("storeButton", getMemDC(), 55 + (i % 3) * 280, 220 + (i / 3) * 90, 1, 0);
			else IMAGEMANAGER->frameRender("storeButton", getMemDC(), 55 + (i % 3) * 280, 220 + (i / 3) * 90, 0, 0);

			//맵정보에는 아이템, 웨폰, 아머 이렇게 있다. 접근시 아이템매니저 벡터를 접근한뒤 해당 아이템의 맵정보에 접근가능하다. 
			//아이템 이름 불러온다.                  //아이템 매니저의 벡터를 돌아 -> 맵정보에 [아이템]맵에 있는 벡터arry넘버를 반환받아-> 인벤토리의 아이템 이름을 받아온다.
			TextOut(getMemDC(), 75 + (i % 3) * 280, 235 + (i / 3) * 90, _im->getVItem()[_im->getItemVNum(i)]->getItemName(), strlen(_im->getVItem()[_im->getItemVNum(i)]->getItemName()));
			//아이템 [가격] 출력
			sprintf(str, "가격");
			TextOut(getMemDC(), 240 + (i % 3) * 280, 235 + (i / 3) * 90, str, strlen(str));
			//아이템 갯수 불러온다.
			TextOut(getMemDC(), 75 + (i % 3) * 280, 255 + (i / 3) * 90, to_string(_im->getItemCount(i)).c_str(), strlen(to_string(_im->getItemCount(i)).c_str()));
			SetTextAlign(getMemDC(), TA_RIGHT);
			//아이템 가격 불러온다.
			TextOut(getMemDC(), 260 + (i % 3) * 280, 255 + (i / 3) * 90,
				to_string(_im->getVItem()[_im->getItemVNum(i)]->getPrice() / 2).c_str(), strlen(to_string(_im->getVItem()[_im->getItemVNum(i)]->getPrice() / 2).c_str()));
			SetTextAlign(getMemDC(), TA_LEFT);
		}
	}
	else if (_currentInventory == INVENTORY_WEAPON)
	{
		for (int i = 0; i < _im->getWeaponInventorySize(); i++)
		{
			if (i == _listSelectCursor.getCursorPos()) IMAGEMANAGER->frameRender("storeButton", getMemDC(), 55 + (i % 3) * 280, 220 + (i / 3) * 90, 1, 0);
			else IMAGEMANAGER->frameRender("storeButton", getMemDC(), 55 + (i % 3) * 280, 220 + (i / 3) * 90, 0, 0);

			//맵정보에는 아이템, 웨폰, 아머 이렇게 있다. 접근시 아이템매니저 벡터를 접근한뒤 해당 아이템의 맵정보에 접근가능하다. 
			//아이템 이름 불러온다.                  //아이템 매니저의 벡터를 돌아 -> 맵정보에 [아이템]맵에 있는 벡터arry넘버를 반환받아-> 인벤토리의 아이템 이름을 받아온다.
			TextOut(getMemDC(), 75 + (i % 3) * 280, 235 + (i / 3) * 90, _im->getVItem()[_im->getWeaponVNum(i)]->getItemName(), strlen(_im->getVItem()[_im->getWeaponVNum(i)]->getItemName()));
			//아이템 [가격] 출력
			sprintf(str, "가격");
			TextOut(getMemDC(), 240 + (i % 3) * 280, 235 + (i / 3) * 90, str, strlen(str));
			//아이템 갯수 불러온다.
			TextOut(getMemDC(), 75 + (i % 3) * 280, 255 + (i / 3) * 90, to_string(_im->getWeaponCount(i)).c_str(), strlen(to_string(_im->getWeaponCount(i)).c_str()));
			SetTextAlign(getMemDC(), TA_RIGHT);
			//아이템 가격 불러온다.
			TextOut(getMemDC(), 260 + (i % 3) * 280, 255 + (i / 3) * 90,
				to_string(_im->getVItem()[_im->getWeaponVNum(i)]->getPrice() / 2).c_str(), strlen(to_string(_im->getVItem()[_im->getWeaponVNum(i)]->getPrice() / 2).c_str()));
			SetTextAlign(getMemDC(), TA_LEFT);
		}
	}
	else if (_currentInventory == INVENTORY_ARMOR)
	{
		for (int i = 0; i < _im->getArmorInventorySize(); i++)
		{
			if (i == _listSelectCursor.getCursorPos()) IMAGEMANAGER->frameRender("storeButton", getMemDC(), 55 + (i % 3) * 280, 220 + (i / 3) * 90, 1, 0);
			else IMAGEMANAGER->frameRender("storeButton", getMemDC(), 55 + (i % 3) * 280, 220 + (i / 3) * 90, 0, 0);

			//맵정보에는 아이템, 웨폰, 아머 이렇게 있다. 접근시 아이템매니저 벡터를 접근한뒤 해당 아이템의 맵정보에 접근가능하다. 
			//아이템 이름 불러온다.                  //아이템 매니저의 벡터를 돌아 -> 맵정보에 [아이템]맵에 있는 벡터arry넘버를 반환받아-> 인벤토리의 아이템 이름을 받아온다.
			TextOut(getMemDC(), 75 + (i % 3) * 280, 235 + (i / 3) * 90, _im->getVItem()[_im->getArmorVNum(i)]->getItemName(), strlen(_im->getVItem()[_im->getArmorVNum(i)]->getItemName()));
			//아이템 [가격] 출력
			sprintf(str, "가격");
			TextOut(getMemDC(), 240 + (i % 3) * 280, 235 + (i / 3) * 90, str, strlen(str));
			//아이템 갯수 불러온다.
			TextOut(getMemDC(), 75 + (i % 3) * 280, 255 + (i / 3) * 90, to_string(_im->getArmorCount(i)).c_str(), strlen(to_string(_im->getArmorCount(i)).c_str()));
			SetTextAlign(getMemDC(), TA_RIGHT);
			//아이템 가격 불러온다.
			TextOut(getMemDC(), 260 + (i % 3) * 280, 255 + (i / 3) * 90,
				to_string(_im->getVItem()[_im->getArmorVNum(i)]->getPrice() / 2).c_str(), strlen(to_string(_im->getVItem()[_im->getArmorVNum(i)]->getPrice() / 2).c_str()));
			SetTextAlign(getMemDC(), TA_LEFT);
		}
	}
}

void storeScene::drawAmountSelectScreen(void)
{
	char itemName[256] = "";
	int itemPrice = 0;

	if (_prevPos == POS_BUY_LIST)
	{
		strcpy(itemName, _vendorList[_listSelectCursor.getCursorPos()]->getItemName());
		itemPrice = _vendorList[_listSelectCursor.getCursorPos()]->getPrice();
	}
	else if (_prevPos == POS_SELL_LIST)
	{
		switch (_currentInventory)
		{
		case INVENTORY_ITEM:
			strcpy(itemName, _im->getVItem()[_im->getItemVNum(_listSelectCursor.getCursorPos())]->getItemName());
			itemPrice = _im->getVItem()[_im->getItemVNum(_listSelectCursor.getCursorPos())]->getPrice() / 2;
			break;
		case INVENTORY_WEAPON:
			strcpy(itemName, _im->getVItem()[_im->getWeaponVNum(_listSelectCursor.getCursorPos())]->getItemName());
			itemPrice = _im->getVItem()[_im->getWeaponVNum(_listSelectCursor.getCursorPos())]->getPrice() / 2;
			break;
		case INVENTORY_ARMOR:
			strcpy(itemName, _im->getVItem()[_im->getArmorVNum(_listSelectCursor.getCursorPos())]->getItemName());
			itemPrice = _im->getVItem()[_im->getArmorVNum(_listSelectCursor.getCursorPos())]->getPrice() / 2;
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
}
