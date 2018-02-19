#pragma once

class weaponItem;
class playerMother
{
protected:
	TCHAR _name[256];				//�÷��̾� �̸�
	TCHAR _job[256];				//�÷��̾� ����
	unsigned int _Lv;
	unsigned int _curEXP, _maxEXP;
	unsigned int _curHP, _maxHP;
	unsigned int _curMP, _maxMP;
	unsigned int _speed;			//���� Ÿ�̸�
	unsigned int _strength;			//���� ������
	unsigned int _magic;			//���� ������
	unsigned int _m_Def;			//���� ����
	unsigned int _a_Def;			//���� ����
	unsigned int _attack;			//�⺻ ���ݷ� + ������ ���ݷ�
	unsigned int _evasion;			//ȸ����
	unsigned int _m_evasion;		//���� ȸ��
	unsigned int _stamina;			//���¹̳��� ������ �𸣰ڴµ� �ڷῡ �ִ�...
	unsigned int _spellPower;		//�����Ŀ�

	image* _faceImg;				//���̹���

	int _partyIdx;					//��Ƽ�� ���ӵǾ� �ִٸ� ���° ��Ƽ���ΰ�?!

	weaponItem* _defaultWeapon;		//�⺻���� ������ ����(���� ���� ������ ���� �⺻ ����)
	weaponItem* _myWeapon;			//���� ������ ����
public:
	playerMother();
	~playerMother();

	//============================Start ������ ������ =======================================
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
	//�÷��̾��� �⺻ ���� ���⿡ ���� ���ͼ���
	inline weaponItem* getDefaultWeapon() { return _defaultWeapon; }
	inline void setDefaultWeapon(weaponItem* weapon) { _defaultWeapon = weapon; }
	//�÷��̾��� ���� ���� ���⿡ ���� ���ͼ���
	inline weaponItem* getWeapon() { return _myWeapon; }	inline void setWeaponItem(weaponItem* weapon) { _myWeapon = weapon; }

	inline TCHAR* getName() { return _name; }	inline void setName(char str[256]) { wsprintf(_name, "%s", str); }
	inline TCHAR* getJob() { return _job; }		inline void setJob(char str[256]) { wsprintf(_job, "%s", str); }

	//============================== End ������ ������ ======================================

};

