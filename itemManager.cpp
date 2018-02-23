#include "stdafx.h"
#include "itemManager.h"
#include "battlePlayerMother.h"
#include "playerManager.h"


itemManager::itemManager()
{
}


itemManager::~itemManager()
{
}

HRESULT itemManager::init()
{
	

	//======================================== 소모품 ========================================
	
	expendablesItem* expendables = new expendablesItem;

	expendables->init(1, ITEM_EXPENDABLE, "에테르", "플레이어 마력 150 회복", 2, 0, 150, false, false, true, false, false);
	_vItem.push_back(expendables);

	expendables = new expendablesItem;
	expendables->init(2, ITEM_EXPENDABLE, "육포", "플레이어 체력 150 회복", 2, 150, 0, false, false, true, false, false);
	_vItem.push_back(expendables);

	expendables = new expendablesItem;
	expendables->init(3, ITEM_EXPENDABLE, "엘릭서", "플레이어 체력 마력 100% 회복", 2, 100, 100, false, false, true, true, true);
	_vItem.push_back(expendables);

	expendables = new expendablesItem;
	expendables->init(4, ITEM_EXPENDABLE, "메가엘릭서", "전체 플레이어 체력 마력 100% 회복", 2, 100, 100, false, true, true, true, true);
	_vItem.push_back(expendables);

	expendables = new expendablesItem;
	expendables->init(5, ITEM_EXPENDABLE, "피닉스깃털", "행동불능이 된 플레이어 회복", 500, 50, 0, true, false, true, false, false);
	_vItem.push_back(expendables);

	expendables = new expendablesItem;
	expendables->init(6, ITEM_EXPENDABLE, "포션", "플레이어 체력 20% 회복", 300, 20, 0, false, false, true, true, false);
	_vItem.push_back(expendables);

	expendables = new expendablesItem;
	expendables->init(7, ITEM_EXPENDABLE, "토닉", "플레이어 마력 50 회복", 200, 0, 50, false, false, true, false, false);
	_vItem.push_back(expendables);

	expendables = new expendablesItem;
	expendables->init(8, ITEM_EXPENDABLE, "침낭", "플레이어 체력 마력 100% 회복 ( 월드맵에서만 사용 가능 )", 500, 100, 100, false, true, false, true, true);
	_vItem.push_back(expendables);

	expendables = new expendablesItem;
	expendables->init(9, ITEM_EXPENDABLE, "텐트", "전체 플레이어 체력 마력 100% 회복 ( 월드맵에서만 사용 가능 )", 1200, 100, 100, true, true, false, true, true);
	_vItem.push_back(expendables);

	expendables = new expendablesItem;
	expendables->init(10, ITEM_EXPENDABLE, "X-에테르", "플레이어 마력 100% 회복", 5000, 100, 0, false, false, true, false, true);
	_vItem.push_back(expendables);

	expendables = new expendablesItem;
	expendables->init(11, ITEM_EXPENDABLE, "X-포션", "플레이어 체력 100% 회복", 5000, 0, 100, false, false, true, true, false);
	_vItem.push_back(expendables);

	//=======================================================================================

	//======================================== 무기 =========================================

	weaponItem* weapon = new weaponItem;

	//weapon->init(ITEM_WEAPON, "DefaultWeapon", "맨주먹공격무기이다", 0, 10, 100);
	//_vItem.push_back(weapon);

	weapon->init(12, ITEM_WEAPON, "Mithril Knife", "...", 300, 30, 180);
	_vItem.push_back(weapon);

	weapon = new weaponItem;
	weapon->init(13, ITEM_WEAPON, "Dirk", "...", 150, 26, 180);
	_vItem.push_back(weapon);

	weapon = new weaponItem;
	weapon->init(14, ITEM_WEAPON, "Thief Knife", "...", 2, 88, 180);
	_vItem.push_back(weapon);

	weapon = new weaponItem;
	weapon->init(15, ITEM_WEAPON, "Illumina", "...", 2, 255, 255);
	_vItem.push_back(weapon);

	weapon = new weaponItem;
	weapon->init(16, ITEM_WEAPON, "Crystal", "...", 15000, 167, 150);
	_vItem.push_back(weapon);

	weapon = new weaponItem;
	weapon->init(17, ITEM_WEAPON, "Striker", "...", 2, 190, 180);
	_vItem.push_back(weapon);

	weapon = new weaponItem;
	weapon->init(18, ITEM_WEAPON, "Full Moon", "...", 2500, 95, 230);
	_vItem.push_back(weapon);

	weapon = new weaponItem;
	weapon->init(19, ITEM_WEAPON, "Wing Edge", "...", 2, 198, 230);
	_vItem.push_back(weapon);

	weapon = new weaponItem;
	weapon->init(20, ITEM_WEAPON, "Morning Start", "...", 5000, 109, 150);
	_vItem.push_back(weapon);

	weapon = new weaponItem;
	weapon->init(21, ITEM_WEAPON, "Shuriken", "...", 30, 86, 230);
	_vItem.push_back(weapon);

	weapon = new weaponItem;
	weapon->init(22, ITEM_WEAPON, "KKongChi", "전설의 무기. 구우면 더 쎄진다.", 3980, 9999, 9999);
	_vItem.push_back(weapon);
	//=======================================================================================

	//======================================== 갑옷 =========================================

	armorItem* armor = new armorItem;
	armor->init(23, ITEM_ARMOR, "크리스탈 갑옷", "_a_Def + 72, _m_Def + 49", 17000, 72, 49);
	_vItem.push_back(armor);

	armor = new armorItem;
	armor->init(24, ITEM_ARMOR, "다이아몬드 갑옷", "_a_Def + 56, _m_Def + 38", 12000, 56, 38);
	_vItem.push_back(armor);

	armor = new armorItem;
	armor->init(25, ITEM_ARMOR, "황금 갑옷", "_a_Def + 40, _m_Def + 27", 8000, 40, 27);
	_vItem.push_back(armor);

	armor = new armorItem;
	armor->init(26, ITEM_ARMOR, "미스릴 갑옷", "_a_Def + 28, _m_Def + 19", 3500, 28, 19);
	_vItem.push_back(armor);

	armor = new armorItem;
	armor->init(27, ITEM_ARMOR, "가죽 갑옷", "_a_Def + 18, _m_Def + 12", 500, 18, 12);
	_vItem.push_back(armor);

	//=======================================================================================

	//======================================== 투구 =========================================

	armor = new armorItem;
	armor->init(28, ITEM_HELMET, "크리스탈 투구", "_a_Def + 29, _m_Def + 19", 10000, 29, 19);
	_vItem.push_back(armor);

	armor = new armorItem;
	armor->init(29, ITEM_HELMET, "다이아몬드 투구", "_a_Def + 27, _m_Def + 18", 7500, 27, 18);
	_vItem.push_back(armor);

	armor = new armorItem;
	armor->init(30, ITEM_HELMET, "황금 투구", "_a_Def + 22, _m_Def + 15", 4000, 22, 15);
	_vItem.push_back(armor);

	armor = new armorItem;
	armor->init(31, ITEM_HELMET, "미스릴 투구", "_a_Def + 20, _m_Def + 13", 2000, 20, 13);
	_vItem.push_back(armor);

	armor = new armorItem;
	armor->init(32, ITEM_HELMET, "깃털 모자", "_a_Def + 14, _m_Def + 9", 250, 14, 9);
	_vItem.push_back(armor);
	
	//=======================================================================================
	
	//======================================== 방패 =========================================
	
	armor = new armorItem;
	armor->init(33, ITEM_SUB_WEAPON, "크리스탈 방패", "_a_Def + 50, _m_Def + 34", 7000, 50, 34);
	_vItem.push_back(armor);

	armor = new armorItem;
	armor->init(34, ITEM_SUB_WEAPON, "다이아몬드 방패", "_a_Def + 40, _m_Def + 27", 3500, 40, 27);
	_vItem.push_back(armor);

	armor = new armorItem;
	armor->init(35, ITEM_SUB_WEAPON, "황금 방패", "_a_Def + 34, _m_Def + 23", 2500, 34, 23);
	_vItem.push_back(armor);

	armor = new armorItem;
	armor->init(36, ITEM_SUB_WEAPON, "미스릴 방패", "_a_Def + 27, _m_Def + 18", 1200, 27, 18);
	_vItem.push_back(armor);

	armor = new armorItem;
	armor->init(37, ITEM_SUB_WEAPON, "버클러 방패", "_a_Def + 16, _m_Def + 10", 200, 16, 10);
	_vItem.push_back(armor);

	//=======================================================================================

	//======================================== 디폴트 ========================================

	//기본 무기 세팅
	weaponItem* defaultWeapon = new weaponItem;
	defaultWeapon->init(0, ITEM_WEAPON, "맨손주먹", "맨손주먹공격무기이다", 0, 10, 100);
	_vItem.push_back(defaultWeapon);

	//기본 갑옷 세팅
	armorItem* defaultArmor = new armorItem;
	defaultArmor->init(-1, ITEM_ARMOR, "", "", 0, 0, 0);
	_vItem.push_back(defaultArmor);

	//기본 헬멧 세팅
	armorItem* defaultHelmet = new armorItem;
	defaultHelmet->init(-2, ITEM_HELMET, "", "", 0, 0, 0);
	_vItem.push_back(defaultHelmet);

	//기본 서브 무기 세팅
	armorItem* defaultSubWeapon = new armorItem;
	defaultSubWeapon->init(-3, ITEM_SUB_WEAPON, "", "", 0, 0, 0);
	_vItem.push_back(defaultSubWeapon);

	return S_OK;
}

