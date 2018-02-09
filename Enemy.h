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

	unsigned int _x, _y;

	bool _enemyTurn;						//���ʹ̵� ���̴�?

	EnemyState _state;						//���ʹ̵� ���°�
	
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

	//=========================== ������ / ������ =============================

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

