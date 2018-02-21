#pragma once
#include "gameNode.h"
#include "itemManager.h"
#include "cursor.h"

class itemManager;

enum CURSOR_POS
{
	POS_BUY_SELL,
	POS_BUY_LIST,
	POS_SELL_LIST,
	POS_END
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

private:
	cursor _buySellSelectCursor;
	cursor _listSelectCursor;

private:
	itemManager* _im;
	vector<itemMother*> _vendorList;
	int _currentInventory;

private:
	CURSOR_POS _currentPos;
	int _cursorIndex;
	int _listSelectIndex;
	int _listMaxIndex;

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

	void setStoreKey(string key);

	void setItemManagerAddressLink(itemManager* im) { _im = im; }
};