void itemManager::saveInventory(char* fileName)
{
	char itemListA[2048];
	char weaponListA[2048];
	char armorListA[2048];

	char maxItem[128];
	char maxWeapon[128];
	char maxArmor[128];

	char gil[1024];

	char tempPairFirst[128];
	char tempPairSecond[128];

	ZeroMemory(itemListA, sizeof(itemListA));
	ZeroMemory(weaponListA, sizeof(weaponListA));
	ZeroMemory(armorListA, sizeof(armorListA));

	ZeroMemory(maxItem, sizeof(maxItem));
	ZeroMemory(maxWeapon, sizeof(maxWeapon));
	ZeroMemory(maxArmor, sizeof(maxArmor));

	ZeroMemory(gil, sizeof(gil));

	ZeroMemory(tempPairFirst, sizeof(tempPairFirst));
	ZeroMemory(tempPairSecond, sizeof(tempPairSecond));

	wsprintf(maxItem, "%d", _arrItemInventory.size());
	wsprintf(maxWeapon, "%d", _arrWeaponInventory.size());
	wsprintf(maxArmor, "%d", _arrArmorInventory.size());

	itoa(_gil, gil, 10);

	strncat_s(itemListA, sizeof(itemListA), maxItem, sizeof(maxItem));
	strncat_s(weaponListA, sizeof(weaponListA), maxWeapon, sizeof(maxWeapon));
	strncat_s(armorListA, sizeof(armorListA), maxArmor, sizeof(maxArmor));

	for (_iterInventory = _arrItemInventory.begin(); _iterInventory != _arrItemInventory.end(); ++_iterInventory)
	{
		wsprintf(tempPairFirst, "%d", _iterInventory->second.first);
		wsprintf(tempPairSecond, "%d", _iterInventory->second.second);
		strcat(itemListA, ",");
		strncat_s(itemListA, sizeof(itemListA), tempPairFirst, sizeof(tempPairFirst));
		strcat(itemListA, ",");
		strncat_s(itemListA, sizeof(itemListA), tempPairSecond, sizeof(tempPairSecond));
	}
	for (_iterInventory = _arrWeaponInventory.begin(); _iterInventory != _arrWeaponInventory.end(); ++_iterInventory)
	{
		wsprintf(tempPairFirst, "%d", _iterInventory->second.first);
		wsprintf(tempPairSecond, "%d", _iterInventory->second.second);
		strcat(weaponListA, ",");
		strncat_s(weaponListA, sizeof(weaponListA), tempPairFirst, sizeof(tempPairFirst));
		strcat(weaponListA, ",");
		strncat_s(weaponListA, sizeof(weaponListA), tempPairSecond, sizeof(tempPairSecond));
	}
	for (_iterInventory = _arrArmorInventory.begin(); _iterInventory != _arrArmorInventory.end(); ++_iterInventory)
	{
		wsprintf(tempPairFirst, "%d", _iterInventory->second.first);
		wsprintf(tempPairSecond, "%d", _iterInventory->second.second);
		strcat(armorListA, ",");
		strncat_s(armorListA, sizeof(armorListA), tempPairFirst, sizeof(tempPairFirst));
		strcat(armorListA, ",");
		strncat_s(armorListA, sizeof(armorListA), tempPairSecond, sizeof(tempPairSecond));
	}

	INIDATA->addData("Inventory", "ItemList", itemListA);
	INIDATA->addData("Inventory", "WeaponList", weaponListA);
	INIDATA->addData("Inventory", "ArmorList", armorListA);
	INIDATA->addData("Inventory", "Gil", gil);
	INIDATA->iniSave(fileName);
}

