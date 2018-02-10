#pragma once
#include "gameNode.h"



class battlePlayerMother : public gameNode
{
private:
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
	image* _faceImg;				//얼굴이미지

	//애니메이션 변수 만들기
	image* _idleImg;			//대기상태
	animation* _idleAnim;
	image* _atkImg;				//공격
	animation* _atkAnim;
	image* _stanbyImg;			//공격하기 직전에 기모으기!!!
	animation* _stanbyAnim;		
	image* _magicAtkImg;		//마법 공격
	animation* _magicAtkAnim;
	image* _magicStanbyImg;		//마법 공격 직전에 기모으기!
	animation* _magicStanbyAnim;
	image* _winImg;				//이겼을때
	animation* _winAnim;
	image* _winBeforeImg;		//이겼을때 모션 나오기 직전에 나올 이미지
	animation* _winBeforeAnim;
	image* _dead;				//죽은 모습 : 1프레임
	image* _dying;				//죽어가는 모습 : 1프레임
	image* _jump;				//점프 모습 : 1프레임



public:
	battlePlayerMother();
	~battlePlayerMother();

	virtual HRESULT init();
	virtual void update();
	virtual void render();
	virtual void draw();
	virtual void release();

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
	//====================================== End 접근자 설정자 ======================================

	//배틀시작할 때 한꺼번에 모든 배틀플레이어를 세팅하자
	inline void setAllBattlePlayerInfo(int lv, int curExp, int maxExp, int curHp, int maxHp, int curMp, 
		int maxMp, int speed, int strength, int magic, int m_def, int a_def, int attack , int evasion) 
	{
		_Lv = lv, curExp = curExp, _maxEXP = maxExp, _curHP = curHp, _maxHP = maxHp;
		_curMP = curMp, _maxMP = maxMp, _speed = speed, _strength = strength, _magic = magic;
		_m_Def = m_def, _a_Def = a_def, _attack = attack, _evasion = evasion;
	}
};

