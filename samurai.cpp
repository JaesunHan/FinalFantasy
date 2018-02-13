#include "stdafx.h"
#include "samurai.h"
#include "battlePlayerMother.h"

samurai::samurai()
{
	//=================================================== 에너미 이미지 ==========================================================
	_img = IMAGEMANAGER->addFrameImage("samurai", ".\\image\\enemyImg\\samurai.bmp", 108, 103, 2, 1, true, RGB(255, 0, 255), true);
	//===========================================================================================================================

	//================================================= 에너미 이펙트 이미지 =====================================================
	IMAGEMANAGER->addImage("samurai기본공격이미지", ".\\image\\enemyEffect\\effect1.bmp", 1800, 130, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("samurai스킬공격이미지", ".\\image\\enemyEffect\\effect3.bmp", 800, 50, true, RGB(255, 0, 255), true);

	_atkEffect = new effect;
	_atkEffect->init(IMAGEMANAGER->findImage("samurai기본공격이미지"), 150, 130, 1.0f, 0.5f);

	_spellEffect = new effect;
	_spellEffect->init(IMAGEMANAGER->findImage("samurai스킬공격이미지"), 100, 50, 1.0f, 0.5f);

	EFFECTMANAGER->addEffect("samurai기본공격이펙트", ".\\image\\enemyEffect\\effect1.bmp", 1800, 130, 150, 130, 1.0f, 1.0f, 1000);
	EFFECTMANAGER->addEffect("samurai스킬공격이펙트", ".\\image\\enemyEffect\\effect3.bmp", 800, 50, 100, 50, 1.0f, 1.0f, 1000);
	//===========================================================================================================================

	_Lv = 40;										//레벨
	_maxEXP = RND->getFromIntTo(1500, 1600);		//현재 경험치, 최대 경험치
	_gold = RND->getFromIntTo(750, 850);			//돈

	_curHP = _maxHP = 3000;							//현재 체력, 최대 체력
	_curMP = _maxMP = 500;							//현재 마력, 최대 마력

	_attack = 13;									//물리 공격력
	_magic = 10;									//마법 공격력

	_m_Def = 20;									//마법 방어력
	_a_Def = 10;									//물리 방어력

	_speed = 20;									//공격 타이머

	_evasion = 0;									//회피율
	_hitRate = 100;									//명중률
	_block = 0;										//방어율
}


samurai::~samurai()
{

}

void samurai::update()
{
	if (_turnEnd == false)
	{
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
				EFFECTMANAGER->play("samurai기본공격이펙트", 800, 320);
				SOUNDMANAGER->play("samurai기본공격sound", CH_EFFECT03, 1.0f);

				_effectFire = false;
			}
		}
		if ((_state == ENEMY_HIT && _rndNum > 7) || (_state == ENEMY_SPELL && _rndNum > 7))
		{
			//_count가 80보다 커지면 공격 이펙트가 그려짐
			if (_count > 80 && _effectFire == true)
			{
				EFFECTMANAGER->play("samurai스킬공격이펙트", 800, 320);
				SOUNDMANAGER->play("samurai스킬공격sound", CH_EFFECT03, 1.0f);

				_effectFire = false;

			}
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

void samurai::render()
{
	IMAGEMANAGER->findImage("samurai")->alphaFrameRender(getMemDC(), _x - _img->getWidth() / 2, _y - _img->getHeight() / 2, _frameX, 0, _alpha);
	//IMAGEMANAGER->findImage("samurai")->frameRender(getMemDC(), _x, _y);
}


void samurai::bearSkill()
{

}