void itemManager::loadInventory(char* fileName)
{
	vector<string> vArrayItem;
	vector<string> vArrayWeapon;
	vector<string> vArrayArmor;
	
	char* separator = ",";
	char* token;

	char* itemContext;
	char* weaponContext;
	char* armorContext;

	int maxItemI;
	int maxWeaponI;
	int maxArmorI;

	char str[256];
	char dir[256];

	ZeroMemory(dir, sizeof(dir));
	sprintf(dir, "\\%s.ini", fileName);

	GetCurrentDirectory(256, str);
	strncat_s(str, 256, dir, 254);

	char itemData[2048] = { NULL };
	char weaponData[2048] = { NULL };
	char armorData[2048] = { NULL };

	GetPrivateProfileString("Inventory", "ItemList", NULL, itemData, 2048, str);
	GetPrivateProfileString("Inventory", "WeaponList", NULL, weaponData, 2048, str);
	GetPrivateProfileString("Inventory", "ArmorList", NULL, armorData, 2048, str);

	token = strtok_s(itemData, separator, &itemContext);
	maxItemI = atoi(token);
	token = strtok_s(weaponData, separator, &weaponContext);
	maxWeaponI = atoi(token);
	token = strtok_s(armorData, separator, &armorContext);
	maxArmorI = atoi(token);

	int tempVectorNum;
	int tempCount;
	for (int i = 0; i < maxItemI; ++i)
	{
		token = strtok_s(NULL, separator, &itemContext);
		tempVectorNum = atoi(token);
		token = strtok_s(NULL, separator, &itemContext);
		tempCount = atoi(token);
		setItemInventory(tempVectorNum, tempCount);
	}
	for (int i = 0; i < maxWeaponI; ++i)
	{
		token = strtok_s(NULL, separator, &weaponContext);
		tempVectorNum = atoi(token);
		token = strtok_s(NULL, separator, &weaponContext);
		tempCount = atoi(token);
		setWeaponInventory(tempVectorNum, tempCount);
	}
	for (int i = 0; i < maxArmorI; ++i)
	{
		token = strtok_s(NULL, separator, &armorContext);
		tempVectorNum = atoi(token);
		token = strtok_s(NULL, separator, &armorContext);
		tempCount = atoi(token);
		setArmorInventory(tempVectorNum, tempCount);
	}

	_gil = INIDATA->loadDataInterger(fileName, "Inventory", "Gil");
}

void itemManager::setItemInventory(int vectorNum, int count)
{
	_element = make_pair(vectorNum, count);
	_iterInventory = _arrItemInventory.find(_vItem[vectorNum]->getItemName());
	if (_iterInventory != _arrItemInventory.end())
	{
		_arrItemInventory[_vItem[vectorNum]->getItemName()] = _element;
	}
	else
	{
		_arrItemInventory.insert(make_pair(_vItem[vectorNum]->getItemName(), _element));
	}
}

void itemManager::setItemInventory(string keyName, int count)
{
	_iterInventory = _arrItemInventory.find(keyName);
	if (_iterInventory != _arrItemInventory.end())
	{
		_arrItemInventory[keyName].second = count;
	}
	else
	{
		for (int i = 0; i < _vItem.size(); ++i)
		{
			if (_vItem[i]->getItemName() == keyName)
			{
				setItemInventory(i, count);
				break;
			}
		}
	}
}

void itemManager::changeItemNumber(int vectorNum, int number)
{
	_iterInventory = _arrItemInventory.find(_vItem[vectorNum]->getItemName());
	if (_iterInventory != _arrItemInventory.end())
	{
		_arrItemInventory[_vItem[vectorNum]->getItemName()].second += number;
	}
	else if (number > 0)
	{
		_element = make_pair(vectorNum, number);
		_arrItemInventory.insert(make_pair(_vItem[vectorNum]->getItemName(), _element));
	}
	if (_arrItemInventory[_vItem[vectorNum]->getItemName()].second <= 0)
	{
		_arrItemInventory.erase(_vItem[vectorNum]->getItemName());
	}
}

