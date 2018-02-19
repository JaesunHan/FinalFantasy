#pragma once

class weaponItem;
class playerMother
{
protected:
	TCHAR _name[256];				//플레이어 이름
	TCHAR _job[256];				//플레이어 직업
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
	unsigned int _spellPower;		//스펠파워

	image* _faceImg;				//얼굴이미지

	int _partyIdx;					//파티에 종속되어 있다면 몇번째 파티원인가?!

	weaponItem* _defaultWeapon;		//기본으로 장착한 무기(무기 장착 안했을 때의 기본 무기)
	weaponItem* _myWeapon;			//내가 장착한 무기
public:
	playerMother();
	~playerMother();

	//============================Start 접근자 설정자 =======================================
	inline int getLv() { return _Lv; }		inline void setLv(int lv) { _Lv = lv; }

	inline int getCurEXP() { return _curEXP; }	inline void setCurEXP(int curEXP) { _curEXP = curEXP; }
	inline int getMaxEXP() { return _maxEXP; }	inline void setMaxEXP(int maxEXP) { _maxEXP = maxEXP; }

	inline int getCurHP() { return _curHP; } inline void setCurHP(int curHP) { _curHP = curHP; }
	inline int getMaxHP() { return _maxHP; } inline void setMaxHP(int maxHP) { _maxHP = maxHP; }

	inline int getCurMP() { return _curMP; } inline void setCurMP(int curMP) { _curMP = curMP; }
	inline int getMaxMP() { return _maxMP; } inline void setMaxMP(int maxMP) { _maxMP = maxMP; }

	inline int getSpeed() { return _speed; }		inline void setSpeed(int spd) { _speed = spd; }
	inline int getStrength() { return _strength; }	inline void setStrength(int strength) { _strength = strength; }
	inline int getMagic() { return _magic; }		inline void setMagic(int magic) { _magic = magic; }
	inline int getMDef() { return _m_Def; }			inline void setMDef(int mdef) { _m_Def = mdef; }
	inline int getADef() { return _a_Def; }			inline void setADef(int adef) { _a_Def = adef; }
	inline int getAttack() { return _attack; }		inline void setAttack(int atk) { _attack = atk; }
	inline int getEvasion() { return _evasion; }	inline void setEvasion(int evasion) { _evasion = evasion; }
	inline int getMEvasion() { return _m_evasion; }	inline void setMEvasion(int mevas) { _m_evasion = mevas; }
	inline int getStamina() { return _stamina; }	inline void setStamina(int stamina) { _stamina = stamina; }
	inline image* getFaceImg() { return _faceImg; }	

	inline int getPartyIdx() { return _partyIdx; }	inline void setPartyIdx(int idx) { _partyIdx = idx; }
	//플레이어의 기본 장착 무기에 대한 게터세터
	inline weaponItem* getDefaultWeapon() { return _defaultWeapon; }
	inline void setDefaultWeapon(weaponItem* weapon) { _defaultWeapon = weapon; }
	//플레이어의 현재 장착 무기에 대한 게터세터
	inline weaponItem* getWeapon() { return _myWeapon; }	inline void setWeaponItem(weaponItem* weapon) { _myWeapon = weapon; }

	inline TCHAR* getName() { return _name; }	inline void setName(char str[256]) { wsprintf(_name, "%s", str); }
	inline TCHAR* getJob() { return _job; }		inline void setJob(char str[256]) { wsprintf(_job, "%s", str); }

	//============================== End 접근자 설정자 ======================================

};

