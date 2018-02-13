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
	//================== Start ���¿� ���� �ٸ� �ִϸ��̼��� ����Ѵ�. =======================
	if (_status == BATTLE_PLAYER_IDLE)
	{
		
		_idleImg->aniRender(getMemDC(), 800 - (_partyIdx % 2) * 70, 150 + _partyIdx * 100, _idleAnim);
	}
	// ���Ĺ��̸� ����ϰ� �� ������ ���ݸ���� �Ѵ�
	if (_status == BATTLE_PLAYER_ATTACK_STANDBY)
	{
		_atkStandbyImg->aniRender(getMemDC(), 800 - (_partyIdx % 2) * 70, 150 + _partyIdx * 100, _atkStandbyAnim);
	}
	if (_status == BATTLE_PLAYER_ATTACK)
	{
		//TextOut(getMemDC(), 800 - (_partyIdx % 2) * 70+60, 150 + _partyIdx * 100 - 10, "����", strlen("����"));
		_atkImg->aniRender(getMemDC(), 800 - (_partyIdx % 2) * 70, 150 + _partyIdx * 100, _atkAnim);
	}
	//���� ���� ���Ĺ��̸� ����ϰ� �� ������ ���� ���� ����� �Ѵ�.
	if (_status == BATTLE_PLAYER_MAGIC_ATTACK_STANDBY)
	{

		_magicAtkStandbyImg->aniRender(getMemDC(), 800 - (_partyIdx % 2) * 70, 150 + _partyIdx * 100, _magicAtkStandbyAnim);
	}
	//���� ����
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
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		_status = (baattlePlayerStatus)((int)_status + 1);
		if (_status >= BATTLE_PLAYER_NONE-1)	 _status = BATTLE_PLAYER_IDLE;
		_playAnimList[_status] = false;
	}
	//IDLE�϶�
	if (_status == BATTLE_PLAYER_IDLE)
	{
		//�ִϸ��̼� ������� �ƴ� �� 
		if (!_playAnimList[BATTLE_PLAYER_IDLE])
		{
			_idleAnim->start();		//�ִϸ��̼� ����
			_playAnimList[BATTLE_PLAYER_IDLE] = true;		//������̴ϱ� true �ٲٱ�
		}
		_idleAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
		
	}
	//attack ���Ĺ���
	if (_status == BATTLE_PLAYER_ATTACK_STANDBY)
	{
		if (!_playAnimList[BATTLE_PLAYER_ATTACK_STANDBY])
		{
			_atkStandbyAnim->start();
			_playAnimList[BATTLE_PLAYER_ATTACK_STANDBY] = true;
		}
		_atkStandbyAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
	}
	//attack �϶�
	if (_status == BATTLE_PLAYER_ATTACK)
	{
		if (!_playAnimList[BATTLE_PLAYER_ATTACK])
		{
			_atkAnim->start();
			_playAnimList[BATTLE_PLAYER_ATTACK] = true;
		}
		_atkAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
		setPlayerStatusToIdle(_atkAnim);		//������ ������ ���� �ٽ� IDLE ���·� ��ȯ�Ѵ�.
	}
	//���� ���� ���Ĺ���
	if (_status == BATTLE_PLAYER_MAGIC_ATTACK_STANDBY)
	{
		if (!_playAnimList[BATTLE_PLAYER_MAGIC_ATTACK_STANDBY])
		{
			_magicAtkStandbyAnim->start();
			_playAnimList[BATTLE_PLAYER_MAGIC_ATTACK_STANDBY] = true;
		}
		_magicAtkStandbyAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
	}

	//���� ����
	if (_status == BATTLE_PLAYER_MAGIC_ATTACK)
	{
		if (!_playAnimList[BATTLE_PLAYER_MAGIC_ATTACK])
		{
			_magicAtkAnim->start();
			_playAnimList[BATTLE_PLAYER_MAGIC_ATTACK] = true;
		}
		_magicAtkAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
		setPlayerStatusToIdle(_magicAtkAnim);	//������ ������ ���� �ٽ� IDLE ���·� ��ȯ�Ѵ�.
	}
	//���� �� 
	if (_status == BATTLE_PLAYER_DEAD)
	{
		if (!_playAnimList[BATTLE_PLAYER_DEAD])
		{
			_deadAnim->start();
			_playAnimList[BATTLE_PLAYER_DEAD] = true;
		}
		_deadAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 5);
		
	}
	//�̱�� ���� �ѹ��� ����Ǿ�� �ϴ� �ִϸ��̼� �̴�.
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