void itemManager::changeItemNumber(string keyName, int number)
{
	_iterInventory = _arrItemInventory.find(keyName);
	if (_iterInventory != _arrItemInventory.end())
	{
		_arrItemInventory[keyName].second += number;
	}
	else if (number > 0)
	{
		for (int i = 0; i < _vItem.size(); ++i)
		{
			if (_vItem[i]->getItemName() == keyName)
			{
				setItemInventory(i, number);
				break;
			}
		}
	}
	if (_arrItemInventory[keyName].second <= 0)
	{
		_arrItemInventory.erase(keyName);
	}
}

void itemManager::setWeaponInventory(int vectorNum, int count)
{
	_element = make_pair(vectorNum, count);
	_iterInventory = _arrWeaponInventory.find(_vItem[vectorNum]->getItemName());
	if (_iterInventory != _arrWeaponInventory.end())
	{
		_arrWeaponInventory[_vItem[vectorNum]->getItemName()] = _element;
	}
	else
	{
		_arrWeaponInventory.insert(make_pair(_vItem[vectorNum]->getItemName(), _element));
	}
}

void itemManager::setWeaponInventory(string keyName, int count)
{
	_iterInventory = _arrWeaponInventory.find(keyName);
	if (_iterInventory != _arrWeaponInventory.end())
	{
		_arrWeaponInventory[keyName].second = count;
	}
	else
	{
		for (int i = 0; i < _vItem.size(); ++i)
		{
			if (_vItem[i]->getItemName() == keyName)
			{
				setWeaponInventory(i, count);
				break;
			}
		}
	}
}

void itemManager::changeWeaponNumber(int vectorNum, int number)
{
	_iterInventory = _arrWeaponInventory.find(_vItem[vectorNum]->getItemName());
	if (_iterInventory != _arrWeaponInventory.end())
	{
		_arrWeaponInventory[_vItem[vectorNum]->getItemName()].second += number;
	}
	else if (number > 0)
	{
		_element = make_pair(vectorNum, number);
		_arrWeaponInventory.insert(make_pair(_vItem[vectorNum]->getItemName(), _element));
	}
	if (_arrWeaponInventory[_vItem[vectorNum]->getItemName()].second <= 0)
	{
		_arrWeaponInventory.erase(_vItem[vectorNum]->getItemName());
	}
}

void itemManager::changeWeaponNumber(string keyName, int number)
{
	_iterInventory = _arrWeaponInventory.find(keyName);
	if (_iterInventory != _arrWeaponInventory.end())
	{
		_arrWeaponInventory[keyName].second += number;
	}
	else if (number > 0)
	{
		for (int i = 0; i < _vItem.size(); ++i)
		{
			if (_vItem[i]->getItemName() == keyName)
			{
				setWeaponInventory(i, number);
				break;
			}
		}
	}
	if (_arrWeaponInventory[keyName].second <= 0)
	{
		_arrWeaponInventory.erase(keyName);
	}
}

void itemManager::setArmorInventory(int vectorNum, int count)
{
	_element = make_pair(vectorNum, count);
	_iterInventory = _arrArmorInventory.find(_vItem[vectorNum]->getItemName());
	if (_iterInventory != _arrArmorInventory.end())
	{
		_arrArmorInventory[_vItem[vectorNum]->getItemName()] = _element;
	}
	else
	{
		_arrArmorInventory.insert(make_pair(_vItem[vectorNum]->getItemName(), _element));
	}
}

void itemManager::setArmorInventory(string keyName, int count)
{
	_iterInventory = _arrArmorInventory.find(keyName);
	if (_iterInventory != _arrArmorInventory.end())
	{
		_arrArmorInventory[keyName].second = count;
	}
	else
	{
		for (int i = 0; i < _vItem.size(); ++i)
		{
			if (_vItem[i]->getItemName() == keyName)
			{
				setArmorInventory(i, count);
				break;
			}
		}
	}
}

void itemManager::changeArmorNumber(int vectorNum, int number)
{
	_iterInventory = _arrArmorInventory.find(_vItem[vectorNum]->getItemName());
	if (_iterInventory != _arrArmorInventory.end())
	{
		_arrArmorInventory[_vItem[vectorNum]->getItemName()].second += number;
	}
	else if (number > 0)
	{
		_element = make_pair(vectorNum, number);
		_arrArmorInventory.insert(make_pair(_vItem[vectorNum]->getItemName(), _element));
	}
	if (_arrArmorInventory[_vItem[vectorNum]->getItemName()].second <= 0)
	{
		_arrArmorInventory.erase(_vItem[vectorNum]->getItemName());
	}
}

void itemManager::changeArmorNumber(string keyName, int number)
{
	_iterInventory = _arrArmorInventory.find(keyName);
	if (_iterInventory != _arrArmorInventory.end())
	{
		_arrArmorInventory[keyName].second += number;
	}
	else if (number > 0)
	{
		for (int i = 0; i < _vItem.size(); ++i)
		{
			if (_vItem[i]->getItemName() == keyName)
			{
				setArmorInventory(i, number);
				break;
			}
		}
	}
	if (_arrArmorInventory[keyName].second <= 0)
	{
		_arrArmorInventory.erase(keyName);
	}
}

int itemManager::getItemVNum(int num)
{
	_iterInventory = _arrItemInventory.begin();
	for (int i = 0; i < num; ++i)
	{
		_iterInventory++;
	}
	return _iterInventory->second.first;
}

int itemManager::getItemCount(int num)
{
	_iterInventory = _arrItemInventory.begin();
	for (int i = 0; i < num; ++i)
	{
		_iterInventory++;
	}
	return _iterInventory->second.second;
}

int itemManager::getItemCountByVector(int vNum)
{
	_iterInventory = _arrItemInventory.find(_vItem[vNum]->getItemName());
	if (_iterInventory != _arrItemInventory.end())
	{
		return _arrItemInventory[_vItem[vNum]->getItemName()].second;
	}
	else
	{
		return 0;
	}
}

