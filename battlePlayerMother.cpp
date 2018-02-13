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
	

	_counter++;
	if (_counter % 100 == 0)
	{

		_turnEnd = true;
		_status = BATTLE_PLAYER_IDLE;
		_counter = 0;
	}

	
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
		
		_idleImg->aniRender(getMemDC(), 800 - (_partyIdx % 2) * 70, 150 + _partyIdx * 100, _idleAnim);
	}
	// 스탠바이를 재생하고 그 다음에 공격모션을 한다
	if (_status == BATTLE_PLAYER_ATTACK_STANDBY)
	{
		_atkStandbyImg->aniRender(getMemDC(), 800 - (_partyIdx % 2) * 70, 150 + _partyIdx * 100, _atkStandbyAnim);
	}
	if (_status == BATTLE_PLAYER_ATTACK)
	{
		//TextOut(getMemDC(), 800 - (_partyIdx % 2) * 70+60, 150 + _partyIdx * 100 - 10, "공격", strlen("공격"));
		_atkImg->aniRender(getMemDC(), 800 - (_partyIdx % 2) * 70, 150 + _partyIdx * 100, _atkAnim);
	}
	//마법 공격 스탠바이를 재생하고 그 다음에 마법 공격 모션을 한다.
	if (_status == BATTLE_PLAYER_MAGIC_ATTACK_STANDBY)
	{

		_magicAtkStandbyImg->aniRender(getMemDC(), 800 - (_partyIdx % 2) * 70, 150 + _partyIdx * 100, _magicAtkStandbyAnim);
	}
	//마법 공격
	if (_status == BATTLE_PLAYER_MAGIC_ATTACK)
	{
		
		_magicAtkImg->aniRender(getMemDC(), 800 - (_partyIdx % 2) * 70, 150 + _partyIdx * 100, _magicAtkAnim);
	}

	if (_status == BATTLE_PLAYER_DEAD)
	{
		
		_deadImg->aniRender(getMemDC(), 800 - (_partyIdx % 2) * 70, 150 + _partyIdx * 100, _deadAnim);
	}
	if (_status == BATTLE_PLAYER_WIN_BEFORE)
	{
		_winBeforeImg->aniRender(getMemDC(), 800 - (_partyIdx % 2) * 70, 150 + _partyIdx * 100, _winBeforeAnim);
		
	}
	//if (_status == BATTLE_PLAYER_WIN)
	//{
	//	_winImg->aniRender(getMemDC(), 800 - (_partyIdx % 2) * 70, 150 + _partyIdx * 100, _winAnim);
	//}
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
		if (_status >= BATTLE_PLAYER_NONE-1)	 _status = BATTLE_PLAYER_IDLE;
		_playAnimList[_status] = false;
	}
	//IDLE일때
	if (_status == BATTLE_PLAYER_IDLE)
	{
		//애니메이션 재생중이 아닐 때 
		if (!_playAnimList[BATTLE_PLAYER_IDLE])
		{
			_idleAnim->start();		//애니메이션 저장
			_playAnimList[BATTLE_PLAYER_IDLE] = true;		//재생중이니까 true 바꾸기
		}
		_idleAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
		
	}
	//attack 스탠바이
	if (_status == BATTLE_PLAYER_ATTACK_STANDBY)
	{
		if (!_playAnimList[BATTLE_PLAYER_ATTACK_STANDBY])
		{
			_atkStandbyAnim->start();
			_playAnimList[BATTLE_PLAYER_ATTACK_STANDBY] = true;
		}
		_atkStandbyAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
	}
	//attack 일때
	if (_status == BATTLE_PLAYER_ATTACK)
	{
		if (!_playAnimList[BATTLE_PLAYER_ATTACK])
		{
			_atkAnim->start();
			_playAnimList[BATTLE_PLAYER_ATTACK] = true;
		}
		_atkAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
		setPlayerStatusToIdle(_atkAnim);		//공격이 끝나고 나면 다시 IDLE 상태로 전환한다.
	}
	//마법 공격 스탠바이
	if (_status == BATTLE_PLAYER_MAGIC_ATTACK_STANDBY)
	{
		if (!_playAnimList[BATTLE_PLAYER_MAGIC_ATTACK_STANDBY])
		{
			_magicAtkStandbyAnim->start();
			_playAnimList[BATTLE_PLAYER_MAGIC_ATTACK_STANDBY] = true;
		}
		_magicAtkStandbyAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
	}

	//마법 공격
	if (_status == BATTLE_PLAYER_MAGIC_ATTACK)
	{
		if (!_playAnimList[BATTLE_PLAYER_MAGIC_ATTACK])
		{
			_magicAtkAnim->start();
			_playAnimList[BATTLE_PLAYER_MAGIC_ATTACK] = true;
		}
		_magicAtkAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
		setPlayerStatusToIdle(_magicAtkAnim);	//공격이 끝나고 나면 다시 IDLE 상태로 전환한다.
	}
	//죽을 때 
	if (_status == BATTLE_PLAYER_DEAD)
	{
		if (!_playAnimList[BATTLE_PLAYER_DEAD])
		{
			_deadAnim->start();
			_playAnimList[BATTLE_PLAYER_DEAD] = true;
		}
		_deadAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 5);
		
	}
	//이기기 전에 한번만 재생되어야 하는 애니메이션 이다.
	if (_status == BATTLE_PLAYER_WIN_BEFORE)
	{
		if (!_playAnimList[BATTLE_PLAYER_WIN_BEFORE])
		{
			_winBeforeAnim->start();
			_playAnimList[BATTLE_PLAYER_WIN_BEFORE] = true;
		}
		_winBeforeAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 7);
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

