#pragma once
#include "gameNode.h"
#include "itemManager.h"

class itemManager;

class storeScene : public gameNode
{
private:
	image* _storeImg;
	string _storeKey;

private:
	itemManager* _im;
	vector<itemMother*> _vendorList;

public:
	storeScene();
	~storeScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void setStoreKey(string key);

	void setItemManagerAddressLink(itemManager* im) { _im = im; }
};

