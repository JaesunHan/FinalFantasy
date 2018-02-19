#include "stdafx.h"
#include "battlePlayerMother.h"
#include "BattleScene.h"
#include "Enemy.h"


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
	
	//attack �϶�
	if (_status == BATTLE_PLAYER_ATTACK)
	{
		//������ ���۵�����
		if (_isStartAtk)
		{
			_isStartAtk = false;
			_atkMotionList[0] = true;
			_atkMotionList[1] = false;
			_atkMotionList[2] = false;
		}
		//�ٰŸ� ������ �ΰ�쿡��
		if (_atkDistance)
		{
			//���ʹ����� �����Ϸ� ����.
			if (_atkMotionList[0])
			{
				//������ �������� �ϴ��� �����ϱ�
				_targetX = _target->getX();
				_targetY = _target->getY();
				moveToTarget(_targetX, _targetY, 0);
			}
			//���ڸ��� ���ƿ´�
			if (_atkMotionList[2])
			{
				_targetX = 760 + (_partyIdx % 2) * 70;
				_targetY = 150 + _partyIdx * 100;
				if (moveToTarget(_targetX, _targetY, 2))
				{
					_posX = _targetX;
					_posY = _targetY;
				}
			}
		}
		//���Ÿ� �������� ���� 
		else
		{
			_atkMotionList[1] = true;
		}
		//���� �����Ѵ�.
		if (_atkMotionList[1])
		{
			//���� ����Ʈ ���尡 ������� �ƴϸ� ����Ѵ�.
			if (!SOUNDMANAGER->isPlaySound(_atkEffectSoundKey))
			{
				SOUNDMANAGER->play(_atkEffectSoundKey, CH_SOKKONGGU, 1.0f);
			}
			//���� ����� �� 
			//���� ���Ÿ� �����ڶ�� �̹��� ���� ��ġ�� ��������� �Ѵ�
			//���� ����� ������ ���� ���̰� �޶�!
			if (!_atkDistance)
			{
				_posX = 760 + (_partyIdx % 2) * 70 - _atkImg->getFrameWidth()/4*3;
			}
			if (!_playAnimList[BATTLE_PLAYER_ATTACK])
			{
				_atkAnim->start();
				_playAnimList[BATTLE_PLAYER_ATTACK] = true;
			}
			_atkAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * _atkAnimPlaySPD);
			//�ִϸ��̼� ����� ������ ���� 
			if (!_atkAnim->isPlay())
			{
				_atkMotionList[0] = false;
				_atkMotionList[1] = false;
				_atkMotionList[2] = true;
				//���� ���Ÿ� �����ڶ��
				if (!_atkDistance)
				{
					_isStartAtk = true;
					_atkMotionList[1] = true;
					setPlayerStatusToIdle(_atkAnim);
				}
				
				_playAnimList[BATTLE_PLAYER_ATTACK] = false;
				_BS->playerAttack();
				
			}
			
		}
	}
	//���� ���� �� ���� �ٰŸ�,���Ÿ� ������� �ٷ� �����Ѵ�.
	if (_status == BATTLE_PLAYER_MAGIC_ATTACK)
	{
		//���� ���� ������ ������� �ƴϸ� �̶� ���� ������ �Ѵ�.
		if (!_playAnimList[BATTLE_PLAYER_MAGIC_ATTACK])
		{
			_magicAtkAnim->start();
			_playAnimList[BATTLE_PLAYER_MAGIC_ATTACK] = true;
		}
		_magicAtkAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
		if (!_magicAtkAnim->isPlay())
		{
			setPlayerStatusToIdle(_magicAtkAnim);	//������ ������ ���� �ٽ� IDLE ���·� ��ȯ�Ѵ�.
			_turnEnd = true;
			_playAnimList[BATTLE_PLAYER_MAGIC_ATTACK] = false;
		}
		
	}

	
}
void battlePlayerMother::render() 
{
	draw();
	//TIMEMANAGER->render(getMemDC());
	//if (_status == BATTLE_PLAYER_ATTACK)
	//{
	//	RECT rc = RectMakeCenter(_targetX, _targetY, _target->getImageWidth() - 20, _target->getImageHeight() - 20);
	//	Rectangle(getMemDC(), rc.left, rc.top, rc.right, rc.bottom);
	//}
	
}
void battlePlayerMother::draw()	  
{
	//================== Start ���¿� ���� �ٸ� �ִϸ��̼��� ����Ѵ�. =======================
	if (_status == BATTLE_PLAYER_IDLE)
	{
		
		//_idleImg->aniRender(getMemDC(), 800 - (_partyIdx % 2) * 70, 150 + _partyIdx * 100, _idleAnim);
		_idleImg->aniRender(getMemDC(), _posX, _posY, _idleAnim);
	}
	// ���Ĺ��̸� ����ϰ� �� ������ ���ݸ���� �Ѵ�
	if (_status == BATTLE_PLAYER_ATTACK_STANDBY)
	{
		//_atkStandbyImg->aniRender(getMemDC(), 800 - (_partyIdx % 2) * 70, 150 + _partyIdx * 100, _atkStandbyAnim);
		_atkStandbyImg->aniRender(getMemDC(),_posX, _posY, _atkStandbyAnim);
	}
	if (_status == BATTLE_PLAYER_ATTACK)
	{
		TextOut(getMemDC(), 800 - (_partyIdx % 2) * 70+60, 150 + _partyIdx * 100 - 10, "����", strlen("����"));
		//_atkImg->aniRender(getMemDC(), 800 - (_partyIdx % 2) * 70, 150 + _partyIdx * 100, _atkAnim);
		_atkImg->aniRender(getMemDC(), _posX, _posY, _atkAnim);
	}
	//���� ���� ���Ĺ��̸� ����ϰ� �� ������ ���� ���� ����� �Ѵ�.
	if (_status == BATTLE_PLAYER_MAGIC_ATTACK_STANDBY)
	{
	
		//_magicAtkStandbyImg->aniRender(getMemDC(), 800 - (_partyIdx % 2) * 70, 150 + _partyIdx * 100, _magicAtkStandbyAnim);
		_magicAtkStandbyImg->aniRender(getMemDC(),_posX, _posY, _magicAtkStandbyAnim);
	}
	//���� ����
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
	//_idleImg->aniRender(getMemDC(), _posX, _posY, _idleAnim);
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
		setPlayerDefaultPosition();
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

	
	//���� �� 
	if (_status == BATTLE_PLAYER_DEAD)
	{
		if (!_playAnimList[BATTLE_PLAYER_DEAD])
		{
			_deadAnim->start();
			_playAnimList[BATTLE_PLAYER_DEAD] = true;
		}
		_deadAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		
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
		if (!_winBeforeAnim->isPlay())
		{
			_status = BATTLE_PLAYER_WIN;
		}
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
	_posX = 760 + (_partyIdx % 2) * 70;
	_posY = 150 + _partyIdx * 100;
}

bool battlePlayerMother::moveToTarget(int targetX, int targetY, int motionListIdx)
{
	RECT rcTarget = RectMakeCenter(targetX, targetY, _target->getImageWidth()-20, _target->getImageHeight()-20);
	RECT rcInter;
	RECT rcChar = RectMake(_posX, _posY, 100,100);

	//Ÿ�ٱ��� ���ޤ���
	if (IntersectRect(&rcInter, &rcTarget, &rcChar))
	{
		
		//���� ���� ��
		if(motionListIdx < sizeof(_atkMotionList)-1)
		{
			_atkMotionList[motionListIdx] = false;
			_atkMotionList[motionListIdx + 1] = true;
		}
		//���� ����
		else {
			_isStartAtk = true;
			setPlayerStatusToIdle(_atkAnim);
			_turnEnd = true;
		}
		return true;
	}
	//���� ��������
	else 
	{
		_angle = getAngle(_posX, _posY+_atkImg->getFrameHeight()/2, _targetX, _targetY);
		_moveSpd = 50.0f;
		_posX += cosf(_angle) * _moveSpd;
		_posY += -sinf(_angle) * _moveSpd;
		return false;
	}
}