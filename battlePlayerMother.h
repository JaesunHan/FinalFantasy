#pragma once
#include "gameNode.h"
#define MAXANIMATIONNUM 8
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
	BATTLE_PLAYER_JUMP,
	BATTLE_PLAYER_MOVE,
	BATTLE_PLAYER_NONE
};

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
	//====================================== End 접근자 설정자 ======================================

	//배틀시작할 때 한꺼번에 모든 배틀플레이어를 세팅하자
	void setAllBattlePlayerInfo(int lv, int curExp, int maxExp, int curHp, int maxHp, int curMp,
		int maxMp, int speed, int strength, int magic, int m_def, int a_def, int attack, int evasion, int m_evasion, int stamina);

	//플레이어의 상태를 IDLE 로 전환하는 함수이다.
	void setPlayerStatusToIdle(animation* anim);
	//공격 공식 알고리즘
	int attackAlgorithm();

	
};

