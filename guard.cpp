#include "stdafx.h"
#include "guard.h"
#include "battlePlayerMother.h"

guard::guard()
{
	//=================================================== 에너미 이미지 ==========================================================
	
	_img = IMAGEMANAGER->addFrameImage("guard", ".\\image\\enemyImg\\guard.bmp", 132, 62, 2, 1, true, RGB(255, 0, 255), true);
	
	//===========================================================================================================================

	//================================================= 에너미 이펙트 이미지 =====================================================

	EFFECTMANAGER->addEffect("guard기본공격", ".\\image\\enemyEffect\\effect1.bmp", 1800, 130, 150, 130, 1.0f, 1.0f, 2);
	EFFECTMANAGER->addEffect("guard스킬공격", ".\\image\\enemyEffect\\effect2.bmp", 1536, 192, 192, 192, 1.0f, 1.0f, 2);
	
	//===========================================================================================================================
	
	//============================================== 기본공격 사운드 ==============================================

	SOUNDMANAGER->addSound("guard기본공격", ".\\sound\\sfx\\2ESwordSlashLong.wav", true, false);

	//============================================================================================================

	//============================================== 스킬공격 사운드 ==============================================

	SOUNDMANAGER->addSound("guard스킬공격", ".\\sound\\sfx\\BEDeathToll.wav", true, false);

	//============================================================================================================

	_Lv = 5;										//레벨
	_maxEXP = RND->getFromIntTo(45, 50) * 100; 		//현재 경험치, 최대 경험치
	_gold = RND->getFromIntTo(45, 50);				//돈

	_curHP = _maxHP = 40;							//현재 체력, 최대 체력
	_curMP = _maxMP = 15;							//현재 마력, 최대 마력

	_attack = 16;									//물리 공격력
	_magic = 6;										//마법 공격력

	_m_Def = 140;									//마법 방어력
	_a_Def = 100;									//물리 방어력

	_speed = 30;									//공격 타이머

	_evasion = 0;									//회피율
	_hitRate = 100;									//명중률
	_block = 0;										//방어율
	
	_spellPower = _Lv - 2;							//마법력

	setItemDropRate(01, 02, 30, 30, 15, 12, 06, 03, 01, 00, 00);
	setItemString();
}


guard::~guard()
{

}

void guard::update()
{
	Enemy::update();
	wsprintf(_basicAttack, "guard기본공격");
	wsprintf(_skillAttack, "guard스킬공격");
}

void guard::render()
{
	Enemy::render();
	IMAGEMANAGER->findImage("guard")->alphaFrameRender(getMemDC(), _x - _img->getFrameWidth() / 2, _y - _img->getFrameHeight() / 2, _frameX, 0, _alpha);
}


void guard::bearSkill()
{

}
