#include "stdafx.h"
#include "itemManager.h"


itemManager::itemManager()
{
}


itemManager::~itemManager()
{
}

HRESULT itemManager::init()
{
	//======================================== �Ҹ�ǰ ========================================
	
	expendablesItem* expendables = new expendablesItem;

	expendables->init(ITEM_EXPENDABLE, "���׸�", "�÷��̾� ���� 150 ȸ��", 2, 0, 150, false, false, false, false);
	_vItem.push_back(expendables);

	expendables->init(ITEM_EXPENDABLE, "����", "�÷��̾� ü�� 150 ȸ��", 2, 150, 0, false, false, false, false);
	_vItem.push_back(expendables);

	expendables->init(ITEM_EXPENDABLE, "������", "�÷��̾� ü�� ���� 100% ȸ��", 2, 0, 0, false, false, true, true);
	_vItem.push_back(expendables);

	expendables->init(ITEM_EXPENDABLE, "�ް�������", "��ü �÷��̾� ü�� ���� 100% ȸ��", 2, 0, 0, false, false, true, true);
	_vItem.push_back(expendables);

	expendables->init(ITEM_EXPENDABLE, "�Ǵн�����", "�ൿ�Ҵ��� �� �÷��̾� ȸ��", 500, 1, 0, true, false, false, false);
	_vItem.push_back(expendables);

	expendables->init(ITEM_EXPENDABLE, "����", "�÷��̾� ü�� 250 ȸ��", 300, 250, 0, false, false, false, false);
	_vItem.push_back(expendables);

	expendables->init(ITEM_EXPENDABLE, "���", "�÷��̾� ���� 50 ȸ��", 200, 0, 50, false, false, false, false);
	_vItem.push_back(expendables);

	expendables->init(ITEM_EXPENDABLE, "ħ��", "�÷��̾� ü�� ���� 100% ȸ�� ( ����ʿ����� ��� ���� )", 500, 0, 0, false, true, true, true);
	_vItem.push_back(expendables);

	expendables->init(ITEM_EXPENDABLE, "��Ʈ", "��ü �÷��̾� ü�� ���� 100% ȸ�� ( ����ʿ����� ��� ���� )", 1200, 0, 0, false, true, true, true);
	_vItem.push_back(expendables);

	expendables->init(ITEM_EXPENDABLE, "X-���׸�", "�÷��̾� ���� 100% ȸ��", 5000, 0, 0, false, false, false, true);
	_vItem.push_back(expendables);

	expendables->init(ITEM_EXPENDABLE, "X-����", "�÷��̾� ü�� 100% ȸ��", 5000, 0, 0, false, false, true, false);
	_vItem.push_back(expendables);

	//=======================================================================================

	//======================================== ���� =========================================

	weaponItem* weapon = new weaponItem;

	//weapon->init(ITEM_WEAPON, "DefaultWeapon", "���ָ԰��ݹ����̴�", 0, 10, 100);
	//_vItem.push_back(weapon);

	weapon->init(ITEM_WEAPON, "Mithril Knife", "...", 300, 30, 180);
	_vItem.push_back(weapon);

	weapon->init(ITEM_WEAPON, "Dirk", "...", 150, 26, 180);
	_vItem.push_back(weapon);

	weapon->init(ITEM_WEAPON, "Thief Knife", "...", 2, 88, 180);
	_vItem.push_back(weapon);

	weapon->init(ITEM_WEAPON, "Illumina", "...", 2, 255, 255);
	_vItem.push_back(weapon);

	weapon->init(ITEM_WEAPON, "Crystal", "...", 15000, 167, 150);
	_vItem.push_back(weapon);

	weapon->init(ITEM_WEAPON, "Striker", "...", 2, 190, 180);
	_vItem.push_back(weapon);

	weapon->init(ITEM_WEAPON, "Full Moon", "...", 2500, 95, 230);
	_vItem.push_back(weapon);

	weapon->init(ITEM_WEAPON, "Wing Edge", "...", 2, 198, 230);
	_vItem.push_back(weapon);

	weapon->init(ITEM_WEAPON, "Morning Start", "...", 5000, 109, 150);
	_vItem.push_back(weapon);

	weapon->init(ITEM_WEAPON, "Shuriken", "...", 30, 86, 230);
	_vItem.push_back(weapon);

	//weapon->init(ITEM_WEAPON, "KKongChi", "������ ����. ����� �� ������.", 100000, 3)

	//=======================================================================================

	//======================================== ���� =========================================

	armorItem* armor = new armorItem;
	armor->init(ITEM_ARMOR, "ũ����Ż ����", "_a_Def + 72, _m_Def + 49", 17000, 72, 49);
	_vItem.push_back(armor);

	armor->init(ITEM_ARMOR, "���̾Ƹ�� ����", "_a_Def + 56, _m_Def + 38", 12000, 56, 38);
	_vItem.push_back(armor);

	armor->init(ITEM_ARMOR, "Ȳ�� ����", "_a_Def + 40, _m_Def + 27", 8000, 40, 27);
	_vItem.push_back(armor);

	armor->init(ITEM_ARMOR, "�̽��� ����", "_a_Def + 28, _m_Def + 19", 3500, 28, 19);
	_vItem.push_back(armor);

	armor->init(ITEM_ARMOR, "���� ����", "_a_Def + 18, _m_Def + 12", 500, 18, 12);
	_vItem.push_back(armor);

	//=======================================================================================

	//======================================== ���� =========================================

	armor->init(ITEM_HELMET, "ũ����Ż ����", "_a_Def + 29, _m_Def + 19", 10000, 29, 19);
	_vItem.push_back(armor);

	armor->init(ITEM_HELMET, "���̾Ƹ�� ����", "_a_Def + 27, _m_Def + 18", 7500, 27, 18);
	_vItem.push_back(armor);

	armor->init(ITEM_HELMET, "Ȳ�� ����", "_a_Def + 22, _m_Def + 15", 4000, 22, 15);
	_vItem.push_back(armor);

	armor->init(ITEM_HELMET, "�̽��� ����", "_a_Def + 20, _m_Def + 13", 2000, 20, 13);
	_vItem.push_back(armor);

	armor->init(ITEM_HELMET, "���� ����", "_a_Def + 14, _m_Def + 9", 250, 14, 9);
	_vItem.push_back(armor);
	
	//=======================================================================================
	
	//======================================== ���� =========================================
	
	armor->init(ITEM_SUB_WEAPON, "ũ����Ż ����", "_a_Def + 50, _m_Def + 34", 7000, 50, 34);
	_vItem.push_back(armor);

	armor->init(ITEM_SUB_WEAPON, "���̾Ƹ�� ����", "_a_Def + 40, _m_Def + 27", 3500, 40, 27);
	_vItem.push_back(armor);

	armor->init(ITEM_SUB_WEAPON, "Ȳ�� ����", "_a_Def + 34, _m_Def + 23", 2500, 34, 23);
	_vItem.push_back(armor);

	armor->init(ITEM_SUB_WEAPON, "�̽��� ����", "_a_Def + 27, _m_Def + 18", 1200, 27, 18);
	_vItem.push_back(armor);

	armor->init(ITEM_SUB_WEAPON, "��Ŭ�� ����", "_a_Def + 16, _m_Def + 10", 200, 16, 10);
	_vItem.push_back(armor);

	//=======================================================================================

	return S_OK;
}