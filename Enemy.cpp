#include "stdafx.h"
#include "Enemy.h"

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
	if (_turnEnd == false)
	{

		//ī��Ʈ �ܻ�
		_count++;

		//_count�� 21���� ������ ��¦��¦
		if (_count < 21) glitter();

		//���ʹ��� ���°� ���� �Ǵ� ��ų���� ���¸� �������� ���� 
		if (_state == ENEMY_NULL)
		{
			//_state = ENEMY_HIT;
			_state = RND->getFromIntTo(ENEMY_HIT, ENEMY_SPELL);				//���� or ���� ����
			_rndNum = RND->getFromIntTo(0, 10);								//��ųȮ���� �����ϱ� ���� ������
		}

		//���ʹ� ���� ���¸�
		if ((_state == ENEMY_HIT && _rndNum <= 7) || (_state == ENEMY_SPELL && _rndNum <= 7))
		{
			//_count�� 80���� Ŀ���� ���� ����Ʈ�� �׷���
			if (_count > 80 && _effectFire == true)
			{
				EFFECTMANAGER->play(basicAttack, 800, 320);
				SOUNDMANAGER->play(basicAttack, CH_EFFECT03, 1.0f);

				_effectFire = false;
			}
		}
		if ((_state == ENEMY_HIT && _rndNum > 7) || (_state == ENEMY_SPELL && _rndNum > 7))
		{
			//_count�� 80���� Ŀ���� ���� ����Ʈ�� �׷���
			if (_count > 80 && _effectFire == true)
			{
				EFFECTMANAGER->play(skillAttack, 800, 320);
				SOUNDMANAGER->play(skillAttack, CH_EFFECT03, 1.0f);

				_effectFire = false;

			}
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
	
}

//���� ���� �Ǹ�
void Enemy::enemyTurn(int damage)
{
	if (_state == RND->getFromIntTo(ENEMY_HIT, ENEMY_SPELL));
	{
		//���� ������ ����
		//���� = Damage = Level * Level * (Battle Power * 4 + Vigor) / 256
		//Vigor = 56 ~ 63 ������
		int _2Lv;
		_2Lv = _Lv * _Lv;
		
		_damage = _2Lv * (damage * 4 + (RND->getFromIntTo(56, 63))) / 256; 
		
		//��ų ������ ����
		//_spellDamage = _damage * RND->getFromFloatTo(1.2f, 2.5f);
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
