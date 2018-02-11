#include "stdafx.h"
#include "battlePlayerMother.h"


battlePlayerMother::battlePlayerMother()
{
	//���⳪ �ƴϸ� init �� �̹��� �ʱ�ȭ �ֱ�	
}


battlePlayerMother::~battlePlayerMother()
{

}


HRESULT battlePlayerMother::init()
{

	return S_OK;
}
void battlePlayerMother::update() 
{
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		_status = (baattlePlayerStatus)((int)_status + 1);
	}
	//================= Start ���� ���¿� ���� ���� �ٸ� �ִϸ��̼��� ������ ������ ���ش�.==========
	
	//================= End ���� ���¿� ���� ���� �ٸ� �ִϸ��̼��� ������ ������ ���ش�.==========

}
void battlePlayerMother::render() 
{
	draw();
}
void battlePlayerMother::draw()	  
{
	//================== Start ���¿� ���� �ٸ� �ִϸ��̼��� ����Ѵ�. =======================
	if (_status == BATTLE_PLAYER_IDLE)
	{
		_idleImg->aniRender(getMemDC(), 800, 150 + _partyIdx * 100, _idleAnim);
	}
	if (_status == BATTLE_PLAYER_ATTACK)
	{
		_atkImg->aniRender(getMemDC(), 800, 150 + _partyIdx * 100, _atkAnim);
	}
	if (_status == BATTLE_PLAYER_MAGIC_ATTACK)
	{
		_magicAtkImg->aniRender(getMemDC(), 800, 150 + _partyIdx * 100, _magicAtkAnim);
	}
	if (_status == BATTLE_PLAYER_DEAD)
	{
		_deadImg->aniRender(getMemDC(), 800, 150 + _partyIdx * 100, _deadAnim);
	}
	if (_status == BATTLE_PLAYER_WIN)
	{
		_winImg->aniRender(getMemDC(), 800, 150 + _partyIdx * 100, _winAnim);
	}
	//================== End ���¿� ���� �ٸ� �ִϸ��̼��� ����Ѵ�. =======================
}
void battlePlayerMother::release()
{

}

void battlePlayerMother::setAllBattlePlayerInfo(int lv, int curExp, int maxExp, int curHp, int maxHp, int curMp,
	int maxMp, int speed, int strength, int magic, int m_def, int a_def, int attack, int evasion, int m_evasion, int stamina)
{
	_Lv = lv, curExp = curExp, _maxEXP = maxExp, _curHP = curHp, _maxHP = maxHp;
	_curMP = curMp, _maxMP = maxMp, _speed = speed, _strength = strength, _magic = magic;
	_m_Def = m_def, _a_Def = a_def, _attack = attack, _evasion = evasion;
}

void battlePlayerMother::animationFrameUpdate()
{
	if (_status == BATTLE_PLAYER_IDLE)
	{
		_idleAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
	}
	if (_status == BATTLE_PLAYER_ATTACK)
	{
		_atkAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
	}
	if (_status == BATTLE_PLAYER_MAGIC_ATTACK)
	{
		_magicAtkAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
	}
	if (_status == BATTLE_PLAYER_DEAD)
	{
		_deadAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
	}
	if (_status == BATTLE_PLAYER_WIN)
	{
		_winAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
	}
}