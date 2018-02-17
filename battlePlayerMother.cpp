#include "stdafx.h"
#include "battlePlayerMother.h"
#include "BattleScene.h"
#include "Enemy.h"


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
	//attack 일때
	if (_status == BATTLE_PLAYER_ATTACK)
	{
		//공격이 시작됐으면
		if (_isStartAtk)
		{
			_isStartAtk = false;
			_atkMotionList[0] = true;
			_atkMotionList[1] = false;
			_atkMotionList[2] = false;
		}
		//근거리 공격자 인경우에만
		if (_atkDistance)
		{
			//에너미한테 공격하러 간다.
			if (_atkMotionList[0])
			{
				//어디까지 움직여야 하는지 세팅하기
				_targetX = _target->getX() - _target->getImageWidth();
				_targetY = _target->getY() - _target->getImageHeight() / 2;
				moveToTarget(_targetX, _targetY, 0);
			}
			//제자리로 돌아온다
			if (_atkMotionList[2])
			{
				_targetX = 800 - (_partyIdx % 2) * 70;
				_targetY = 150 + _partyIdx * 100;
				moveToTarget(_targetX, _targetY, 2);
			}
		}
		//원거리 공격자일 때는 
		else
		{
			_atkMotionList[1] = true;
		}
		//이제 공격한다.
		if (_atkMotionList[1])
		{
			if (!_playAnimList[BATTLE_PLAYER_ATTACK])
			{
				_atkAnim->start();
				_playAnimList[BATTLE_PLAYER_ATTACK] = true;
			}
			_atkAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 5);
			//애니메이션 재생이 끝났을 때는 
			if (!_atkAnim->isPlay())
			{
				_atkMotionList[0] = false;
				_atkMotionList[1] = false;
				_atkMotionList[2] = true;
				//만약 원거리 공격자라면
				if (!_atkDistance)
				{
					_isStartAtk = true;
					_turnEnd = true;
					_atkMotionList[1] = true;
				}
				_playAnimList[BATTLE_PLAYER_ATTACK] = false;
			}
		}
	}
	//마법 공격 일 때는 근거리,원거리 상관없이 바로 공격한다.
	if (_status == BATTLE_PLAYER_MAGIC_ATTACK)
	{
		//만약 매직 공격이 재생중이 아니면 이때 마법 공격을 한다.
		if (!_playAnimList[BATTLE_PLAYER_MAGIC_ATTACK])
		{
			_magicAtkAnim->start();
			_playAnimList[BATTLE_PLAYER_MAGIC_ATTACK] = true;
		}
		_magicAtkAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
		if (!_magicAtkAnim->isPlay())
		{
			setPlayerStatusToIdle(_magicAtkAnim);	//공격이 끝나고 나면 다시 IDLE 상태로 전환한다.
			_turnEnd = true;
			_playAnimList[BATTLE_PLAYER_MAGIC_ATTACK] = false;
		}
		
	}
}
void battlePlayerMother::render() 
{
	draw();
	TIMEMANAGER->render(getMemDC());
}
void battlePlayerMother::draw()	  
{
	//================== Start 상태에 따라 다른 애니메이션을 출력한다. =======================
	if (_status == BATTLE_PLAYER_IDLE)
	{
		
		//_idleImg->aniRender(getMemDC(), 800 - (_partyIdx % 2) * 70, 150 + _partyIdx * 100, _idleAnim);
		_idleImg->aniRender(getMemDC(), _posX, _posY, _idleAnim);
	}
	// 스탠바이를 재생하고 그 다음에 공격모션을 한다
	if (_status == BATTLE_PLAYER_ATTACK_STANDBY)
	{
		//_atkStandbyImg->aniRender(getMemDC(), 800 - (_partyIdx % 2) * 70, 150 + _partyIdx * 100, _atkStandbyAnim);
		_atkStandbyImg->aniRender(getMemDC(),_posX, _posY, _atkStandbyAnim);
	}
	if (_status == BATTLE_PLAYER_ATTACK)
	{
		TextOut(getMemDC(), 800 - (_partyIdx % 2) * 70+60, 150 + _partyIdx * 100 - 10, "공격", strlen("공격"));
		//_atkImg->aniRender(getMemDC(), 800 - (_partyIdx % 2) * 70, 150 + _partyIdx * 100, _atkAnim);
		_atkImg->aniRender(getMemDC(), _posX, _posY, _atkAnim);
	}
	//마법 공격 스탠바이를 재생하고 그 다음에 마법 공격 모션을 한다.
	if (_status == BATTLE_PLAYER_MAGIC_ATTACK_STANDBY)
	{

		//_magicAtkStandbyImg->aniRender(getMemDC(), 800 - (_partyIdx % 2) * 70, 150 + _partyIdx * 100, _magicAtkStandbyAnim);
		_magicAtkStandbyImg->aniRender(getMemDC(),_posX, _posY, _magicAtkStandbyAnim);
	}
	//마법 공격
	if (_status == BATTLE_PLAYER_MAGIC_ATTACK)
	{
		
		//_magicAtkImg->aniRender(getMemDC(), 800 - (_partyIdx % 2) * 70, 150 + _partyIdx * 100, _magicAtkAnim);
		_magicAtkImg->aniRender(getMemDC(), _posX, _posY, _magicAtkAnim);
	}

	if (_status == BATTLE_PLAYER_DEAD)
	{
		
		//_deadImg->aniRender(getMemDC(), 800 - (_partyIdx % 2) * 70, 150 + _partyIdx * 100, _deadAnim);
		_deadImg->aniRender(getMemDC(), _posX, _posY, _deadAnim);
	}
	if (_status == BATTLE_PLAYER_WIN_BEFORE)
	{
		//_winBeforeImg->aniRender(getMemDC(), 800 - (_partyIdx % 2) * 70, 150 + _partyIdx * 100, _winBeforeAnim);
		_winBeforeImg->aniRender(getMemDC(), _posX, _posY, _winBeforeAnim);
	}
	if (_status == BATTLE_PLAYER_WIN)
	{
		//_winImg->aniRender(getMemDC(), 800 - (_partyIdx % 2) * 70, 150 + _partyIdx * 100, _winAnim);
		_winImg->aniRender(getMemDC(), _posX, _posY, _winAnim);
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

void battlePlayerMother::setPlayerDefaultPosition()
{
	_posX = 800 - (_partyIdx % 2) * 70;
	_posY = 150 + _partyIdx * 100;
}

void battlePlayerMother::moveToTarget(int targetX, int targetY, int motionListIdx)
{
	RECT rcTarget = RectMake(targetX, targetY, _target->getImageWidth(), _target->getImageHeight());
	RECT rcInter;
	RECT rcChar = RectMake(_posX, _posY, 100,100);
	//타겟까지 도달ㅎ면
	if (IntersectRect(&rcInter, &rcTarget, &rcChar))
	{
		
		//아직 공격 중
		if(motionListIdx < sizeof(_atkMotionList)-1)
		{
			_atkMotionList[motionListIdx] = false;
			_atkMotionList[motionListIdx + 1] = true;
		}
		//공격 끝남
		else {
			_isStartAtk = true;
			setPlayerStatusToIdle(_atkAnim);
			_turnEnd = true;
		}
	}
	//도달 안했으면
	else 
	{
		_angle = getAngle(_posX, _posY, _targetX, _targetY);
		_moveSpd = 12.0f;
		_posX += cosf(_angle) * _moveSpd;
		_posY += -sinf(_angle) * _moveSpd;
	}
}