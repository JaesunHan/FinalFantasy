#pragma once
#include "gameNode.h"
#include "magic.h"
#define MAXANIMATIONNUM 9
#define MAXATKMOTION	3
//배틀 플레이어의 상태를 나타낼 enum
enum baattlePlayerStatus
{
	BATTLE_PLAYER_IDLE,
	BATTLE_PLAYER_ATTACK_STANDBY,
	BATTLE_PLAYER_ATTACK,
	BATTLE_PLAYER_MAGIC_ATTACK_STANDBY,
	BATTLE_PLAYER_MAGIC_ATTACK,
	BATTLE_PLAYER_DEAD,
	BATTLE_PLAYER_WIN_BEFORE,
	BATTLE_PLAYER_WIN,
	BATTLE_PLAYER_ITEM,
	//BATTLE_PLAYER_JUMP,
	//BATTLE_PLAYER_MOVE,
	BATTLE_PLAYER_NONE
};

class BattleScene;
class Enemy;
class weaponItem;
class armorItem;
class battlePlayerMother : public gameNode
{
protected:
	unsigned int _Lv;
	unsigned int _curEXP, _maxEXP;
	unsigned int _curHP, _maxHP;
	unsigned int _curMP, _maxMP;
	unsigned int _speed;			//공격 타이머
	unsigned int _strength;			//물리 데미지
	unsigned int _magic;			//마법 데미지
	unsigned int _m_Def;			//마법 방어력
	unsigned int _a_Def;			//물리 방어력
	unsigned int _attack;			//기본 공격력 + 무기의 공격력
	unsigned int _evasion;			//회피율
	unsigned int _m_evasion;		//마법 회피
	unsigned int _stamina;			//스태미나가 뭔지는 모르겠는데 자료에 있당...

	image* _faceImg;				//얼굴이미지

	//애니메이션 변수 만들기
	image* _idleImg;			//대기상태
	animation* _idleAnim;
	image* _atkImg;				//공격
	animation* _atkAnim;
	image* _atkStandbyImg;		//공격 대기
	animation* _atkStandbyAnim;	
		
	image* _magicAtkImg;		//마법 공격
	animation* _magicAtkAnim;
	image* _magicAtkStandbyImg;		//마법 공격 대기
	animation* _magicAtkStandbyAnim;	
	
	image* _winImg;				//이겼을때
	animation* _winAnim;
	image* _winBeforeImg;		//이기기 직전에
	animation* _winBeforeAnim;	

	image* _deadImg;				//죽은 모습 
	animation* _deadAnim;
	image* _jumpImg;				//점프 모습 : 1프레임
	image* _moveImg;				//움직일 때 모습: 1프레임
	

	baattlePlayerStatus _status;	//배틀플레이어의 상태

	bool _turnEnd;					//배틀 플레이어의 턴이 끝났을 때 반환할 불값

	int _partyIdx;					//파티에 종속되어 있다면 몇변째 파티원인가?!
	float _posX, _posY;				//출력될 위치좌표(중점)

	
	//애니메이션을 재생할지 말지에 대한 불값
	bool _playAnimList[MAXANIMATIONNUM];
	
	//공경할 때 근거리 애들( true )은 에너미한테 가서 공격하고, 원거리 애들( false )은 제자리에서 공격해야 한다.
	bool _atkDistance;
	//공격할 때 일정 시간동안에는 무빙을 ㅏ고
	bool _atkMotionList[3];
	bool _isStartAtk;
	float _angle;	/*움직일 방향*/	float _moveSpd;	/*움직일 때 속도*/
	//공격할 때 일정 시간동안애는 공격을 한다.
	bool _atkMotion;

	//일반공격 타겟
	Enemy* _target;
	//마법 공격 타겟(적)
	Enemy* _mEnemyTarget;
	//마법 힐 타겟(아군)
	battlePlayerMother* _mAllyTarget;
	//선택한 마법 종류
	magic* _selectMagic;

	
	//아이템 사용시 띄울 이팩트이다
	image* _itemEffectImg;
	animation* _itemEffect;

	float _targetX, _targetY;
	int _targetWidth, _targetHeight;

	float _hitRate;		//

	BattleScene* _BS;

	int _atkAnimPlaySPD;		//어택 공격 애니메이션 재생할 때 속도

	//공격할 때 띄울 사운드의 키값
	string _atkEffectSoundKey;
	string _atkEffectSoundFile;

	//마법 공격할 때 띄울 사운드 키값
	string _mAtkEffectSoundKey;
	string _mAtkEffectSoundFile;
	//마법 힐 할 때 띄울 사운드 키값
	string _healEffectSoundKey;
	string _healEffectSoundFile;

	//장착한 무기
	weaponItem* _myWeapon;
	//장착한 갑옷
	armorItem* _myArmor;
	//장착한 투구
	armorItem* _myHelmet;
	//장착한 보조무기
	armorItem* _mySubWeapon;
	
