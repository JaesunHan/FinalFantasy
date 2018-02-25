#pragma once
#include "gameNode.h"
#include <vector>
#include <map>
#include "expendablesItem.h"
#include "weaponItem.h"
#include "armorItem.h"

enum ITEMTARGET
{
	ITEM_TINA,
	ITEM_ROCKE,
	ITEM_CELES,
	ITEM_SHADOW,
	ITEM_PARTY
};

class battlePlayerMother;
class playerManager;

class itemManager : public gameNode
{
private:
	vector<itemMother*>							_vItem;
	//벡터 번호, 갯수	
	pair<int, int>								_element;		
	map<string, pair<int, int>>					_arrItemInventory;
	map<string, pair<int, int>>					_arrWeaponInventory;
	map<string, pair<int, int>>					_arrArmorInventory;
	map<string, pair<int, int>>::iterator		_iterInventory;
	unsigned int								_gil;

	battlePlayerMother*							_battlePlayer[5];
	playerManager*								_pm;
public:
	itemManager();
	~itemManager();

	HRESULT init();

	vector<itemMother*> getVItem() { return _vItem; }		//아이템 정보 저장 벡터

	void useItemInMenu(int partyIdx, int invenNum);			//메뉴에서 아이템 사용
	bool useItemInBattle(int itemTarget, int invenNum);		//배틀에서 아이템 사용

	void saveInventory(char* fileName);						//인벤토리를 키값의 파일에 저장
	void loadInventory(char* fileName);						//키값의 파일로부터 인벤토리 로드

	itemKind getItemKind(string keyName);					//키값으로 아이템 타잎 반환
	int getVNumByItemNum(int itemNumber);					//인덱스 번호로 아이템 벡터 번호 반환

	int getItemVNum(int num);								//아이템 인벤토리에 저장된 순서의 번호로 아이텐 정보 벡터의 번호 반환
	int getItemCount(int num);								//아이템 인벤토리에 저장된 순서의 번호의 갯수 반환
	int getItemCountByVector(int vNum);						//아이템 인벤토리에 저장된 순서의 번호를 벡터 번호로 검색해서 반환

	int getWeaponVNum(int num);								//무기 인벤토리에 저장된 순서의 번호로 아이텐 정보 벡터의 번호 반환
	int getWeaponCount(int num);							//무기 인벤토리에 저장된 순서의 번호의 갯수 반환
	int getWeaponCountByVector(int vNum);					//무기 인벤토리에 저장된 순서의 번호를 벡터 번호로 검색해서 반환

	int getArmorVNum(int num);								//방어구 인벤토리에 저장된 순서의 번호로 아이텐 정보 벡터의 번호 반환
	int getArmorCount(int num);								//방어구 인벤토리에 저장된 순서의 번호의 갯수 반환
	int getArmorCountByVector(int vNum);					//방어구 인벤토리에 저장된 순서의 번호를 벡터 번호로 검색해서 반환

	void setItemInventory(int vectorNum, int count);		//아이템 인벤토리에 벡터 번호의 아이템을 해당 갯수만큼 넣어준다
	void setItemInventory(string keyName, int count);		//아이템 인벤토리에 키값 이름의 아이템을 해당 갯수만큼 넣어준다
	void changeItemNumber(int vectorNum, int number);		//아이템 인벤토리에 벡터 번호의 아이템을 해당 갯수만큼 증감한다
	void changeItemNumber(string keyName, int number);		//아이템 인벤토리에 키값 이름의 아이템을 해당 갯수만큼 증감한다

	void setWeaponInventory(int vectorNum, int count);		//무기 인벤토리에 벡터 번호의 아이템을 해당 갯수만큼 넣어준다
	void setWeaponInventory(string keyName, int count);		//무기 인벤토리에 키값 이름의 아이템을 해당 갯수만큼 넣어준다
	void changeWeaponNumber(int vectorNum, int number);		//무기 인벤토리에 벡터 번호의 아이템을 해당 갯수만큼 증감준다
	void changeWeaponNumber(string keyName, int number);	//무기 인벤토리에 키값 이름의 아이템을 해당 갯수만큼 증감준다

	void setArmorInventory(int vectorNum, int count);		//방어구 인벤토리에 벡터 번호의 아이템을 해당 갯수만큼 넣어준다
	void setArmorInventory(string keyName, int count);		//방어구 인벤토리에 키값 이름의 아이템을 해당 갯수만큼 넣어준다
	void changeArmorNumber(int vectorNum, int number);		//방어구 인벤토리에 벡터 번호의 아이템을 해당 갯수만큼 증감준다
	void changeArmorNumber(string keyName, int number);		//방어구 인벤토리에 키값 이름의 아이템을 해당 갯수만큼 증감준다

	inline int getItemInventorySize() { return _arrItemInventory.size(); }		//아이템 인벤토리 사이즈 반환
	inline int getWeaponInventorySize() { return _arrWeaponInventory.size(); }	//무기 인벤토리 사이즈 반환
	inline int getArmorInventorySize() { return _arrArmorInventory.size(); }	//방어구 인벤토리 사이즈 반환

	inline unsigned int getMoney() { return _gil; }								//소지금 반환
	inline void setMoney(unsigned int money) { _gil = money; }					//소지금 설정

	void setBattleTinaMemoryAddressLink(battlePlayerMother* tina) { _battlePlayer[ITEM_TINA] = tina; }
	void setBattleRockeMemoryAddressLink(battlePlayerMother* rocke) { _battlePlayer[ITEM_ROCKE] = rocke; }
	void setBattleCelesMemoryAddressLink(battlePlayerMother* celes) { _battlePlayer[ITEM_CELES] = celes; }
	void setBattleShadowMemoryAddressLink(battlePlayerMother* shadow) { _battlePlayer[ITEM_SHADOW] = shadow; }
	void setPlayerManagerMemoryAddressLink(playerManager* pm) { _pm = pm; }
};

