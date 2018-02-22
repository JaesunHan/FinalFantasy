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
	//���� ��ȣ, ����	
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

	vector<itemMother*> getVItem() { return _vItem; }		//������ ���� ���� ����

	void saveInventory(char* fileName);						//�κ��丮�� Ű���� ���Ͽ� ����
	void loadInventory(char* fileName);						//Ű���� ���Ϸκ��� �κ��丮 �ε�
	int getItemVNum(int num);								//������ �κ��丮�� ����� ������ ��ȣ�� ������ ���� ������ ��ȣ ��ȯ
	int getItemCount(int num);								//������ �κ��丮�� ����� ������ ��ȣ�� ���� ��ȯ
	int getWeaponVNum(int num);								//���� �κ��丮�� ����� ������ ��ȣ�� ������ ���� ������ ��ȣ ��ȯ
	int getWeaponCount(int num);							//���� �κ��丮�� ����� ������ ��ȣ�� ���� ��ȯ
	int getArmorVNum(int num);								//�� �κ��丮�� ����� ������ ��ȣ�� ������ ���� ������ ��ȣ ��ȯ
	int getArmorCount(int num);								//�� �κ��丮�� ����� ������ ��ȣ�� ���� ��ȯ
	void setItemInventory(int vectorNum, int count);		//������ �κ��丮�� ���� ��ȣ�� �������� �ش� ������ŭ �־��ش�
	void setItemInventory(string keyName, int count);		//������ �κ��丮�� Ű�� �̸��� �������� �ش� ������ŭ �־��ش�
	void changeItemNumber(int vectorNum, int number);		//������ �κ��丮�� ���� ��ȣ�� �������� �ش� ������ŭ �����Ѵ�
	void changeItemNumber(string keyName, int number);		//������ �κ��丮�� Ű�� �̸��� �������� �ش� ������ŭ �����Ѵ�
	void setWeaponInventory(int vectorNum, int count);		//���� �κ��丮�� ���� ��ȣ�� �������� �ش� ������ŭ �־��ش�
	void setWeaponInventory(string keyName, int count);		//���� �κ��丮�� Ű�� �̸��� �������� �ش� ������ŭ �־��ش�
	void changeWeaponNumber(int vectorNum, int number);		//���� �κ��丮�� ���� ��ȣ�� �������� �ش� ������ŭ �����ش�
	void changeWeaponNumber(string keyName, int number);	//���� �κ��丮�� Ű�� �̸��� �������� �ش� ������ŭ �����ش�
	void setArmorInventory(int vectorNum, int count);		//�� �κ��丮�� ���� ��ȣ�� �������� �ش� ������ŭ �־��ش�
	void setArmorInventory(string keyName, int count);		//�� �κ��丮�� Ű�� �̸��� �������� �ش� ������ŭ �־��ش�
	void changeArmorNumber(int vectorNum, int number);		//�� �κ��丮�� ���� ��ȣ�� �������� �ش� ������ŭ �����ش�
	void changeArmorNumber(string keyName, int number);		//�� �κ��丮�� Ű�� �̸��� �������� �ش� ������ŭ �����ش�
	inline int getItemInventorySize() { return _arrItemInventory.size(); }		//������ �κ��丮 ������ ��ȯ
	inline int getWeaponInventorySize() { return _arrWeaponInventory.size(); }	//���� �κ��丮 ������ ��ȯ
	inline int getArmorInventorySize() { return _arrArmorInventory.size(); }	//�� �κ��丮 ������ ��ȯ
	inline unsigned int getMoney() { return _gil; }								//������ ��ȯ
	inline void setMoney(unsigned int money) { _gil = money; }					//������ ����

};

