#pragma once
#include "gameNode.h"



class battlePlayerMother : public gameNode
{
private:
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

	//�ִϸ��̼� ���� �����
	image* _idleImg;			//������
	animation* _idleAnim;
	image* _atkImg;				//����
	animation* _atkAnim;
	image* _stanbyImg;			//�����ϱ� ������ �������!!!
	animation* _stanbyAnim;		
	image* _magicAtkImg;		//���� ����
	animation* _magicAtkAnim;
	image* _magicStanbyImg;		//���� ���� ������ �������!
	animation* _magicStanbyAnim;
	image* _winImg;				//�̰�����
	animation* _winAnim;
	image* _winBeforeImg;		//�̰����� ��� ������ ������ ���� �̹���
	animation* _winBeforeAnim;
	image* _deadImg;				//���� ��� 
	animation* _deadAnim;
	image* _jump;				//���� ��� : 1������



public:
	battlePlayerMother();
	~battlePlayerMother();

	virtual HRESULT init();
	virtual void update();
	virtual void render();
	virtual void draw();
	virtual void release();

	//===============================Start ������ ������ =======================================
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
	//====================================== End ������ ������ ======================================

	//��Ʋ������ �� �Ѳ����� ��� ��Ʋ�÷��̾ ��������
	void setAllBattlePlayerInfo(int lv, int curExp, int maxExp, int curHp, int maxHp, int curMp,
		int maxMp, int speed, int strength, int magic, int m_def, int a_def, int attack, int evasion, int m_evasion, int stamina);
	
};

