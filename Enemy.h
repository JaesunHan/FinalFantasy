#pragma once
#include "gameNode.h"
#include "effect.h"
#include "itemManager.h"

//에너미 상태값
enum EnemyState
{
	ENEMY_HIT,
	ENEMY_SPELL,
	ENEMY_DIE,
	ENEMY_NULL
};

class battlePlayerMother;					//배틀플레이어 부모클래스 전방선언

class Enemy : public gameNode
{
protected:
	image* _img;

	unsigned int _Lv;						//레벨
	unsigned int _maxEXP;					//경험치
	unsigned int _gold;						//돈
	unsigned int _curHP, _maxHP;			//현재 체력, 최대 체력
	unsigned int _curMP, _maxMP;			//현재 마력, 최대 마력
	unsigned int _attack;					//기본 데미지
	unsigned int _magic;					//마법 데미지
	unsigned int _rndNum;					//랜덤수를 담기 위한 변수
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
	unsigned int _state;					//에너미들 상태값
	unsigned int _count = 0;

	float _damage;							//최종 데미지
	float _spellDamage;						//스킬 최종 데미지
	float _spellPower;						//스펠 데미지

	bool _turnEnd;							//에너미들 턴이니?
	bool _effectFire;						//이펙트 터트리기 위한 불값

	char _basicAttack[128];					//기본공격의 사운드와 이펙트를 위한 변수
	char _skillAttack[128];					//스킬공격의 사운드와 이펙트를 위한 변수
	char _damageNum[128];					//데미지를 넣기 위한 변수
	char _itemString[128];					//아이템 이름을 가져오자

	effect* _atkEffect;						//에너미 기본공격 이펙트
	effect* _spellEffect;					//에너미 스킬공격 이펙트
	effect* _spellEffect2;					//보스 두번째 스킬 이펙트

	//============= 전방선언 =============
	battlePlayerMother* _celes;
	battlePlayerMother* _locke;
	battlePlayerMother* _shadow;
	battlePlayerMother* _tina;
	battlePlayerMother* _target;
	//===================================

public:
	Enemy();
	~Enemy();
	
	//		  몬스터를 뿌려줄 x,     y
	virtual HRESULT init(int x, int y);
	virtual void update();
	virtual void render();

	virtual void damageAlgorithm();					//데미지 공식 함수

	virtual void glitter();							//에너미 턴일때 어떤 에너미의 턴인지 알기위한 함수 (반짝거림)

	virtual void playerGetItem();					//플레이어가 아이템을 얻었는가?

	//======================================= 전방선언 ========================================================
	void setBattleCelesMemoryAddressLink(battlePlayerMother* celes) { _celes = celes; }
	void setBattleLockeMemoryAddressLink(battlePlayerMother* locke) { _locke = locke; }
	void setBattleShadowMemoryAddressLink(battlePlayerMother* shadow) { _shadow = shadow; }
	void setBattleTinaMemoryAddressLink(battlePlayerMother* tina) { _tina = tina; }
	void setTargetMemoryAddressLink(battlePlayerMother* target) { _target = target; }
	//========================================================================================================

	//================================ 접근자 =================================

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

	//================================ 설정자 =================================
	inline void setAlpha(int alpha) { _alpha = alpha; }
	inline void setMaxEXP(int maxEXP) { _maxEXP = maxEXP; }
	inline void setCurHP(int curHP) { _curHP = curHP; }
	inline void setCurMP(int curMP) { _curMP = curMP; }
	inline void setTurnEnd(bool enemyTurn) { _turnEnd = enemyTurn; }
	inline void setEffectFire(bool effectFire) { _effectFire = effectFire; }
	//========================================================================
};

