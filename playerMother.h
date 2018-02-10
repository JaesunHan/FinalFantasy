#pragma once

class playerMother
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

public:
	playerMother();
	~playerMother();

	//============================Start 접근자 설정자 =======================================
	int getLv() { return _Lv; }		void setLv(int lv) { _Lv = lv; }

	int getCurEXP() { return _curEXP; }	void setCurEXP(int curEXP) { _curEXP = curEXP; }
	int getMaxEXP() { return _maxEXP; } void setMaxEXP(int maxEXP) { _maxEXP = maxEXP; }

	int getCurHP() { return _curHP; } void setCurHP(int curHP) { _curHP = curHP; }
	int getMaxHP() { return _maxHP; } void setMaxHP(int maxHP) { _maxHP = maxHP; }

	int getCurMP() { return _curMP; } void setCurMP(int curMP) { _curMP = curMP; }
	int getMaxMP() { return _maxMP; } void setMaxMP(int maxMP) { _maxMP = maxMP; }

	int getSpeed() { return _speed; }
	int getStrength() { return _strength; }
	int getMagic() { return _magic; }
	int getMDef() { return _m_Def; }
	int getADef() { return _a_Def; }
	int getAttack() { return _attack; }
	int getEvasion() { return _evasion; }
	int getMEvasion() { return _m_evasion; }
	int getStamina() { return _stamina; }
	image* getFaceImg() { return _faceImg; }
	//============================== End 접근자 설정자 ======================================


};

