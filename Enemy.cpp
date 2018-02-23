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
	_enemyItemNum = RND->getFromIntTo(1, 100);

	if (_turnEnd == false)
	{
		if (_count == 0) damageAlgorithm();									//에너미 턴이 되면 데미지 공식 함수를 적용

		//카운트 쁠쁠
		_count++;

		//_count가 21보다 작으면 반짝반짝
		if (_count < 21) glitter();

		//에너미의 상태가 공격 또는 스킬쓰는 상태를 랜덤으로 받음 
		if (_state == ENEMY_NULL)
		{
			//_state = ENEMY_HIT;
			_state = RND->getFromIntTo(ENEMY_HIT, ENEMY_SPELL);				//공격 or 스펠 상태
			_rndNum = RND->getFromIntTo(1, 10);								//스킬확률을 조절하기 위한 랜덤값
		}

		//에너미 기본 공격 상태
		if ((_state == ENEMY_HIT && _rndNum <= 8) || (_state == ENEMY_SPELL && _rndNum <= 8))
		{
			//_count가 80보다 커지면 공격 이펙트가 그려짐
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

		//에너미 스킬 공격 상태
		if ((_state == ENEMY_HIT && _rndNum > 8) || (_state == ENEMY_SPELL && _rndNum > 8))
		{
			//_count가 80보다 커지면 공격 이펙트가 그려짐
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
	//데미지가 뜨는걸 랜더로 그려주자!!
	if (_count > 80 && _count < 150)
	{
		TextOut(getMemDC(), _target->getPosX() + 25, _target->getPosY() - 30, _damageNum, strlen(_damageNum));
	}
}

//몬스터 턴이 되면
void Enemy::damageAlgorithm()
{
	bool _hit;																								//맞았는지 빗나갔는지를 알기위한 불값
	float BlockValue = (255 - _target->getMDef() * 2) + 1;													//회피율 공식 _target->getMDef() == 플레이어의 마법방어력 수치
	if (BlockValue > 255) BlockValue = 255;																	//BlockValue가 255 보다 크면 BlockValue값은 255
	if (BlockValue < 1) BlockValue = 1;																		//BlockValue가 1보다 작으면 BlockValue값은 1
	if (((float)_hitRate * BlockValue / 256) > RND->getFromFloatTo(0, 0.99f))								
	{
		_hit = true;																						//맞았다!
	}
	else
	{
		_hit = false;																						//빗나감 ㅠㅠ
	}

	if (_hit == true)																						//맞앗으면 데미지 공식 적용
	{																										
		int Vigor = RND->getInt(8) + 56;																	// Vigor는 56 ~ 63 랜덤값
		_damage = (float)_Lv * (float)_Lv * ((float)_attack * 4 + (float)Vigor) / 256;						// 데미지 공식
		_damage = (_damage * (float)RND->getFromIntTo(224, 255) / 256) + 1;									// 데미지에서 방어력을 빼는 공식
		_damage = (_damage * (255 - (float)_target->getADef()) / 256) + 1;									// 데미지에서 방어력을 빼는 공식
																											
		_spellDamage = _spellPower * 4 + ((float)_Lv * ((float)_magic * 3 / 2) * _spellPower) / 32;			// 스킬 데미지 공식
	}
	else																									//빗나갔다 ㅠㅠ 데미지 스킬데미지 0
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