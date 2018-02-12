#pragma once
#include "gameNode.h"
#include "effect.h"

//에너미 상태값
enum EnemyState
{
	ENEMY_HIT,
	ENEMY_SPELL,
	ENEMY_DIE,
	ENEMY_NULL
};

//배틀플레이어 부모클래스 전방선언
class battlePlayerMother;

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

	unsigned int _damage;					//최종 데미지
	unsigned int _spellDamage;				//스킬 데미지
	
	unsigned int _m_Def;					//마법 방어력
	unsigned int _a_Def;					//물리 방어력
	
	unsigned int _speed;					//공격 타이머

	unsigned int _evasion;					//회피율
	unsigned int _hitRate;					//명중률
	unsigned int _block;					//방어율

	unsigned int _x, _y;					//이미지 뿌리기 위한 좌표
	unsigned int _frameX;					//이미지 프레임
	unsigned int _alpha;					//에너미 알파 값

	unsigned int _glitterCount;				//glitter함수에서 쓸 카운트변수

	bool _turnEnd = false;					//에너미들 턴이니?

	unsigned int _state;					//에너미들 상태값
	
	effect* _atkEffect;						//에너미 기본공격 이펙트
	effect* _spellEffect;					//에너미 스킬공격 이펙트
	effect* _spellEffect2;					//보스 두번째 스킬 이펙트
	bool _effectFire;						//이펙트 터트리기 위한 불값

	int _count = 0;

	//============= 전방선언 =============

	battlePlayerMother* _tina;
	battlePlayerMother* _shadow;
	battlePlayerMother* _locke;
	battlePlayerMother* _celes;

	//===================================

public:
	Enemy();
	~Enemy();
	
	//		  몬스터를 뿌려줄 x,     y
	virtual HRESULT init(int x, int y);
	virtual void update();
	virtual void render();

	void enemyTurn(int damage);				//데미지 공식 함수

	void glitter();							//에너미 턴일때 어떤 에너미의 턴인지 알기위한 함수 (반짝거림)

	//======================================= 전방선언 ========================================================

	void setBattleTinaMemoryAddressLink(battlePlayerMother* tina) { _tina = tina; }
	void setBattleShadowMemoryAddressLink(battlePlayerMother* shadow) { _shadow = shadow; }
	void setBattleLockeMemoryAddressLink(battlePlayerMother* locke) { _locke = locke; }
	void setBattleCelesMemoryAddressLink(battlePlayerMother* celes) { _celes = celes; }

	//========================================================================================================

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

	inline bool getTurnEnd() { return _turnEnd; }
	inline void setTurnEnd(bool enemyTurn) { _turnEnd = enemyTurn; }

	inline bool getEffectFire() { return _effectFire; }
	inline void setEffectFire(bool effectFire) { _effectFire = effectFire; }

	//========================================================================
};