int itemManager::getWeaponVNum(int num)
{
	_iterInventory = _arrWeaponInventory.begin();
	for (int i = 0; i < num; ++i)
	{
		_iterInventory++;
	}
	return _iterInventory->second.first;
}

int itemManager::getWeaponCount(int num)
{
	_iterInventory = _arrWeaponInventory.begin();
	for (int i = 0; i < num; ++i)
	{
		_iterInventory++;
	}
	return _iterInventory->second.second;
}

int itemManager::getWeaponCountByVector(int vNum)
{
	_iterInventory = _arrWeaponInventory.find(_vItem[vNum]->getItemName());
	if (_iterInventory != _arrWeaponInventory.end())
	{
		return _arrWeaponInventory[_vItem[vNum]->getItemName()].second;
	}
	else
	{
		return 0;
	}
}

int itemManager::getArmorVNum(int num)	
{
	_iterInventory = _arrArmorInventory.begin();
	for (int i = 0; i < num; ++i)
	{
		_iterInventory++;
	}
	return _iterInventory->second.first;
}

int itemManager::getArmorCount(int num)	
{
	_iterInventory = _arrArmorInventory.begin();
	for (int i = 0; i < num; ++i)
	{
		_iterInventory++;
	}
	return _iterInventory->second.second;
}

int itemManager::getArmorCountByVector(int vNum)
{
	_iterInventory = _arrWeaponInventory.find(_vItem[vNum]->getItemName());
	if (_iterInventory != _arrWeaponInventory.end())
	{
		return _arrWeaponInventory[_vItem[vNum]->getItemName()].second;
	}
	else
	{
		return 0;
	}
}

