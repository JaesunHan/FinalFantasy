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
	map<string, pair<int, int>>					_arrItemInventory;
	map<string, pair<int, int>>					_arrWeaponInventory;
	map<string, pair<int, int>>					_arrArmorInventory;
	map<string, pair<int, int>>::iterator		_iterInventory;
	unsigned int								_gil;

public:
	itemManager();
	~itemManager();

	HRESULT init();

	vector<itemMother*> getVItem() { return _vItem; }
	void saveInventory(char* fileName);
	void loadInventory(char* fileName);
	int getItemVNum(int num);
	int getItemCount(int num);
	int getWeaponVNum(int num);
	int getWeaponCount(int num);
	int getArmorVNum(int num);
	int getArmorCount(int num);
	void setItemInventory(int vectorNum, int count);
	void setItemInventory(string keyName, int count);
	void changeItemNumber(int vectorNum, int number);
	void changeItemNumber(string keyName, int number);
	void setWeaponInventory(int vectorNum, int count);
	void setWeaponInventory(string keyName, int count);
	void changeWeaponNumber(int vectorNum, int number);
	void changeWeaponNumber(string keyName, int number);
	void setArmorInventory(int vectorNum, int count);
	void setArmorInventory(string keyName, int count);
	void changeArmorNumber(int vectorNum, int number);
	void changeArmorNumber(string keyName, int number);
	inline int getItemInventorySize() { return _arrItemInventory.size(); }
	inline int getWeaponInventorySize() { return _arrWeaponInventory.size(); }
	inline int getArmorInventorySize() { return _arrArmorInventory.size(); }
	inline unsigned int getMoney() { return _gil; }

};

