#include "stdafx.h"
#include "bossAtma.h"
#include "battlePlayerMother.h"

bossAtma::bossAtma()
{
	//=================================================== 에너미 이미지 ==========================================================
	
	_img = IMAGEMANAGER->addFrameImage("bossAtma", ".\\image\\enemyImg\\bossAtma.bmp", 1000, 500, 2, 1, true, RGB(255, 0, 255), true);
	
	//===========================================================================================================================

	//================================================= 에너미 이펙트 이미지 =====================================================
	
	EFFECTMANAGER->addEffect("bossAtma기본공격", ".\\image\\enemyEffect\\effect4.bmp", 304, 64, 76, 64, 1.0f, 1.0f, 2);
	EFFECTMANAGER->addEffect("bossAtma스킬공격1", ".\\image\\enemyEffect\\effect11.bmp", 583, 102, 53, 102, 1.0f, 1.0f, 2);
	EFFECTMANAGER->addEffect("bossAtma스킬공격2", ".\\image\\enemyEffect\\effect6.bmp", 2100, 100, 100, 100, 1.0f, 1.0f, 2);
	
	//===========================================================================================================================
	
	//============================================== 기본공격 사운드 ==============================================

	SOUNDMANAGER->addSound("bossAtma기본공격", ".\\sound\\sfx\\16Fire1.wav", true, false);

	//============================================================================================================

	//============================================== 스킬공격 사운드 ==============================================

	SOUNDMANAGER->addSound("bossAtma스킬공격1", ".\\sound\\sfx\\13Explosion.wav", true, false);
	SOUNDMANAGER->addSound("bossAtma스킬공격2", ".\\sound\\sfx\\15Bolt3.wav", true, false);

	//============================================================================================================

	_Lv = 67;										//레벨
	_maxEXP = 0;	 								//현재 경험치, 최대 경험치
	_gold = 0;										//돈

	_curHP = _maxHP = 55000;						//현재 체력, 최대 체력
	_curMP = _maxMP = 19000;						//현재 마력, 최대 마력

	_attack = 20;									//물리 공격력
	_magic = 10;									//마법 공격력

	_m_Def = 70;									//마법 방어력
	_a_Def = 75;									//물리 방어력

	_speed = 63;									//공격 타이머

	_evasion = 0;									//회피율
	_hitRate = 100;									//명중률
	_block = 0;										//방어율

	_spellPower = _Lv;								//마법력
	_spellPower2 = _Lv * 1.2f;						//마법력2
}


bossAtma::~bossAtma()
{

}

void bossAtma::update()
{
	if (_turnEnd == false)
	{
		if (_count == 0)
		{
			damageAlgorithm();													//에너미 턴이 되면 데미지 공식 함수를 적용
			_rndNum = RND->getFromIntTo(1, 10);									//스킬확률을 조절하기 위한 랜덤값
		}
		_count++;															//카운트 쁠쁠

		//_count가 21보다 작으면 반짝반짝
		if (_count < 21) glitter();


		wsprintf(_basicAttack, "bossAtma기본공격");
		wsprintf(_skillAttack, "bossAtma스킬공격1");
		wsprintf(_skillAttack2, "bossAtma스킬공격2");
	
		//에너미 기본 공격 상태
		if (_rndNum <= 3)
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
		else if (_rndNum <= 7)
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
		}//에너미 스킬2 공격 상태
		else
		{
			//_count가 80보다 커지면 공격 이펙트가 그려짐
			if (_count > 50 && _effectFire == true)
			{
				EFFECTMANAGER->play(_skillAttack2, _target->getPosX() + _target->getWidth() / 2, _target->getPosY() + _target->getHeight() / 2);
				SOUNDMANAGER->play(_skillAttack2, CH_EFFECT05, 1.0f);
				_target->setCurHP(_target->getCurHP() - _spellDamage2);

				if (_target->getCurHP() <= 0)
				{
					_target->setCurHP(0);
				}

				_effectFire = false;
			}
			wsprintf(_damageNum, "%d", (int)_spellDamage2);
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

void bossAtma::render()
{
	Enemy::render();
	IMAGEMANAGER->findImage("bossAtma")->alphaFrameRender(getMemDC(), _x - _img->getFrameWidth() / 2, _y - _img->getFrameHeight() / 2, _frameX, 0, _alpha);
}


void bossAtma::bearSkill()
{

}
