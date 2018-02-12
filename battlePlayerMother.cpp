#include "stdafx.h"
#include "battlePlayerMother.h"


battlePlayerMother::battlePlayerMother()
{
	//여기나 아니면 init 에 이미지 초기화 넣기	
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
	
	

}
void battlePlayerMother::render() 
{
	draw();
}
void battlePlayerMother::draw()	  
{
	//================== Start 상태에 따라 다른 애니메이션을 출력한다. =======================
	if (_status == BATTLE_PLAYER_IDLE)
	{
		
		_idleImg->aniRender(getMemDC(), 800 - _idleImg->getFrameWidth() / 2, 150 + _partyIdx * 100, _idleAnim);
	}
	if (_status == BATTLE_PLAYER_ATTACK)
	{
		
		_atkImg->aniRender(getMemDC(), 800 - _atkImg->getFrameWidth(), 150 + _partyIdx * 100, _atkAnim);
	}
	if (_status == BATTLE_PLAYER_MAGIC_ATTACK)
	{
		
		_magicAtkImg->aniRender(getMemDC(), 800 - _magicAtkImg->getFrameWidth() / 2, 150 + _partyIdx * 100, _magicAtkAnim);
	}
	if (_status == BATTLE_PLAYER_DEAD)
	{
		
		_deadImg->aniRender(getMemDC(), 800 - _deadImg->getFrameWidth() / 2, 150 + _partyIdx * 100, _deadAnim);
	}
	if (_status == BATTLE_PLAYER_WIN)
	{
		
		_winImg->aniRender(getMemDC(), 800 - _winImg->getFrameWidth() / 2, 150 + _partyIdx * 100, _winAnim);
	}
	//================== End 상태에 따라 다른 애니메이션을 출력한다. =======================
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
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		_status = (baattlePlayerStatus)((int)_status + 1);
		if (_status > BATTLE_PLAYER_NONE)	 _status = BATTLE_PLAYER_IDLE;
		_playAnimList[_status] = false;
	}
	if (_status == BATTLE_PLAYER_IDLE)
	{
		if (!_playAnimList[BATTLE_PLAYER_IDLE])
		{
			_idleAnim->start();
			_playAnimList[BATTLE_PLAYER_IDLE] = true;
		}
		_idleAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
		
	}
	if (_status == BATTLE_PLAYER_ATTACK)
	{
		if (!_playAnimList[BATTLE_PLAYER_ATTACK])
		{
			_atkAnim->start();
			_playAnimList[BATTLE_PLAYER_ATTACK] = true;
		}
		_atkAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
		setPlayerStatusToIdle(_atkAnim);
	}
	if (_status == BATTLE_PLAYER_MAGIC_ATTACK)
	{
		if (!_playAnimList[BATTLE_PLAYER_MAGIC_ATTACK])
		{
			_magicAtkAnim->start();
			_playAnimList[BATTLE_PLAYER_MAGIC_ATTACK] = true;
		}
		_magicAtkAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
		setPlayerStatusToIdle(_magicAtkAnim);
	}
	if (_status == BATTLE_PLAYER_DEAD)
	{
		if (!_playAnimList[BATTLE_PLAYER_DEAD])
		{
			_deadAnim->start();
			_playAnimList[BATTLE_PLAYER_DEAD] = true;
		}
		_deadAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 5);
		
	}
	if (_status == BATTLE_PLAYER_WIN)
	{
		if (!_playAnimList[BATTLE_PLAYER_WIN])
		{
			_winAnim->start();
			_playAnimList[BATTLE_PLAYER_WIN] = true;
		}
		_winAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 7);
		
	}
}

void battlePlayerMother::setPlayerStatusToIdle(animation* anim)
{
	if(!anim->isPlay())
	{
		_status = BATTLE_PLAYER_IDLE;
	}
}

int battlePlayerMother::attackAlgorithm()
{
	int vigor2 = _strength * 2;
	if (_strength >= 128) vigor2 = 255;
	int atk = _attack + vigor2;

	int dmg = (float)_attack + (((float)_Lv*(float)_Lv*(float)atk) / 256.0)*3.0 / 2.0;
	return dmg;
}