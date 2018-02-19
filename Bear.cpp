#include "stdafx.h"
#include "Bear.h"
#include "battlePlayerMother.h"

Bear::Bear()
{
	//=================================================== 에너미 이미지 ==========================================================
	
	_img = IMAGEMANAGER->addFrameImage("bear", ".\\image\\enemyImg\\bear.bmp", 180, 106, 2, 1, true, RGB(255, 0, 255), true);
	
	//===========================================================================================================================
	
	//================================================= 에너미 이펙트 이미지 =====================================================
	
	IMAGEMANAGER->addImage("bear기본공격이미지", ".\\image\\enemyEffect\\effect16.bmp", 411, 134, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("bear스킬공격이미지", ".\\image\\enemyEffect\\effect15.bmp", 660, 123, true, RGB(255, 0, 255), true);
	
	_atkEffect = new effect;
	_atkEffect->init(IMAGEMANAGER->findImage("bear기본공격이미지"), 137, 134, 1.0f, 0.5f);

	_spellEffect = new effect;
	_spellEffect->init(IMAGEMANAGER->findImage("bear스킬공격이미지"), 132, 123, 1.0f, 0.5f);
	
	EFFECTMANAGER->addEffect("bear기본공격", ".\\image\\enemyEffect\\effect16.bmp", 411, 134, 137, 134, 1.0f, 1.0f, 2);
	EFFECTMANAGER->addEffect("bear스킬공격", ".\\image\\enemyEffect\\effect15.bmp", 660, 123, 132, 123, 1.0f, 1.0f, 2);
	
	//===========================================================================================================================
	
	//============================================== 기본공격 사운드 ==============================================

	SOUNDMANAGER->addSound("bear기본공격", ".\\sound\\sfx\\8BClawSlash.wav", true, false);

	//============================================================================================================

	//============================================== 스킬공격 사운드 ==============================================

	SOUNDMANAGER->addSound("bear스킬공격", ".\\sound\\sfx\\37Ice2Part2.wav", true, false);

	//============================================================================================================

	_Lv = 5;										//레벨
	_maxEXP = RND->getFromIntTo(150, 170);	 		//현재 경험치, 최대 경험치
	_gold = RND->getFromIntTo(172, 196);			//돈

	_curHP = _maxHP = 275;							//현재 체력, 최대 체력
	_curMP = _maxMP = 0;							//현재 마력, 최대 마력

	_attack = 13;									//물리 공격력
	_magic = 10;									//마법 공격력

	_m_Def = 140;									//마법 방어력
	_a_Def = 40;					 				//물리 방어력

	_speed = 25;									//공격 타이머

	_evasion = 0;									//회피율
	_hitRate = 100;									//명중률
	_block = 0;										//방어율

	_spellPower = _Lv;								//마법력


}

Bear::~Bear()
{

}

//HRESULT Bear::init()
//{
//
//
//	return S_OK;
//}

void Bear::update()
{
	Enemy::update();
	wsprintf(basicAttack, "bear기본공격");
	wsprintf(skillAttack, "bear스킬공격");
}

void Bear::render()
{
	Enemy::render();
	IMAGEMANAGER->findImage("bear")->alphaFrameRender(getMemDC(), _x - _img->getFrameWidth() / 2, _y - _img->getFrameHeight() / 2, _frameX, 0, _alpha);
}

void Bear::bearSkill()
{

}