	//마법 공격
	vector<magic*> _myUsableMagic;

public:
	battlePlayerMother();
	~battlePlayerMother();

	virtual HRESULT init();
	virtual void update();
	virtual void render();
	virtual void draw();
	virtual void release();

	virtual void animationFrameUpdate();

	//===============================Start 접근자 설정자 =======================================
	inline int getLv() { return _Lv; }		inline void setLv(int lv) { _Lv = lv; }

	inline int getCurEXP() { return _curEXP; }	inline void setCurEXP(int curEXP) { _curEXP = curEXP; }
	inline int getMaxEXP() { return _maxEXP; } inline void setMaxEXP(int maxEXP) { _maxEXP = maxEXP; }

	inline int getCurHP() { return _curHP; } inline void setCurHP(int curHP) { _curHP = curHP; }
	inline int getMaxHP() { return _maxHP; } inline void setMaxHP(int maxHP) { _maxHP = maxHP; }

	inline int getCurMP() { return _curMP; } inline void setCurMP(int curMP) { _curMP = curMP; }
	inline int getMaxMP() { return _maxMP; } inline void setMaxMP(int maxMP) { _maxMP = maxMP; }

	inline int getSpeed() { return _speed; }
	inline int getStrength() { return _strength; }
	inline int getMagic() { return _magic; }
	inline int getMDef() { return _m_Def; }
	inline int getADef() { return _a_Def; }
	inline int getAttack() { return _attack; }
	inline int getEvasion() { return _evasion; }
	inline image* getFaceImg() { return _faceImg; }
	
	inline bool getTurnEnd() { return _turnEnd; }	inline void setTurnEnd(bool turnEnd) { _turnEnd = turnEnd; }
	inline int getPartyIdx() { return _partyIdx; }	inline void setPartyIdx(int idx) { _partyIdx = idx; }
	inline baattlePlayerStatus getStatus() { return _status; }	inline void setStatus(baattlePlayerStatus status) { _status = status; }
	inline float getPosX() { return _posX; }	
	inline float getPosY() { return _posY; }
	inline float getHitRate() { return _hitRate; }

	//플레이어의 가로 세로 크기
	inline int getWidth() { return _idleImg->getFrameWidth(); }
	inline int getHeight() { return _idleImg->getFrameHeight(); }

	//플레이어가 장착한 무기 세팅
	inline weaponItem* getWeapon() { return _myWeapon; }
	inline void setWeapon(weaponItem* weapon) { _myWeapon = weapon; }

	//플레이어가 장착한 갑옷 세팅
	inline armorItem* getArmor() { return _myArmor; }
	inline void setArmor(armorItem* armor) { _myArmor = armor; }

	//플레이어가 장착한 투구 세팅
	inline armorItem* getHelmet() { return _myHelmet; }
	inline void setHelmet(armorItem* helmet) { _myHelmet = helmet; }

	//플레이어가 장착한 보조 무기 세팅
	inline armorItem* getSubWeapon() { return _mySubWeapon; }
	inline void setSubWeapon(armorItem* subWeapon) { _mySubWeapon = subWeapon; }
	
	//배틀 플레이어가 보유하고 있는 마법 목록 게터
	inline vector<magic*> getMyUsableMagic() {
		return _myUsableMagic;	
	}
	inline void setMyUsableMagic(vector<magic*> vMagic) { _myUsableMagic = vMagic; }

	//====================================== End 접근자 설정자 ======================================

	//배틀시작할 때 한꺼번에 모든 배틀플레이어를 세팅하자
	void setAllBattlePlayerInfo(int lv, int curExp, int maxExp, int curHp, int maxHp, int curMp,
		int maxMp, int speed, int strength, int magic, int m_def, int a_def, int attack, int evasion, int m_evasion, int stamina);

	//플레이어의 상태를 IDLE 로 전환하는 함수이다.
	void setPlayerStatusToIdle(animation* anim);
	//공격 공식 알고리즘
	int attackAlgorithm();

	//공격할 대상 에너미의 주소를 받아온다
	void setTargetEnemy(Enemy* target) { _target = target; }
	void setPlayerDefaultPosition();
	//지정한 포지션까지 움직이는 함수(지정한 포지션까지 도달했으면 true 를 반환한다.)
	bool moveToTarget(int targetX, int targetY, int motionListIdx);

	void setBattleScene(BattleScene* bs) { _BS = bs; }

	//마법공격할 적 대상세팅
	void setMEnemyTarget(Enemy* target) { _mEnemyTarget = target; }
	//마법 힐을 줄 아군 대상 세팅
	void setMAllyTarget(battlePlayerMother* target) { _mAllyTarget = target; }
	//선택한 마법 세팅
	void setSelectMagic(magic* m) { _selectMagic = m; }

	//마법 힐 할 때 힐퍼센트를 힐해줄 대상에게 적용하기
	void calculateMagicHeal();
};

