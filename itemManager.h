#pragma once
#include "gameNode.h"
#include <vector>
#include <map>
#include "expendablesItem.h"
#include "weaponItem.h"
#include "armorItem.h"

class itemManager : public gameNode
{
private:
	vector<itemMother*>							_vItem;
	//º¤ÅÍ ¹øÈ£, °¹¼ö	
	pair<int, int>								_element;		
	map<string, pair<int, int>>					_arrInventory;
	map<string, pair<int, int>>::iterator		_iterInventory;

public:
	itemManager();
	~itemManager();

	HRESULT init();

	vector<itemMother*> getVItem() { return _vItem; }
	void saveInventory(char* fileName);
	void loadInventory(char* fileName);
	int getItemVNum(int num);
	int getItemCount(int num);
	void setInventory(int vectorNum, int count);
	void setInventory(string keyName, int count);
	inline int getInventorySize() { return _arrInventory.size(); }

};

