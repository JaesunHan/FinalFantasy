#pragma once
#include "gameNode.h"
#include "effect.h"
#include "itemManager.h"

//���ʹ� ���°�
enum EnemyState
{
	ENEMY_HIT,
	ENEMY_SPELL,
	ENEMY_DIE,
	ENEMY_NULL
};

class battlePlayerMother;					//��Ʋ�÷��̾� �θ�Ŭ���� ���漱��

class Enemy : public gameNode
{
protected:
	image* _img;

	unsigned int _Lv;						//����
	unsigned int _maxEXP;					//����ġ
	unsigned int _gold;						//��
	unsigned int _curHP, _maxHP;			//���� ü��, �ִ� ü��
	unsigned int _curMP, _maxMP;			//���� ����, �ִ� ����
	unsigned int _attack;					//�⺻ ������
	unsigned int _magic;					//���� ������
	unsigned int _rndNum;					//�������� ��� ���� ����
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
	unsigned int _state;					//���ʹ̵� ���°�
	unsigned int _count = 0;

	float _damage;							//���� ������
	float _spellDamage;						//��ų ���� ������
	float _spellPower;						//���� ������

	bool _turnEnd;							//���ʹ̵� ���̴�?
	bool _effectFire;						//����Ʈ ��Ʈ���� ���� �Ұ�

	char _basicAttack[128];					//�⺻������ ����� ����Ʈ�� ���� ����
	char _skillAttack[128];					//��ų������ ����� ����Ʈ�� ���� ����
	char _damageNum[128];					//�������� �ֱ� ���� ����
	char _itemString[128];					//������ �̸��� ��������

	effect* _atkEffect;						//���ʹ� �⺻���� ����Ʈ
	effect* _spellEffect;					//���ʹ� ��ų���� ����Ʈ
	effect* _spellEffect2;					//���� �ι�° ��ų ����Ʈ

	//============= ���漱�� =============
	battlePlayerMother* _celes;
	battlePlayerMother* _locke;
	battlePlayerMother* _shadow;
	battlePlayerMother* _tina;
	battlePlayerMother* _target;
	//===================================

public:
	Enemy();
	~Enemy();
	
	//		  ���͸� �ѷ��� x,     y
	virtual HRESULT init(int x, int y);
	virtual void update();
	virtual void render();

	virtual void damageAlgorithm();					//������ ���� �Լ�

	virtual void glitter();							//���ʹ� ���϶� � ���ʹ��� ������ �˱����� �Լ� (��¦�Ÿ�)

	virtual void playerGetItem();					//�÷��̾ �������� ����°�?

	//======================================= ���漱�� ========================================================
	void setBattleCelesMemoryAddressLink(battlePlayerMother* celes) { _celes = celes; }
	void setBattleLockeMemoryAddressLink(battlePlayerMother* locke) { _locke = locke; }
	void setBattleShadowMemoryAddressLink(battlePlayerMother* shadow) { _shadow = shadow; }
	void setBattleTinaMemoryAddressLink(battlePlayerMother* tina) { _tina = tina; }
	void setTargetMemoryAddressLink(battlePlayerMother* target) { _target = target; }
	//========================================================================================================

	//================================ ������ =================================

	inline int getAlpha() { return _alpha; }
	inline int getImageWidth() { return _img->getFrameWidth(); }
	inline int getImageHeight() { return _img->getFrameHeight(); }
	inline int getLv() { return _Lv; }
	inline int getMaxEXP() { return _maxEXP; }
	inline int getCurHP() { return _curHP; }
	inline int getCurMP() { return _curMP; }
	inline int getMagic() { return _magic; }
	inline int getSpeed() { return _speed; }
	inline int getADef() { return _a_Def; }
	inline int getMDef() { return _m_Def; }
	inline int getAttack() { return _attack; }
	inline int getEvasion() { return _evasion; }
	inline int getGold() { return _gold; }
	inline int getHitRate() { return _hitRate; }
	inline int getBlock() { return _block; }
	inline int getX() { return _x; }
	inline int getY() { return _y; }
	//inline bool getIsItem() { return _isItem; }
	inline bool getTurnEnd() { return _turnEnd; }
	inline bool getEffectFire() { return _effectFire; }
	inline char* getItemName() { return _itemString; }
	//========================================================================

	//================================ ������ =================================
	inline void setAlpha(int alpha) { _alpha = alpha; }
	inline void setMaxEXP(int maxEXP) { _maxEXP = maxEXP; }
	inline void setCurHP(int curHP) { _curHP = curHP; }
	inline void setCurMP(int curMP) { _curMP = curMP; }
	inline void setTurnEnd(bool enemyTurn) { _turnEnd = enemyTurn; }
	inline void setEffectFire(bool effectFire) { _effectFire = effectFire; }
	//========================================================================
};

