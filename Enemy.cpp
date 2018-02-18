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
	if (_turnEnd == false)
	{
		if (_count == 0) damageAlgorithm();
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
				EFFECTMANAGER->play(basicAttack, _target->getPosX() + _target->getWidth() / 2, _target->getPosY() + _target->getHeight() / 2);
				SOUNDMANAGER->play(basicAttack, CH_EFFECT03, 1.0f);
				_target->setCurHP(_target->getCurHP() - _damage);
				_effectFire = false;
			}
			wsprintf(_damageNum, "%d", (int)_damage);
		}
		if ((_state == ENEMY_HIT && _rndNum > 7) || (_state == ENEMY_SPELL && _rndNum > 7))
		{
			//_count�� 80���� Ŀ���� ���� ����Ʈ�� �׷���
			if (_count > 80 && _effectFire == true)
			{
				EFFECTMANAGER->play(skillAttack, _target->getPosX() + _target->getWidth() / 2, _target->getPosY() + _target->getHeight() / 2);
				SOUNDMANAGER->play(skillAttack, CH_EFFECT03, 1.0f);
				_target->setCurHP(_target->getCurHP() - _spellDamage);
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
	if (_count > 100 && _count < 150)
	{
		//RECT rc = { _target->getPosX() - 50, _target->getPosY() + 30, _target->getPosX() + 150, _target->getPosY() };
		//HFONT newFont = CreateFont(30, 0, 0, 0, 1000, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("Sandoll �̻�"));
		//HFONT oldFont = (HFONT)SelectObject(getMemDC(), newFont);
		//DrawText(getMemDC(), _damageNum, -1, &rc, DT_CENTER | DT_WORDBREAK);
		//SelectObject(getMemDC(), oldFont);
		//DeleteObject(oldFont);
		//DeleteObject(newFont);
		TextOut(getMemDC(), _target->getPosX() + 20, _target->getPosY() - 30, _damageNum, strlen(_damageNum));
	}
}

//���� ���� �Ǹ�
void Enemy::damageAlgorithm()
{
	bool _hit;
	float BlockValue = (255 - _target->getMDef() * 2) + 1;
	if (BlockValue > 255) BlockValue = 255;
	if (BlockValue < 1) BlockValue = 1;
	if (((float)_hitRate * BlockValue / 256) > RND->getFromFloatTo(0, 0.99f))
	{
		_hit = true;
	}
	else
	{
		_hit = false;
	}
	if (_hit == true)
	{
		int Vigor = RND->getInt(8) + 56;
		_damage = (float)_Lv * (float)_Lv * ((float)_attack * 4 + (float)Vigor) / 256;
		_damage = (_damage * (float)RND->getFromIntTo(224, 255) / 256) + 1;
		_damage = (_damage * (255 - (float)_target->getADef()) / 256) + 1;
		_spellDamage = _spellPower * 4 + ((float)_Lv * ((float)_magic * 3 / 2) * _spellPower) / 32;
	}
	else
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
