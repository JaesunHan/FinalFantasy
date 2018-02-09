#pragma once
#include "gameNode.h"

class Enemy : public gameNode
{
protected:
	unsigned int _Lv;						//����
	unsigned int _maxEXP;					//����ġ
	unsigned int _gold;						//��

	unsigned int _curHP, _maxHP;			//���� ü��, �ִ� ü��
	unsigned int _curMP, _maxMP;			//���� ����, �ִ� ����
	
	unsigned int _attack;					//�⺻ ������
	unsigned int _magic;					//���� ������
	
	unsigned int _m_Def;					//���� ����
	unsigned int _a_Def;					//���� ����
	
	unsigned int _speed;					//���� Ÿ�̸�

	unsigned int _evasion;					//ȸ����
	unsigned int _hitRate;					//���߷�
	unsigned int _block;					//�����


public:
	Enemy();
	~Enemy();

	virtual void update();
	virtual void render();

	//================= ������ / ������ ===================

	inline int getLv() { return _Lv; }

	inline int getMaxEXP() { return _maxEXP; }
	inline void setMaxEXP(int maxEXP) { _maxEXP = maxEXP; }

	inline int getCurHP() { return _curHP; }
	inline void setCurHP(int curHP) { _curHP = curHP; }

	inline int getCurMP() { return _curMP; }
	inline void setCurMP(int curMP) { _curMP = curMP; }

	inline int getMagic() { return _magic; }

	inline int getSpeed() { return _speed; }

	inline int getADef() { return _a_Def; }

	inline int getMDef() { return _m_Def; }

	inline int getAttack() { return _attack; }

	inline int getEvasion() { return _evasion; }

	inline int getGold() { return _gold; }

	inline int getHitRate() { return _hitRate; }

	inline int getBlock() { return _block; }

	//====================================================
};

