#include "stdafx.h"
#include "Enemy.h"
#include "battlePlayerMother.h"

Enemy::Enemy()
{
}


Enemy::~Enemy()
{

}

//	     ���͸� �ѷ��� x,     y
HRESULT Enemy::init(int x, int y)
{
	//============================================== ��Ÿ��� ���� ==============================================
	
	SOUNDMANAGER->addSound("monsterDie", ".\\sound\\sfx\\2DMonsterDeath.wav", true, false);
	SOUNDMANAGER->addSound("attackMissSound", ".\\sound\\sfx\\0DMiss.wav", true, false);

	//============================================================================================================

	_x = x;
	_y = y;
	_alpha = 255;
	_frameX = 0;
	_glitterCount = 0;
	_rndNum = 0;

	_state = ENEMY_NULL;

	_turnEnd = false;
	_effectFire = true;

	return S_OK;
}

void Enemy::update()
{
	_enemyItemNum = RND->getFromIntTo(1, 100);

	if (_turnEnd == false)
	{
		if (_count == 0) damageAlgorithm();									//���ʹ� ���� �Ǹ� ������ ���� �Լ��� ����

		//ī��Ʈ �ܻ�
		_count++;

		//_count�� 21���� ������ ��¦��¦
		if (_count < 21) glitter();

		//���ʹ��� ���°� ���� �Ǵ� ��ų���� ���¸� �������� ���� 
		if (_state == ENEMY_NULL)
		{
			//_state = ENEMY_HIT;
			_state = RND->getFromIntTo(ENEMY_HIT, ENEMY_SPELL);				//���� or ���� ����
			_rndNum = RND->getFromIntTo(1, 10);								//��ųȮ���� �����ϱ� ���� ������
		}

		//���ʹ� �⺻ ���� ����
		if ((_state == ENEMY_HIT && _rndNum <= 8) || (_state == ENEMY_SPELL && _rndNum <= 8))
		{
			//_count�� 80���� Ŀ���� ���� ����Ʈ�� �׷���
			if (_count > 50 && _effectFire == true)
			{
				EFFECTMANAGER->play(_basicAttack, _target->getPosX() + _target->getWidth() / 2, _target->getPosY() + _target->getHeight() / 2);
				SOUNDMANAGER->play(_basicAttack, CH_EFFECT05, 1.0f);
				_target->setCurHP(_target->getCurHP() - _damage);
				
				if (_target->getCurHP() <= 0)
				{
					_target->setCurHP(0);
				}

				_effectFire = false;
			}
			wsprintf(_damageNum, "%d", (int)_damage);
		}

		//���ʹ� ��ų ���� ����
		if ((_state == ENEMY_HIT && _rndNum > 8) || (_state == ENEMY_SPELL && _rndNum > 8))
		{
			//_count�� 80���� Ŀ���� ���� ����Ʈ�� �׷���
			if (_count > 50 && _effectFire == true)
			{
				EFFECTMANAGER->play(_skillAttack, _target->getPosX() + _target->getWidth() / 2, _target->getPosY() + _target->getHeight() / 2);
				SOUNDMANAGER->play(_skillAttack, CH_EFFECT05, 1.0f);
				_target->setCurHP(_target->getCurHP() - _spellDamage);

				if (_target->getCurHP() <= 0)
				{
					_target->setCurHP(0);
				}

				_effectFire = false;
			}
			wsprintf(_damageNum, "%d", (int)_spellDamage);
		}
		
		//_count�� 150���� ũ�� ���� �÷��̾�� �ѱ��
		if (_count > 150)
		{
			_turnEnd = true;
			_effectFire = true;
			_state = ENEMY_NULL;
			_glitterCount = 0;
			_count = 0;
		}
	}
}

void Enemy::render() 
{
	//�������� �ߴ°� ������ �׷�����!!
	if (_count > 80 && _count < 150)
	{
		TextOut(getMemDC(), _target->getPosX() + 25, _target->getPosY() - 30, _damageNum, strlen(_damageNum));
	}
}

//���� ���� �Ǹ�
void Enemy::damageAlgorithm()
{
	bool _hit;																								//�¾Ҵ��� ������������ �˱����� �Ұ�
	float BlockValue = (255 - _target->getMDef() * 2) + 1;													//ȸ���� ���� _target->getMDef() == �÷��̾��� �������� ��ġ
	if (BlockValue > 255) BlockValue = 255;																	//BlockValue�� 255 ���� ũ�� BlockValue���� 255
	if (BlockValue < 1) BlockValue = 1;																		//BlockValue�� 1���� ������ BlockValue���� 1
	if (((float)_hitRate * BlockValue / 256) > RND->getFromFloatTo(0, 0.99f))								
	{
		_hit = true;																						//�¾Ҵ�!
	}
	else
	{
		_hit = false;																						//������ �Ф�
	}

	if (_hit == true)																						//�¾����� ������ ���� ����
	{																										
		int Vigor = RND->getInt(8) + 56;																	// Vigor�� 56 ~ 63 ������
		_damage = (float)_Lv * (float)_Lv * ((float)_attack * 4 + (float)Vigor) / 256;						// ������ ����
		_damage = (_damage * (float)RND->getFromIntTo(224, 255) / 256) + 1;									// ���������� ������ ���� ����
		_damage = (_damage * (255 - (float)_target->getADef()) / 256) + 1;									// ���������� ������ ���� ����
																											
		_spellDamage = _spellPower * 4 + ((float)_Lv * ((float)_magic * 3 / 2) * _spellPower) / 32;			// ��ų ������ ����
	}
	else																									//�������� �Ф� ������ ��ų������ 0
	{
		_damage = 0;
		_spellDamage = 0;
	}
}

//���ʹ� ���϶� � ���ʹ��� ������ �˱����� �Լ� (��¦�Ÿ�)
void Enemy::glitter()
{
	_glitterCount++;

	if (_glitterCount % 3 == 0)
	{
		_frameX = 1;
		_glitterCount = 0;
	}
	else
	{
		_frameX = 0;
	}
}