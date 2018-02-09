#pragma once
#include "gameNode.h"



class Enemy : public gameNode
{
protected:
	unsigned int _Lv;						//레벨
	
	unsigned int _curEXP, _maxEXP;			//현재 경험치, 최대 경험치
	unsigned int _curHP, _maxHP;			//현재 체력, 최대 체력
	unsigned int _curMP, _maxMP;			//현재 마력, 최대 마력
	
	unsigned int _strength;					//물리 데미지
	unsigned int _attack;					//기본 공격력 + 무기의 공격력
	
	unsigned int _magic;					//마법 데미지
	
	unsigned int _m_Def;					//마법 방어력
	unsigned int _a_Def;					//물리 방어력
	
	unsigned int _speed;					//공격 타이머

	unsigned int _evasion;					//회피율
	unsigned int _hitRate;					//명중률
	unsigned int _block;					//방어율

	unsigned int _gold;						//돈

public:
	Enemy();
	~Enemy();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	//================= 접근자 / 설정자 ===================

	inline int getLv() { return _Lv; }

	inline int getCurEXP() { return _curEXP; }
	inline void setCurEXP(int curEXP) { _curEXP = curEXP; }

	inline int getMaxEXP() { return _maxEXP; }
	inline void setMaxEXP(int maxEXP) { _maxEXP = maxEXP; }

	inline int getCurHP() { return _curHP; }
	inline void setCurHP(int curHP) { _curHP = curHP; }

	inline int getMaxHP() { return _maxHP; }
	inline void setMaxHP(int maxHP) { _maxHP = maxHP; }

	inline int getCurMP() { return _curMP; }
	inline void setCurMP(int curMP) { _curMP = curMP; }

	inline int getMaxMP() { return _maxMP; }
	inline void setMaxMP(int maxMP) { _maxMP = maxMP; }

	inline int getStrength() { return _Lv; }

	inline int getLv() { return _strength; }

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

