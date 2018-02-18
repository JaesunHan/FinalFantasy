#pragma once

class weaponItem;
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

	int _partyIdx;					//파티에 종속되어 있다면 몇번째 파티원인가?!

	weaponItem* _defaultWeapon;		//기본으로 장착한 무기(무기 장착 안했을 때의 기본 무기)
	weaponItem* _myWeapon;			//내가 장착한 무기
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

	inline int getPartyIdx() { return _partyIdx; }	inline void setPartyIdx(int idx) { _partyIdx = idx; }
	//플레이어의 기본 장착 무기에 대한 게터세터
	inline weaponItem* getDefaultWeapon() { return _defaultWeapon; }
	inline void setDefaultWeapon(weaponItem* weapon) { _defaultWeapon = weapon; }
	//플레이어의 현재 장착 무기에 대한 게터세터
	inline weaponItem* getWeapon() { return _myWeapon; }	inline void setWeaponItem(weaponItem* weapon) { _myWeapon = weapon; }

	//============================== End 접근자 설정자 ======================================

};

