#include "stdafx.h"
#include "siren.h"
#include "battlePlayerMother.h"

siren::siren()
{
	//=================================================== 에너미 이미지 ==========================================================
	
	_img = IMAGEMANAGER->addFrameImage("siren", ".\\image\\enemyImg\\siren.bmp", 368, 148, 2, 1, true, RGB(255, 0, 255), true);
	
	//===========================================================================================================================

	//================================================= 에너미 이펙트 이미지 =====================================================
	
	IMAGEMANAGER->addImage("siren기본공격이미지", ".\\image\\enemyEffect\\effect14.bmp", 608, 76, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("siren스킬공격이미지", ".\\image\\enemyEffect\\effect9.bmp", 480, 59, true, RGB(255, 0, 255), true);

	_atkEffect = new effect;
	_atkEffect->init(IMAGEMANAGER->findImage("siren기본공격이미지"), 76, 76, 1.0f, 0.5f);

	_spellEffect = new effect;
	_spellEffect->init(IMAGEMANAGER->findImage("siren스킬공격이미지"), 80, 59, 1.0f, 0.5f);

	EFFECTMANAGER->addEffect("siren기본공격이펙트", ".\\image\\enemyEffect\\effect14.bmp", 608, 76, 76, 76, 1.0f, 1.0f, 1000);
	EFFECTMANAGER->addEffect("siren스킬공격이펙트", ".\\image\\enemyEffect\\effect9.bmp", 480, 59, 80, 59, 1.0f, 1.0f, 1000);
	
	//===========================================================================================================================
	
	//============================================== 기본공격 사운드 ==============================================

	SOUNDMANAGER->addSound("siren기본공격sound", ".\\sound\\sfx\\BFBuyingSelling.wav", true, false);

	//============================================================================================================

	//============================================== 스킬공격 사운드 ==============================================

	SOUNDMANAGER->addSound("siren스킬공격sound", ".\\sound\\sfx\\BBBigClose.wav", true, false);

	//============================================================================================================

	_Lv = 50;										//레벨
	_maxEXP = RND->getFromIntTo(2800, 3200);		//현재 경험치, 최대 경험치
	_gold = RND->getFromIntTo(1100, 1300);			//돈

	_curHP = _maxHP = 10050;						//현재 체력, 최대 체력
	_curMP = _maxMP = 12850;						//현재 마력, 최대 마력

	_attack = 13;									//물리 공격력
	_magic = 15;									//마법 공격력

	_m_Def = 170;									//마법 방어력
	_a_Def = 70;									//물리 방어력

	_speed = 35;									//공격 타이머

	_evasion = 0;									//회피율
	_hitRate = 100;									//명중률
	_block = 0;										//방어율
}


siren::~siren()
{

}

void siren::update()
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
				EFFECTMANAGER->play("siren기본공격이펙트", 800, 320);
				SOUNDMANAGER->play("siren기본공격sound", CH_EFFECT03, 1.0f);

				_effectFire = false;
			}
		}
		if ((_state == ENEMY_HIT && _rndNum > 7) || (_state == ENEMY_SPELL && _rndNum > 7))
		{
			//_count가 80보다 커지면 공격 이펙트가 그려짐
			if (_count > 80 && _effectFire == true)
			{
				EFFECTMANAGER->play("siren스킬공격이펙트", 800, 320);
				SOUNDMANAGER->play("siren스킬공격sound", CH_EFFECT03, 1.0f);

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

void siren::render()
{
	IMAGEMANAGER->findImage("siren")->alphaFrameRender(getMemDC(), _x - _img->getFrameWidth(), _y - _img->getFrameHeight(), _frameX, 0, _alpha);
	//IMAGEMANAGER->findImage("siren")->frameRender(getMemDC(), _x, _y);
}


void siren::bearSkill()
{

}
