#pragma once

class weaponItem;
class playerMother
{
protected:
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

	image* _faceImg;				//���̹���

	int _partyIdx;					//��Ƽ�� ���ӵǾ� �ִٸ� ���° ��Ƽ���ΰ�?!

	weaponItem* _defaultWeapon;		//�⺻���� ������ ����(���� ���� ������ ���� �⺻ ����)
	weaponItem* _myWeapon;			//���� ������ ����
public:
	playerMother();
	~playerMother();

	//============================Start ������ ������ =======================================
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
	//�÷��̾��� �⺻ ���� ���⿡ ���� ���ͼ���
	inline weaponItem* getDefaultWeapon() { return _defaultWeapon; }
	inline void setDefaultWeapon(weaponItem* weapon) { _defaultWeapon = weapon; }
	//�÷��̾��� ���� ���� ���⿡ ���� ���ͼ���
	inline weaponItem* getWeapon() { return _myWeapon; }	inline void setWeaponItem(weaponItem* weapon) { _myWeapon = weapon; }

	//============================== End ������ ������ ======================================

};

