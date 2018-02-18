#include "stdafx.h"
#include "Enemy.h"
#include "battlePlayerMother.h"

Enemy::Enemy()
{
}


Enemy::~Enemy()
{

}

//	     몬스터를 뿌려줄 x,     y
HRESULT Enemy::init(int x, int y)
{
	//============================================== 기타등등 사운드 ==============================================
	
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
		//카운트 쁠쁠
		_count++;

		//_count가 21보다 작으면 반짝반짝
		if (_count < 21) glitter();

		//에너미의 상태가 공격 또는 스킬쓰는 상태를 랜덤으로 받음 
		if (_state == ENEMY_NULL)
		{
			//_state = ENEMY_HIT;
			_state = RND->getFromIntTo(ENEMY_HIT, ENEMY_SPELL);				//공격 or 스펠 상태
			_rndNum = RND->getFromIntTo(0, 10);								//스킬확률을 조절하기 위한 랜덤값
		}

		//에너미 공격 상태면
		if ((_state == ENEMY_HIT && _rndNum <= 7) || (_state == ENEMY_SPELL && _rndNum <= 7))
		{
			//_count가 80보다 커지면 공격 이펙트가 그려짐
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
			//_count가 80보다 커지면 공격 이펙트가 그려짐
			if (_count > 80 && _effectFire == true)
			{
				EFFECTMANAGER->play(skillAttack, _target->getPosX() + _target->getWidth() / 2, _target->getPosY() + _target->getHeight() / 2);
				SOUNDMANAGER->play(skillAttack, CH_EFFECT03, 1.0f);
				_target->setCurHP(_target->getCurHP() - _spellDamage);
				_effectFire = false;
			}
			wsprintf(_damageNum, "%d", (int)_spellDamage);
		}
		

		//_count가 150보다 크면 턴을 플레이어에게 넘긴다
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
		//HFONT newFont = CreateFont(30, 0, 0, 0, 1000, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("Sandoll 미생"));
		//HFONT oldFont = (HFONT)SelectObject(getMemDC(), newFont);
		//DrawText(getMemDC(), _damageNum, -1, &rc, DT_CENTER | DT_WORDBREAK);
		//SelectObject(getMemDC(), oldFont);
		//DeleteObject(oldFont);
		//DeleteObject(newFont);
		TextOut(getMemDC(), _target->getPosX() + 20, _target->getPosY() - 30, _damageNum, strlen(_damageNum));
	}
}

//몬스터 턴이 되면
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

//에너미 턴일때 어떤 에너미의 턴인지 알기위한 함수 (반짝거림)
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
