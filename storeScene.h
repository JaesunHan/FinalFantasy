#pragma once
#include "gameNode.h"
#include "itemManager.h"
#include "cursor.h"

class itemManager;

enum CURSOR_POS
{
	POS_MESSAGEBOX,
	POS_BUY_SELL,
	POS_BUY_LIST,
	POS_SELL_LIST,
	POS_AMOUNT_SELECT,
	POS_END
};

enum MESSAGEBOX_TYPE
{
	MESSAGE_NO_MONEY,
	MESSAGE_OVER_ITEM,
	MESSAGE_NONE
};

enum INVENTORY_KIND
{
	INVENTORY_WEAPON,
	INVENTORY_ARMOR,
	INVENTORY_ITEM,
	INVENTORY_END
};

class storeScene : public gameNode
{
private:
	image* _storeImg;
	string _storeKey;
	string _storeName;
	char str[128];

	MESSAGEBOX_TYPE _mbType;

private:
	cursor _buySellSelectCursor;
	cursor _listSelectCursor;

private:
	itemManager* _im;
	vector<itemMother*> _vendorList;
	int _currentInventory;

private:
	CURSOR_POS _currentPos, _prevPos;
	int _cursorIndex;
	int _listSelectIndex;
	int _listMaxIndex;
	int _currentAmount;

public:
	storeScene();
	~storeScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void keyControl(void);

	void drawStoreInterface(void);
	void drawVendorList(void);
	void drawSellItemList(void);
	void drawAmountSelectScreen(void);
	void drawAlertScreen(void);

	void setStoreKey(string key);

	void setItemManagerAddressLink(itemManager* im) { _im = im; }
};