void itemManager::useItemInMenu(int partyIdx, int invenNum)
{
	bool usedItem;
	usedItem = false;
	for (int i = 0; i < 4; ++i)
	{
		if (_vItem[getItemVNum(invenNum)]->getItmeKind() != ITEM_EXPENDABLE) break;
		if (_pm->getVPlayer()[i]->getPartyIdx() == partyIdx)
		{
			if (((expendablesItem*)_vItem[getItemVNum(invenNum)])->getIsReviveItem() == true)
			{
				if (((expendablesItem*)_vItem[getItemVNum(invenNum)])->getAmountHpRestored() > 0)
				{
					if (((expendablesItem*)_vItem[getItemVNum(invenNum)])->getIsPercentHP() == true)
					{
						_pm->getVPlayer()[i]->setCurHP((float)_pm->getVPlayer()[i]->getCurHP() + (float)_pm->getVPlayer()[i]->getMaxHP() * (float)((expendablesItem*)_vItem[getItemVNum(invenNum)])->getAmountHpRestored() / 100);
						if (_pm->getVPlayer()[i]->getCurHP() > _pm->getVPlayer()[i]->getMaxHP()) _pm->getVPlayer()[i]->setCurHP(_pm->getVPlayer()[i]->getMaxHP());
					}
					else
					{
						_pm->getVPlayer()[i]->setCurHP(_pm->getVPlayer()[i]->getCurHP() + ((expendablesItem*)_vItem[getItemVNum(invenNum)])->getAmountHpRestored());
						if (_pm->getVPlayer()[i]->getCurHP() > _pm->getVPlayer()[i]->getMaxHP()) _pm->getVPlayer()[i]->setCurHP(_pm->getVPlayer()[i]->getMaxHP());
					}
					usedItem = true;
				}
				if (((expendablesItem*)_vItem[getItemVNum(invenNum)])->getAmountMpRestored() > 0)
				{
					if (((expendablesItem*)_vItem[getItemVNum(invenNum)])->getIsPercentMP() == true)
					{
						_pm->getVPlayer()[i]->setCurMP((float)_pm->getVPlayer()[i]->getCurMP() + (float)_pm->getVPlayer()[i]->getMaxMP() * (float)((expendablesItem*)_vItem[getItemVNum(invenNum)])->getAmountMpRestored() / 100);
						if (_pm->getVPlayer()[i]->getCurMP() > _pm->getVPlayer()[i]->getMaxMP()) _pm->getVPlayer()[i]->setCurMP(_pm->getVPlayer()[i]->getMaxMP());
					}
					else
					{
						_pm->getVPlayer()[i]->setCurMP(_pm->getVPlayer()[i]->getCurMP() + ((expendablesItem*)_vItem[getItemVNum(invenNum)])->getAmountMpRestored());
						if (_pm->getVPlayer()[i]->getCurMP() > _pm->getVPlayer()[i]->getMaxMP()) _pm->getVPlayer()[i]->setCurMP(_pm->getVPlayer()[i]->getMaxMP());
					}
					usedItem = true;
				}
			}
			else if (_pm->getVPlayer()[i]->getCurHP() > 0)
			{
				if (((expendablesItem*)_vItem[getItemVNum(invenNum)])->getAmountHpRestored() > 0)
				{
					if (((expendablesItem*)_vItem[getItemVNum(invenNum)])->getIsPercentHP() == true)
					{
						_pm->getVPlayer()[i]->setCurHP((float)_pm->getVPlayer()[i]->getCurHP() + (float)_pm->getVPlayer()[i]->getMaxHP() * (float)((expendablesItem*)_vItem[getItemVNum(invenNum)])->getAmountHpRestored() / 100);
						if (_pm->getVPlayer()[i]->getCurHP() > _pm->getVPlayer()[i]->getMaxHP()) _pm->getVPlayer()[i]->setCurHP(_pm->getVPlayer()[i]->getMaxHP());
					}
					else
					{
						_pm->getVPlayer()[i]->setCurHP(_pm->getVPlayer()[i]->getCurHP() + ((expendablesItem*)_vItem[getItemVNum(invenNum)])->getAmountHpRestored());
						if (_pm->getVPlayer()[i]->getCurHP() > _pm->getVPlayer()[i]->getMaxHP()) _pm->getVPlayer()[i]->setCurHP(_pm->getVPlayer()[i]->getMaxHP());
					}
					usedItem = true;
				}
				if (((expendablesItem*)_vItem[getItemVNum(invenNum)])->getAmountMpRestored() > 0)
				{
					if (((expendablesItem*)_vItem[getItemVNum(invenNum)])->getIsPercentMP() == true)
					{
						_pm->getVPlayer()[i]->setCurMP((float)_pm->getVPlayer()[i]->getCurMP() + (float)_pm->getVPlayer()[i]->getMaxMP() * (float)((expendablesItem*)_vItem[getItemVNum(invenNum)])->getAmountMpRestored() / 100);
						if (_pm->getVPlayer()[i]->getCurMP() > _pm->getVPlayer()[i]->getMaxMP()) _pm->getVPlayer()[i]->setCurMP(_pm->getVPlayer()[i]->getMaxMP());
					}
					else
					{
						_pm->getVPlayer()[i]->setCurMP(_pm->getVPlayer()[i]->getCurMP() + ((expendablesItem*)_vItem[getItemVNum(invenNum)])->getAmountMpRestored());
						if (_pm->getVPlayer()[i]->getCurMP() > _pm->getVPlayer()[i]->getMaxMP()) _pm->getVPlayer()[i]->setCurMP(_pm->getVPlayer()[i]->getMaxMP());
					}
					usedItem = true;
				}
			}
		}
		else if (((expendablesItem*)_vItem[getItemVNum(invenNum)])->getIsPartyItem() == true)
		{
			if (((expendablesItem*)_vItem[getItemVNum(invenNum)])->getIsReviveItem() == true)
			{
				if (((expendablesItem*)_vItem[getItemVNum(invenNum)])->getAmountHpRestored() > 0)
				{
					if (((expendablesItem*)_vItem[getItemVNum(invenNum)])->getIsPercentHP() == true)
					{
						_pm->getVPlayer()[i]->setCurHP((float)_pm->getVPlayer()[i]->getCurHP() + (float)_pm->getVPlayer()[i]->getMaxHP() * (float)((expendablesItem*)_vItem[getItemVNum(invenNum)])->getAmountHpRestored() / 100);
						if (_pm->getVPlayer()[i]->getCurHP() > _pm->getVPlayer()[i]->getMaxHP()) _pm->getVPlayer()[i]->setCurHP(_pm->getVPlayer()[i]->getMaxHP());
					}
					else
					{
						_pm->getVPlayer()[i]->setCurHP(_pm->getVPlayer()[i]->getCurHP() + ((expendablesItem*)_vItem[getItemVNum(invenNum)])->getAmountHpRestored());
						if (_pm->getVPlayer()[i]->getCurHP() > _pm->getVPlayer()[i]->getMaxHP()) _pm->getVPlayer()[i]->setCurHP(_pm->getVPlayer()[i]->getMaxHP());
					}
					usedItem = true;
				}
				if (((expendablesItem*)_vItem[getItemVNum(invenNum)])->getAmountMpRestored() > 0)
				{
					if (((expendablesItem*)_vItem[getItemVNum(invenNum)])->getIsPercentMP() == true)
					{
						_pm->getVPlayer()[i]->setCurMP((float)_pm->getVPlayer()[i]->getCurMP() + (float)_pm->getVPlayer()[i]->getMaxMP() * (float)((expendablesItem*)_vItem[getItemVNum(invenNum)])->getAmountMpRestored() / 100);
						if (_pm->getVPlayer()[i]->getCurMP() > _pm->getVPlayer()[i]->getMaxMP()) _pm->getVPlayer()[i]->setCurMP(_pm->getVPlayer()[i]->getMaxMP());
					}
					else
					{
						_pm->getVPlayer()[i]->setCurMP(_pm->getVPlayer()[i]->getCurMP() + ((expendablesItem*)_vItem[getItemVNum(invenNum)])->getAmountMpRestored());
						if (_pm->getVPlayer()[i]->getCurMP() > _pm->getVPlayer()[i]->getMaxMP()) _pm->getVPlayer()[i]->setCurMP(_pm->getVPlayer()[i]->getMaxMP());
					}
					usedItem = true;
				}
			}
			else if (_pm->getVPlayer()[i]->getCurHP() > 0)
			{
				if (((expendablesItem*)_vItem[getItemVNum(invenNum)])->getAmountHpRestored() > 0)
				{
					if (((expendablesItem*)_vItem[getItemVNum(invenNum)])->getIsPercentHP() == true)
					{
						_pm->getVPlayer()[i]->setCurHP((float)_pm->getVPlayer()[i]->getCurHP() + (float)_pm->getVPlayer()[i]->getMaxHP() * (float)((expendablesItem*)_vItem[getItemVNum(invenNum)])->getAmountHpRestored() / 100);
						if (_pm->getVPlayer()[i]->getCurHP() > _pm->getVPlayer()[i]->getMaxHP()) _pm->getVPlayer()[i]->setCurHP(_pm->getVPlayer()[i]->getMaxHP());
					}
					else
					{
						_pm->getVPlayer()[i]->setCurHP(_pm->getVPlayer()[i]->getCurHP() + ((expendablesItem*)_vItem[getItemVNum(invenNum)])->getAmountHpRestored());
						if (_pm->getVPlayer()[i]->getCurHP() > _pm->getVPlayer()[i]->getMaxHP()) _pm->getVPlayer()[i]->setCurHP(_pm->getVPlayer()[i]->getMaxHP());
					}
					usedItem = true;
				}
				if (((expendablesItem*)_vItem[getItemVNum(invenNum)])->getAmountMpRestored() > 0)
				{
					if (((expendablesItem*)_vItem[getItemVNum(invenNum)])->getIsPercentMP() == true)
					{
						_pm->getVPlayer()[i]->setCurMP((float)_pm->getVPlayer()[i]->getCurMP() + (float)_pm->getVPlayer()[i]->getMaxMP() * (float)((expendablesItem*)_vItem[getItemVNum(invenNum)])->getAmountMpRestored() / 100);
						if (_pm->getVPlayer()[i]->getCurMP() > _pm->getVPlayer()[i]->getMaxMP()) _pm->getVPlayer()[i]->setCurMP(_pm->getVPlayer()[i]->getMaxMP());
					}
					else
					{
						_pm->getVPlayer()[i]->setCurMP(_pm->getVPlayer()[i]->getCurMP() + ((expendablesItem*)_vItem[getItemVNum(invenNum)])->getAmountMpRestored());
						if (_pm->getVPlayer()[i]->getCurMP() > _pm->getVPlayer()[i]->getMaxMP()) _pm->getVPlayer()[i]->setCurMP(_pm->getVPlayer()[i]->getMaxMP());
					}
					usedItem = true;
				}
			}
		}
	}
	if (usedItem == true)
	{
		changeItemNumber(getItemVNum(invenNum), -1);
	}
}

