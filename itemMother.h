#pragma once
#include "gameNode.h"

#define MAXNAMESIZE 1024

enum itemKind
{
	ITEM_EXPENDABLE,			//�Ҹ�ǰ
	ITEM_WEAPON,				//����
	ITEM_SUB_WEAPON,			//����
	ITEM_ARMOR,					//����
	ITEM_HELMET,				//����
	ITEM_ACCESSORY											//����
};

class itemMother : public gameNode
{
protected:
	//================================== ���� =======================================

	itemKind _itemKind;								//������ ����

	char _name[MAXNAMESIZE];						//������ �̸�
	char _description[MAXNAMESIZE];					//������ ����
	
	unsigned int _price;							//������ ����

	//==============================================================================

	//	//================================ ��� ���� ====================================
	//	
	//	unsigned int _vigor;							//== _strength
	//	unsigned int _attack;							//���� ���ݷ�
	//	unsigned int _m_attack;							//���� ���ݷ�
	//	unsigned int _speed;							//���� Ÿ�̸�
	//	unsigned int _stamina;							//���׹̳�
	//	unsigned int _a_Def;							//���� ����
	//	unsigned int _m_Def;							//���� ����
	//	unsigned int _evasion;							//���� ȸ����
	//	unsigned int _m_evasion;						//���� ȸ����
	//	
	//	//==============================================================================

public:
	itemMother();
	~itemMother();

	virtual	HRESULT init(itemKind itemKind, char itemName[MAXNAMESIZE], char description[MAXNAMESIZE], int price);
	virtual void release();
	virtual void update();

	inline char* getItemName() { return _name; }
	inline itemKind getItmeKind() { return _itemKind; }
	inline char* getItemDescription() {		return _description;	}
	inline int getPrice() { return _price; }
};

