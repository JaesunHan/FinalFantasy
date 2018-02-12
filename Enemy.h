#pragma once
#include "gameNode.h"
#include "effect.h"

//���ʹ� ���°�
enum EnemyState
{
	ENEMY_HIT,
	ENEMY_SPELL,
	ENEMY_DIE,
	ENEMY_NULL
};

//��Ʋ�÷��̾� �θ�Ŭ���� ���漱��
class battlePlayerMother;

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

	unsigned int _damage;					//���� ������
	unsigned int _spellDamage;				//��ų ������
	
	unsigned int _m_Def;					//���� ����
	unsigned int _a_Def;					//���� ����
	
	unsigned int _speed;					//���� Ÿ�̸�

	unsigned int _evasion;					//ȸ����
	unsigned int _hitRate;					//���߷�
	unsigned int _block;					//�����

	unsigned int _x, _y;					//�̹��� �Ѹ��� ���� ��ǥ
	unsigned int _frameX;					//�̹��� ������
	unsigned int _alpha;					//���ʹ� ���� ��

	unsigned int _glitterCount;				//glitter�Լ����� �� ī��Ʈ����

	bool _turnEnd = false;					//���ʹ̵� ���̴�?

	unsigned int _state;					//���ʹ̵� ���°�
	
	effect* _atkEffect;						//���ʹ� �⺻���� ����Ʈ
	effect* _spellEffect;					//���ʹ� ��ų���� ����Ʈ
	effect* _spellEffect2;					//���� �ι�° ��ų ����Ʈ
	bool _effectFire;						//����Ʈ ��Ʈ���� ���� �Ұ�

	int _count = 0;

	//============= ���漱�� =============

	battlePlayerMother* _tina;
	battlePlayerMother* _shadow;
	battlePlayerMother* _locke;
	battlePlayerMother* _celes;

	//===================================

public:
	Enemy();
	~Enemy();
	
	//		  ���͸� �ѷ��� x,     y
	virtual HRESULT init(int x, int y);
	virtual void update();
	virtual void render();

	void enemyTurn(int damage);				//������ ���� �Լ�

	void glitter();							//���ʹ� ���϶� � ���ʹ��� ������ �˱����� �Լ� (��¦�Ÿ�)

	//======================================= ���漱�� ========================================================

	void setBattleTinaMemoryAddressLink(battlePlayerMother* tina) { _tina = tina; }
	void setBattleShadowMemoryAddressLink(battlePlayerMother* shadow) { _shadow = shadow; }
	void setBattleLockeMemoryAddressLink(battlePlayerMother* locke) { _locke = locke; }
	void setBattleCelesMemoryAddressLink(battlePlayerMother* celes) { _celes = celes; }

	//========================================================================================================

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

	inline bool getTurnEnd() { return _turnEnd; }
	inline void setTurnEnd(bool enemyTurn) { _turnEnd = enemyTurn; }

	inline bool getEffectFire() { return _effectFire; }
	inline void setEffectFire(bool effectFire) { _effectFire = effectFire; }

	//========================================================================
};