bool itemManager::useItemInBattle(int itemTarget, int invenNum)
{
	bool usedItem;
	usedItem = false;
	if (((expendablesItem*)_vItem[getItemVNum(invenNum)])->getIsInBattle() == true)
	{
		for (int i = 0; i < 4; ++i)
		{
			if (_vItem[getItemVNum(invenNum)]->getItmeKind() != ITEM_EXPENDABLE) break;
			if (i == itemTarget)
			{
				if (((expendablesItem*)_vItem[getItemVNum(invenNum)])->getIsReviveItem() == true)
				{
					if (((expendablesItem*)_vItem[getItemVNum(invenNum)])->getAmountHpRestored() > 0)
					{
						if (((expendablesItem*)_vItem[getItemVNum(invenNum)])->getIsPercentHP() == true)
						{
							_battlePlayer[i]->setCurHP((float)_battlePlayer[i]->getCurHP() + (float)_battlePlayer[i]->getMaxHP() * (float)((expendablesItem*)_vItem[getItemVNum(invenNum)])->getAmountHpRestored() / 100);
							if (_battlePlayer[i]->getCurHP() > _battlePlayer[i]->getMaxHP()) _battlePlayer[i]->setCurHP(_battlePlayer[i]->getMaxHP());
						}
						else
						{
							_battlePlayer[i]->setCurHP(_battlePlayer[i]->getCurHP() + ((expendablesItem*)_vItem[getItemVNum(invenNum)])->getAmountHpRestored());
							if (_battlePlayer[i]->getCurHP() > _battlePlayer[i]->getMaxHP()) _battlePlayer[i]->setCurHP(_battlePlayer[i]->getMaxHP());
						}
						usedItem = true;
					}
					if (((expendablesItem*)_vItem[getItemVNum(invenNum)])->getAmountMpRestored() > 0)
					{
						if (((expendablesItem*)_vItem[getItemVNum(invenNum)])->getIsPercentMP() == true)
						{
							_battlePlayer[i]->setCurMP((float)_battlePlayer[i]->getCurMP() + (float)_battlePlayer[i]->getMaxMP() * (float)((expendablesItem*)_vItem[getItemVNum(invenNum)])->getAmountMpRestored() / 100);
							if (_battlePlayer[i]->getCurMP() > _battlePlayer[i]->getMaxMP()) _battlePlayer[i]->setCurMP(_battlePlayer[i]->getMaxMP());
						}
						else
						{
							_battlePlayer[i]->setCurMP(_battlePlayer[i]->getCurMP() + ((expendablesItem*)_vItem[getItemVNum(invenNum)])->getAmountMpRestored());
							if (_battlePlayer[i]->getCurMP() > _battlePlayer[i]->getMaxMP()) _battlePlayer[i]->setCurMP(_battlePlayer[i]->getMaxMP());
						}
						usedItem = true;
					}
				}
				else if (_pm->getVPlayer()[i]->getCurHP() > 0)
				{
					if (((expendablesItem*)_vItem[getItemVNum(invenNum)])->getAmountHpRestored() > 0)
					{
						if (((expendablesItem*)_vItem[getItemVNum(invenNum)])->getIsPercentHP() == true)
						{
							_battlePlayer[i]->setCurHP((float)_battlePlayer[i]->getCurHP() + (float)_battlePlayer[i]->getMaxHP() * (float)((expendablesItem*)_vItem[getItemVNum(invenNum)])->getAmountHpRestored() / 100);
							if (_battlePlayer[i]->getCurHP() > _battlePlayer[i]->getMaxHP()) _battlePlayer[i]->setCurHP(_battlePlayer[i]->getMaxHP());
						}
						else
						{
							_battlePlayer[i]->setCurHP(_battlePlayer[i]->getCurHP() + ((expendablesItem*)_vItem[getItemVNum(invenNum)])->getAmountHpRestored());
							if (_battlePlayer[i]->getCurHP() > _battlePlayer[i]->getMaxHP()) _battlePlayer[i]->setCurHP(_battlePlayer[i]->getMaxHP());
						}
						usedItem = true;
					}
					if (((expendablesItem*)_vItem[getItemVNum(invenNum)])->getAmountMpRestored() > 0)
					{
						if (((expendablesItem*)_vItem[getItemVNum(invenNum)])->getIsPercentMP() == true)
						{
							_battlePlayer[i]->setCurMP((float)_battlePlayer[i]->getCurMP() + (float)_battlePlayer[i]->getMaxMP() * (float)((expendablesItem*)_vItem[getItemVNum(invenNum)])->getAmountMpRestored() / 100);
							if (_battlePlayer[i]->getCurMP() > _battlePlayer[i]->getMaxMP()) _battlePlayer[i]->setCurMP(_battlePlayer[i]->getMaxMP());
						}
						else
						{
							_battlePlayer[i]->setCurMP(_battlePlayer[i]->getCurMP() + ((expendablesItem*)_vItem[getItemVNum(invenNum)])->getAmountMpRestored());
							if (_battlePlayer[i]->getCurMP() > _battlePlayer[i]->getMaxMP()) _battlePlayer[i]->setCurMP(_battlePlayer[i]->getMaxMP());
						}
						usedItem = true;
					}
				}
			}
			else if (((expendablesItem*)_vItem[getItemVNum(invenNum)])->getIsPartyItem() == true)
			{
				if (((expendablesItem*)_vItem[getItemVNum(invenNum)])->getIsReviveItem() == true)
				{
					if (((expendablesItem*)_vItem[getItemVNum(invenNum)])->getAmountHpRestored() > 0)
					{
						if (((expendablesItem*)_vItem[getItemVNum(invenNum)])->getIsPercentHP() == true)
						{
							_battlePlayer[i]->setCurHP((float)_battlePlayer[i]->getCurHP() + (float)_battlePlayer[i]->getMaxHP() * (float)((expendablesItem*)_vItem[getItemVNum(invenNum)])->getAmountHpRestored() / 100);
							if (_battlePlayer[i]->getCurHP() > _battlePlayer[i]->getMaxHP()) _battlePlayer[i]->setCurHP(_battlePlayer[i]->getMaxHP());
						}
						else
						{
							_battlePlayer[i]->setCurHP(_battlePlayer[i]->getCurHP() + ((expendablesItem*)_vItem[getItemVNum(invenNum)])->getAmountHpRestored());
							if (_battlePlayer[i]->getCurHP() > _battlePlayer[i]->getMaxHP()) _battlePlayer[i]->setCurHP(_battlePlayer[i]->getMaxHP());
						}
						usedItem = true;
					}
					if (((expendablesItem*)_vItem[getItemVNum(invenNum)])->getAmountMpRestored() > 0)
					{
						if (((expendablesItem*)_vItem[getItemVNum(invenNum)])->getIsPercentMP() == true)
						{
							_battlePlayer[i]->setCurMP((float)_battlePlayer[i]->getCurMP() + (float)_battlePlayer[i]->getMaxMP() * (float)((expendablesItem*)_vItem[getItemVNum(invenNum)])->getAmountMpRestored() / 100);
							if (_battlePlayer[i]->getCurMP() > _battlePlayer[i]->getMaxMP()) _battlePlayer[i]->setCurMP(_battlePlayer[i]->getMaxMP());
						}
						else
						{
							_battlePlayer[i]->setCurMP(_battlePlayer[i]->getCurMP() + ((expendablesItem*)_vItem[getItemVNum(invenNum)])->getAmountMpRestored());
							if (_battlePlayer[i]->getCurMP() > _battlePlayer[i]->getMaxMP()) _battlePlayer[i]->setCurMP(_battlePlayer[i]->getMaxMP());
						}
						usedItem = true;
					}
				}
				else if (_pm->getVPlayer()[i]->getCurHP() > 0)
				{
					if (((expendablesItem*)_vItem[getItemVNum(invenNum)])->getAmountHpRestored() > 0)
					{
						if (((expendablesItem*)_vItem[getItemVNum(invenNum)])->getIsPercentHP() == true)
						{
							_battlePlayer[i]->setCurHP((float)_battlePlayer[i]->getCurHP() + (float)_battlePlayer[i]->getMaxHP() * (float)((expendablesItem*)_vItem[getItemVNum(invenNum)])->getAmountHpRestored() / 100);
							if (_battlePlayer[i]->getCurHP() > _battlePlayer[i]->getMaxHP()) _battlePlayer[i]->setCurHP(_battlePlayer[i]->getMaxHP());
						}
						else
						{
							_battlePlayer[i]->setCurHP(_battlePlayer[i]->getCurHP() + ((expendablesItem*)_vItem[getItemVNum(invenNum)])->getAmountHpRestored());
							if (_battlePlayer[i]->getCurHP() > _battlePlayer[i]->getMaxHP()) _battlePlayer[i]->setCurHP(_battlePlayer[i]->getMaxHP());
						}
						usedItem = true;
					}
					if (((expendablesItem*)_vItem[getItemVNum(invenNum)])->getAmountMpRestored() > 0)
					{
						if (((expendablesItem*)_vItem[getItemVNum(invenNum)])->getIsPercentMP() == true)
						{
							_battlePlayer[i]->setCurMP((float)_battlePlayer[i]->getCurMP() + (float)_battlePlayer[i]->getMaxMP() * (float)((expendablesItem*)_vItem[getItemVNum(invenNum)])->getAmountMpRestored() / 100);
							if (_battlePlayer[i]->getCurMP() > _battlePlayer[i]->getMaxMP()) _battlePlayer[i]->setCurMP(_battlePlayer[i]->getMaxMP());
						}
						else
						{
							_battlePlayer[i]->setCurMP(_battlePlayer[i]->getCurMP() + ((expendablesItem*)_vItem[getItemVNum(invenNum)])->getAmountMpRestored());
							if (_battlePlayer[i]->getCurMP() > _battlePlayer[i]->getMaxMP()) _battlePlayer[i]->setCurMP(_battlePlayer[i]->getMaxMP());
						}
						usedItem = true;
					}
				}
			}
		}
	}
	if (usedItem == true)
	{
		changeItemNumber(getItemVNum(invenNum), -1);
		return true;
	}
	else
	{
		return false;
	}
}

itemKind itemManager::getItemKind(string keyName)
{
	for (int i = 0; i < _vItem.size(); ++i)
	{
		if (_vItem[i]->getItemName() == keyName)
		{
			return _vItem[i]->getItmeKind();
		}
	}
}