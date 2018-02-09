#pragma once
#include "gameNode.h"

enum EnemyState
{
	ENEMY_IDEL,
	ENEMY_HIT,
	ENEMY_SPELL,
	ENEMY_DIE
};

class battleTina;
class battleShadow;
class battleLocke;
class battleCeles;

class Enemy : public gameNode
{
protected:
	unsigned int _Lv;						//레벨
	unsigned int _maxEXP;					//경험치
	unsigned int _gold;						//돈

	unsigned int _curHP, _maxHP;			//현재 체력, 최대 체력
	unsigned int _curMP, _maxMP;			//현재 마력, 최대 마력
	
	unsigned int _attack;					//기본 데미지
	unsigned int _magic;					//마법 데미지
	
	unsigned int _m_Def;					//마법 방어력
	unsigned int _a_Def;					//물리 방어력
	
	unsigned int _speed;					//공격 타이머

	unsigned int _evasion;					//회피율
	unsigned int _hitRate;					//명중률
	unsigned int _block;					//방어율

	unsigned int _x, _y;

	bool _enemyTurn;						//에너미들 턴이니?

	EnemyState _state;						//에너미들 상태값
	
	battleTina* _tina;
	battleShadow* _shadow;
	battleLocke* _locke;
	battleCeles* _celes;

public:
	Enemy();
	~Enemy();

	virtual HRESULT init(int x, int y);
	virtual void update();
	virtual void render();

	virtual void enemyAttack();

	void setBattleTinaMemoryAddressLink(battleTina* tina) { _tina = tina; }
	void setBattleShadowMemoryAddressLink(battleShadow* shadow) { _shadow = shadow; }
	void setBattleLockeMemoryAddressLink(battleLocke* locke) { _locke = locke; }
	void setBattleCelesMemoryAddressLink(battleCeles* celes) { _celes = celes; }

	//=========================== 접근자 / 설정자 =============================

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

	inline bool getEnemyTurn() { return _enemyTurn; }
	inline void setEnemyTurn(bool enemyTurn) { _enemyTurn = enemyTurn; }

	//========================================================================
};

