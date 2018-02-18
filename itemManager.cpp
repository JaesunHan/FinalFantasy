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
	
	expendablesItem* ether = new expendablesItem;
	ether->init(ITEM_EXPENDABLE, "���׸�", "�÷��̾� ���� 150 ȸ��", 2, 0, 150, false, false, false, false);
	_vItem.push_back(ether);

	expendablesItem* driedMeat = new expendablesItem;
	driedMeat->init(ITEM_EXPENDABLE, "����", "�÷��̾� ü�� 150 ȸ��", 2, 150, 0, false, false, false, false);
	_vItem.push_back(driedMeat);

	expendablesItem* elixir = new expendablesItem;
	elixir->init(ITEM_EXPENDABLE, "������", "�÷��̾� ü�� ���� 100% ȸ��", 2, 0, 0, false, false, true, true);
	_vItem.push_back(elixir);

	expendablesItem* megaElixir = new expendablesItem;
	megaElixir->init(ITEM_EXPENDABLE, "�ް�������", "��ü �÷��̾� ü�� ���� 100% ȸ��", 2, 0, 0, false, false, true, true);
	_vItem.push_back(megaElixir);

	expendablesItem* phoenixDown = new expendablesItem;
	phoenixDown->init(ITEM_EXPENDABLE, "�Ǵн�����", "�ൿ�Ҵ��� �� �÷��̾� ȸ��", 500, 1, 0, true, false, false, false);
	_vItem.push_back(phoenixDown);

	expendablesItem* potion = new expendablesItem;
	potion->init(ITEM_EXPENDABLE, "����", "�÷��̾� ü�� 250 ȸ��", 300, 250, 0, false, false, false, false);
	_vItem.push_back(potion);

	expendablesItem* tonic = new expendablesItem;
	tonic->init(ITEM_EXPENDABLE, "���", "�÷��̾� ���� 50 ȸ��", 200, 0, 50, false, false, false, false);
	_vItem.push_back(tonic);

	expendablesItem* sleepingBag = new expendablesItem;
	sleepingBag->init(ITEM_EXPENDABLE, "ħ��", "�÷��̾� ü�� ���� 100% ȸ�� ( ����ʿ����� ��� ���� )", 500, 0, 0, false, true, true, true);
	_vItem.push_back(sleepingBag);

	expendablesItem* tent = new expendablesItem;
	tent->init(ITEM_EXPENDABLE, "��Ʈ", "��ü �÷��̾� ü�� ���� 100% ȸ�� ( ����ʿ����� ��� ���� )", 1200, 0, 0, false, true, true, true);
	_vItem.push_back(tent);

	expendablesItem* X_ether = new expendablesItem;
	X_ether->init(ITEM_EXPENDABLE, "X-���׸�", "�÷��̾� ���� 100% ȸ��", 5000, 0, 0, false, false, false, true);
	_vItem.push_back(X_ether);

	expendablesItem* X_potion = new expendablesItem;
	X_potion->init(ITEM_EXPENDABLE, "X-����", "�÷��̾� ü�� 100% ȸ��", 5000, 0, 0, false, false, true, false);
	_vItem.push_back(X_potion);

	//=======================================================================================

	//======================================== ���� =========================================

	weaponItem* temp = new weaponItem;
	temp->init(ITEM_WEAPON, "Mithril Knife", "...", 300, 30, 180);
	_vItem.push_back(temp);
	temp->init(ITEM_WEAPON, "Dirk", "...", 150, 26, 180);
	_vItem.push_back(temp);
	temp->init(ITEM_WEAPON, "Thief Knife", "...", 2, 88, 180);
	_vItem.push_back(temp);
	temp->init(ITEM_WEAPON, "Illumina", "...", 2, 255, 255);
	_vItem.push_back(temp);
	temp->init(ITEM_WEAPON, "Crystal", "...", 15000, 167, 150);
	_vItem.push_back(temp);
	temp->init(ITEM_WEAPON, "Striker", "...", 2, 190, 180);
	_vItem.push_back(temp);
	temp->init(ITEM_WEAPON, "Full Moon", "...", 2500, 95, 230);
	_vItem.push_back(temp);
	temp->init(ITEM_WEAPON, "Wing Edge", "...", 2, 198, 230);
	_vItem.push_back(temp);
	temp->init(ITEM_WEAPON, "Morning Start", "...", 5000, 109, 150);
	_vItem.push_back(temp);
	temp->init(ITEM_WEAPON, "Shuriken", "...", 30, 86, 230);
	_vItem.push_back(temp);

	//=======================================================================================

	//======================================== ���� =========================================

	expendablesItem* crystalMail = new expendablesItem;
	crystalMail->init(ITEM_ARMOR, "ũ����Ż ����", "_a_Def + 72, _m_Def + 49", 17000, 0, 0, false, false, false, false);
	_vItem.push_back(crystalMail);

	expendablesItem* diamondArmor = new expendablesItem;
	diamondArmor->init(ITEM_ARMOR, "���̾Ƹ�� ����", "_a_Def + 56, _m_Def + 38", 12000, 0, 0, false, false, false, false);
	_vItem.push_back(diamondArmor);

	expendablesItem* goldHelmet = new expendablesItem;
	goldHelmet->init(ITEM_ARMOR, "Ȳ�� ����", "_a_Def + 40, _m_Def + 27", 8000, 0, 0, false, false, false, false);
	_vItem.push_back(goldHelmet);

	expendablesItem* mithrilHelmet = new expendablesItem;
	X_potion->init(ITEM_ARMOR, "X-����", "�÷��̾� ü�� 100% ȸ��", 5000, 0, 0, false, false, false, false);
	_vItem.push_back(X_potion);

	expendablesItem* leatherArmor = new expendablesItem;
	X_potion->init(ITEM_ARMOR, "���� ����", "�÷��̾� ü�� 100% ȸ��", 5000, 0, 0, false, false, false, false);
	_vItem.push_back(X_potion);

	//=======================================================================================

	//======================================== ���� =========================================

	expendablesItem* X_potion = new expendablesItem;
	X_potion->init(ITEM_EXPENDABLE, "X-����", "�÷��̾� ü�� 100% ȸ��", 5000, 0, 0, false, false, true, false);
	_vItem.push_back(X_potion);

	expendablesItem* X_potion = new expendablesItem;
	X_potion->init(ITEM_EXPENDABLE, "X-����", "�÷��̾� ü�� 100% ȸ��", 5000, 0, 0, false, false, true, false);
	_vItem.push_back(X_potion);

	expendablesItem* X_potion = new expendablesItem;
	X_potion->init(ITEM_EXPENDABLE, "X-����", "�÷��̾� ü�� 100% ȸ��", 5000, 0, 0, false, false, true, false);
	_vItem.push_back(X_potion);

	expendablesItem* X_potion = new expendablesItem;
	X_potion->init(ITEM_EXPENDABLE, "X-����", "�÷��̾� ü�� 100% ȸ��", 5000, 0, 0, false, false, true, false);
	_vItem.push_back(X_potion);

	expendablesItem* X_potion = new expendablesItem;
	X_potion->init(ITEM_EXPENDABLE, "X-����", "�÷��̾� ü�� 100% ȸ��", 5000, 0, 0, false, false, true, false);
	_vItem.push_back(X_potion);

	//=======================================================================================

	//======================================== ���� =========================================

	expendablesItem* X_potion = new expendablesItem;
	X_potion->init(ITEM_EXPENDABLE, "X-����", "�÷��̾� ü�� 100% ȸ��", 5000, 0, 0, false, false, true, false);
	_vItem.push_back(X_potion);

	expendablesItem* X_potion = new expendablesItem;
	X_potion->init(ITEM_EXPENDABLE, "X-����", "�÷��̾� ü�� 100% ȸ��", 5000, 0, 0, false, false, true, false);
	_vItem.push_back(X_potion);

	expendablesItem* X_potion = new expendablesItem;
	X_potion->init(ITEM_EXPENDABLE, "X-����", "�÷��̾� ü�� 100% ȸ��", 5000, 0, 0, false, false, true, false);
	_vItem.push_back(X_potion);

	expendablesItem* X_potion = new expendablesItem;
	X_potion->init(ITEM_EXPENDABLE, "X-����", "�÷��̾� ü�� 100% ȸ��", 5000, 0, 0, false, false, true, false);
	_vItem.push_back(X_potion);

	expendablesItem* X_potion = new expendablesItem;
	X_potion->init(ITEM_EXPENDABLE, "X-����", "�÷��̾� ü�� 100% ȸ��", 5000, 0, 0, false, false, true, false);
	_vItem.push_back(X_potion);

	//=======================================================================================

	return S_OK;
}