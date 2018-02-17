#pragma once
#include "gameNode.h"

#define MAXNAMESIZE 1024

enum itemKind
{
	ITEM_EXPENDABLE,
	ITEM_WEAPON,
	ITEM_SUB_WEAPON,
	ITEM_ARMOR,
	ITEM_HELMET,
	ITEM_ACCESSORY
};

class itemMother : public gameNode
{
protected:
	//================================== 공통 =======================================

	itemKind _itemKind;								//아이템 종류

	char _name[MAXNAMESIZE];						//아이템 이름
	char _description[MAXNAMESIZE];					//아이템 설명
	
	unsigned int _price;							//아이템 가격
	unsigned int _ability;							//아이템 효과

	//==============================================================================

	//================================ 장비 정보 ====================================

	unsigned int _vigor;							//== _strength
	unsigned int _attack;							//물리 공격력
	unsigned int _m_attack;							//마법 공격력
	unsigned int _speed;							//공격 타이머
	unsigned int _stamina;							//스테미나
	unsigned int _a_Def;							//물리 방어력
	unsigned int _m_Def;							//마법 방어력
	unsigned int _evasion;							//물리 회피율
	unsigned int _m_evasion;						//마법 회피율

	//==============================================================================

public:
	itemMother();
	~itemMother();

	virtual	HRESULT init(itemKind itemKind, char itemName[MAXNAMESIZE], char description[MAXNAMESIZE], int price, int ability);
	virtual void release();
	virtual void update();

	//void shopItemList();
	//void enemyItemList();
};

